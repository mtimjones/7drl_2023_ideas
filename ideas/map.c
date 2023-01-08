#include "headers.h"
#include "ces.h"

cell_t map[ MAP_MAX_NCOLS ][ MAP_MAX_NROWS ];

location_t deltas[4] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

bool valid_map_location( int col, int row )
{
   bool valid = ( col >= 0 && row >= 0 && col < MAP_MAX_NCOLS && row < MAP_MAX_NROWS ) ;

   return valid;
}

void set_cell_passable( int col, int row, bool passable )
{
   map[ col ][ row ].passable = passable;
}

void set_cell_entity( int col, int row, int entity )
{
   map[ col ][ row ].entity = entity;
}

void clear_cell_entity( int col, int row )
{
   map[ col ][ row ].entity = NO_ENTITY;
}

bool is_cell_empty( int col, int row )
{
   return valid_map_location( col, row ) && map[ col ][ row ].type == type_uninit &&
          map[ col ][ row ].entity == NO_ENTITY;
}

static void set_cell_uninit( int col, int row )
{
   map[ col ][ row ].type = type_uninit;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
   map[ col ][ row ].entity = NO_ENTITY;
   map[ col ][ row ].passable = true;
}

static void set_cell_static( int col, int row, char cell, bool passable )
{
   map[ col ][ row ].type = type_static;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
   map[ col ][ row ].u.static_map.cell = cell;
   map[ col ][ row ].passable = passable;
}

static void set_cell_dynamic( int col, int row, int state_cnt, char *states, int delay, bool passable )
{
   map[ col ][ row ].type = type_dynamic;
   map[ col ][ row ].location.col = col;
   map[ col ][ row ].location.row = row;
   map[ col ][ row ].u.dynamic_map.delay = delay;
   map[ col ][ row ].u.dynamic_map.cur_delay = 0;
   map[ col ][ row ].u.dynamic_map.state = 0;
   map[ col ][ row ].u.dynamic_map.max_state = state_cnt;
   map[ col ][ row ].passable = passable;

   for ( int i = 0 ; i < state_cnt ; i++ )
   {
      map[ col ][ row ].u.dynamic_map.cells[ i ] = states[ i ];
   }

   return;
}

bool passable( int col, int row )
{
   if ( col < 0 || col > MAP_MAX_NCOLS-1 || row < 0 || row > MAP_MAX_NROWS-1 ) return false;
   return ( map[ col ][ row ].passable && map[ col ][ row ].entity == NO_ENTITY );
}

chtype get_cell( int col, int row )
{
   if ( !valid_map_location( col, row ) )
   {
      // Void space (outside of the map).
      return '~';
   }
   else if ( map[ col ][ row ].entity != NO_ENTITY )
   {
      return get_entity_render( map[ col ][ row ].entity );
   }

   switch ( map[ col ][ row ].type )
   {
      case type_uninit:
         return ' ';
         break;

      case type_static:
         return map[ col ][ row ].u.static_map.cell;
         break;

      case type_dynamic:
         if ( map[ col ][ row ].u.dynamic_map.cur_delay < map[ col ][ row ].u.dynamic_map.delay )
         {
            map[ col ][ row ].u.dynamic_map.cur_delay++;
         }
         else
         {
            map[ col ][ row ].u.dynamic_map.cur_delay = 0;
            if ( ++map[ col ][ row ].u.dynamic_map.state >= map[ col ][ row ].u.dynamic_map.max_state )
            {
               map[ col ][ row ].u.dynamic_map.state = 0;
            }
         }
         return map[ col ][ row ].u.dynamic_map.cells[ map[ col ][ row ].u.dynamic_map.state ];
         break;

      default:
         assert( 0 );
         break;
   }
   
   // Will not reach.
   return '!';
}

static void place_gas_cloud( int col, int row )
{
   int c, r, l;
   int num_rays = 20;
   const int ray_len  = 80;

   do 
   {
      col += getRand( MAPWIN_COL_SIZE );
      row += getRand( MAPWIN_ROW_SIZE );
   } 
   while ( !map[ col ][ row ].type == type_uninit );

   while ( num_rays-- > 0 )
   {
      c = col; r = row;
      l = ray_len;

      while ( l > 0 )
      {
         int delta = getRand( 4 );
         int cd = deltas[delta].col;
         int rd = deltas[delta].row;

         if ( valid_map_location( c + cd, r + rd ) )
         {
            c += cd; r += rd;
            set_cell_static( c, r, '#', false );
            l--;
         }

      }

   }
   
   return;
}

static void clean_up_gas_clouds( void )
{
   int iterations = get_gas_smoothing_iters( get_level( ) );

   while ( iterations-- )
   {
      for ( int row = 1 ; row < MAP_MAX_NROWS-2 ; row++ )
      {
         for ( int col = 1 ; col < MAP_MAX_NCOLS-2 ; col++ )
         {
            unsigned int count = 0;
            for ( int r = -1 ; r < 2 ; r++ )
            {
               for ( int c = -1 ; c < 2 ; c++ )
               {
                  if ( get_cell( col+c, row+r ) == '#' ) count++;
               }
            }

            if ( get_cell( col, row ) == '#' )
            {
               if ( count <= get_gas_smoothing_param( get_level( ) ) ) set_cell_uninit( col, row );
            }
            else if ( get_cell( col, row ) == ' ' )
            {
               if ( count >= get_gas_smoothing_filler_param( get_level( ) ) )
               {
                  set_cell_static( col, row, '#', false );
               }
            }
         }
      }
   }

   return;
}

static void place_map_entry_exit( void )
{
   int col = 10;
   int row = ( MAP_MAX_NROWS >> 1 );

   // Generate the entry gate for all but the first level.
   if ( get_level( ) > 0 )
   {
      // Ensure that there's an open path to the star gate.
      for ( int i = 0 ; i < 20 ; i++ ) set_cell_uninit( col+i, row );

      for ( int i = 0 ; i < 14 ; i++ ) set_cell_static( col+i, row-1, '=', false );
      set_cell_dynamic( col+1,  row, 4, "|/-\\", 50, false );
      set_cell_dynamic( col+3,  row, 6, ">     ", 30, true );
      set_cell_static(  col+4,  row, ' ', false );
      set_cell_dynamic( col+5,  row, 6, " >    ", 30, false );
      set_cell_static(  col+6,  row, ' ', false );
      set_cell_dynamic( col+7,  row, 6, "  >   ", 30, false );
      set_cell_static(  col+8,  row, ' ', false );
      set_cell_dynamic( col+9,  row, 6, "   >  ", 30, false );
      set_cell_static(  col+10, row, ' ', false );
      set_cell_dynamic( col+11, row, 6, "    > ", 30, false );
      set_cell_static(  col+12, row, ' ', false );
      set_cell_dynamic( col+13, row, 6, "     >", 30, false );
      for ( int i = 0 ; i < 14 ; i++ ) set_cell_static( col+i, row+1, '=', false );
   }

   if ( get_level( ) != get_max_level( ) )
   {
      col = MAP_MAX_NCOLS - 20;
      row = ( MAP_MAX_NROWS >> 1 );

      // Ensure that there's an open path to the star gate.
      for ( int i = 0 ; i < 20 ; i++ ) set_cell_uninit( col-i, row );

      // TODO: Put [Ex/it] above gate.
      for ( int i = 0 ; i < 14 ; i++ ) set_cell_static( col+i, row-1, '=', false );
      set_cell_dynamic(  col,    row, 6, ">     ", 30, true );
      set_cell_dynamic(  col+2,  row, 6, " >    ", 30, false );
      set_cell_dynamic(  col+4,  row, 6, "  >   ", 30, false );
      set_cell_dynamic(  col+6,  row, 6, "   >  ", 30, false );
      set_cell_dynamic(  col+8,  row, 6, "    > ", 30, false );
      set_cell_dynamic(  col+10, row, 6, "     >", 30, false );
      set_cell_dynamic(  col+12, row, 4, "|/-\\",  10, false );
      for ( int i = 0 ; i < 14 ; i++ ) set_cell_static( col+i, row+1, '=', false );
   }

   return;
}

void get_exit_location( int *col, int *row )
{
    *col = MAP_MAX_NCOLS - 20;
    *row = MAP_MAX_NROWS >> 1;

    return;
}

static void init_map_assets( void )
{
    // Place gas-clouds randomly in the level.
    for ( int sector_row = 0 ; sector_row < MAP_SEC_NROWS ; sector_row++ )
    {
        for ( int sector_col = 0 ; sector_col < MAP_SEC_NCOLS ; sector_col++ )
        {
            // Don't place anything in the first an last col sector in the middle row sector
            if ( !( (sector_row == 1) && ( (sector_col == 0) || (sector_col == MAP_MAX_NCOLS-1) ) ) )
            {
               place_gas_cloud( sector_col * MAPWIN_COL_SIZE, sector_row * MAPWIN_ROW_SIZE );
            }
        }

    }

    clean_up_gas_clouds( );

    place_map_entry_exit( );

    return;
}

static void clear_map( void )
{
   memset( map, 0, sizeof( map ) );

   for ( int row = 0 ; row < MAP_MAX_NROWS ; row++ )
   {
      for ( int col = 0 ; col < MAP_MAX_NCOLS ; col++ )
      {
         set_cell_uninit( col, row );
         clear_cell_entity( col, row );
      }
   }

   return;
}

void init_map( void )
{
   clear_map( );

   init_map_assets( );

#if 0
   set_cell_dynamic( 10, 10, 4, "^>v<", 87, false );
   set_cell_dynamic( 10, 12, 4, "O0o.", 74, false );

   int col = 10;
   int row = ( MAP_MAX_NROWS >> 1 ) - 2;
   set_cell_static(  col, row, '[', false );
   set_cell_dynamic( col+1, row, 8, "Danger! ", 20, false );
   set_cell_dynamic( col+2, row, 8, "anger!  ", 20, false );
   set_cell_dynamic( col+3, row, 8, "nger!   ", 20, false );
   set_cell_static(  col+4, row, ']', false );
#endif

}

