// ces.c
#include "headers.h"
#include "ces.h"

World world;

int get_entity_at( int col, int row )
{
    int entity;

    for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
    {
        if ( world.mask[ entity ] != COMPONENT_NONE )
        {
            if ( world.location[ entity ].col == col && world.location[ entity ].row == row )
            {
                return entity;
            }
        }
    }

    return NO_ENTITY;
}

int get_free_entity( void )
{
    int entity;

    for ( entity = 1 ; entity < MAX_ENTITIES ; entity++ )
    {
        if ( world.mask[ entity ] == COMPONENT_NONE ) break;
    }

    return entity;
}

void destroy_entity( int entity )
{
    world.mask[ entity ] = COMPONENT_NONE;

    return;
}

void find_empty_space( int col_sec, int row_sec, int *col, int *row )
{
    while ( 1 )
    {
        *col = col_sec * MAPWIN_COL_SIZE + getRand( MAPWIN_COL_SIZE );
        *row = row_sec * MAPWIN_ROW_SIZE * getRand( MAPWIN_ROW_SIZE );

        if ( is_cell_empty( *col, *row ) )
        {
            break;
        }
    }

    return;
}

void next_level( int dest_entity, int source_entity )
{
   ( void )dest_entity;
   if ( source_entity == 0 )
   {
      void cleanup_entities( void );
      void create_map_entities( void );

      cleanup_entities( );

      inc_level( );
      init_map( );

      create_map_entities( );

      clear_cell_entity( world.location[ source_entity ].col, world.location[ source_entity ].row );
      set_player_col( PLAYER_COL_START );
      set_player_row( PLAYER_ROW_START );
      set_cell_entity( world.location[ source_entity ].col, world.location[ source_entity ].row, source_entity );

      if ( get_level( ) < get_max_level( ) )
      {
          add_message( "You've entered the next sector." );
      }
      else
      {
          add_message( "Welcome to the final level." );
      }
   }

   return;
}

void create_exit_entity( void )
{
    int entity = get_free_entity( );
    int col, row;

    get_exit_location( &col, &row );

    // Create the exit entity with an on_attack callback.
    world.id[ entity ] = entity;
    world.mask[ entity ] = COMPONENT_LOCATION;
    world.location[ entity].col = col;
    world.location[ entity].row = row;

    set_cell_entity( col, row, entity );

    world.callbacks[ entity ].on_attack = &next_level;

    return;
}

void create_wreck_entity( int col, int row, int resources )
{
    int entity = get_free_entity( );
    
    // Create a wreck entity
    world.id[ entity ] = entity;
    world.mask[ entity ] = COMPONENT_LOCATION | COMPONENT_RENDER | COMPONENT_RESOURCES;

    world.resources[ entity ].value = resources;

    world.location[ entity ].col = col;
    world.location[ entity ].row = row;

    set_cell_entity( col, row, entity );

    world.render[ entity ].cell = '%';
    world.render[ entity ].attr = COLOR_PAIR( COLOR_WRECK );

    return;
}

void create_cedrone_entity( int col, int row, int resources, int health, int speed, int attack, int xp )
{
   (void)col; (void)row; (void)resources; (void)health; (void)speed; (void)attack; (void)xp;
}

void set_entity_render( int entity )
{
    world.mask[ entity ] |= COMPONENT_RENDER;
}

void reset_entity_render( int entity )
{
    world.mask[ entity ] &= ~COMPONENT_RENDER;
}

void create_sdrone_entity( int health, int speed, int max_capacity, int scav_speed )
{
    int entity;

    entity = get_free_entity( );
    
    // Create a scaveger drone entity
    world.id[ entity ] = entity;
    world.mask[ entity ] = COMPONENT_FRIENDLY | COMPONENT_SDRONE | COMPONENT_LOCATION | 
                           COMPONENT_HEALTH   | COMPONENT_TARGET;

    // COMPONENT_RENDER is added once the drone is undocked.

    world.location[ entity ].col = 0;
    world.location[ entity ].row = 0;

    world.health[ entity ].value = health;
    world.health[ entity ].max_health = health;

    world.movement[ entity ].speed = speed;
    world.movement[ entity ].type = TYPE_TARGET;
    world.movement[ entity ].state = 0; // TODO

    world.health[ entity ].value = health;
    world.health[ entity ].max_health = health;

    world.xp[ entity ].level = 1;

    world.scavdrone[ entity ].capacity = 0;
    world.scavdrone[ entity ].max_capacity = max_capacity;
    world.scavdrone[ entity ].scav_speed = scav_speed;

    set_cell_entity( world.location[ entity ].col, world.location[ entity ].row, entity );

    world.render[ entity ].cell = 'S';
    world.render[ entity ].attr = 0;

    return;
}

chtype get_entity_render( int entity )
{
    chtype ch;
    if ( world.mask[ entity ] & COMPONENT_RENDER )
    {
        ch = world.render[ entity ].cell | world.render[ entity ].attr;
    }
    else
    {
        ch = ' ';
    }

    return ch;
}

void create_player_entity( )
{
    int entity;

    entity = 0; // get_free_entity( );

    // Create the player entity
    world.id[ entity ] = entity;
    world.mask[ entity ] = COMPONENT_LOCATION | COMPONENT_USER_INPUT | COMPONENT_HEALTH |
                           COMPONENT_ATTACK | COMPONENT_MOVEMENT |
                           COMPONENT_RENDER | COMPONENT_PLAYER;

    world.location[ entity ].col = PLAYER_COL_START;
    world.location[ entity ].row = PLAYER_ROW_START;

    world.xp[ entity ].level = 1;

    world.health[ entity ].value = 5;
    world.health[ entity ].max_health = 5;

    world.render[ entity ].cell = '@';
    world.render[ entity ].attr = COLOR_PAIR( COLOR_BORG ) | A_BOLD;

    set_cell_entity( world.location[ entity ].col, world.location[ entity ].row, entity );

    return;
}

int get_player_col( void )
{
    return world.location[ 0 ].col;
}

int get_player_row( void )
{
    return world.location[ 0 ].row;
}

void set_player_col( int col )
{
    world.location[ 0 ].col = col;
}

void set_player_row( int row )
{
    world.location[ 0 ].row = row;
}

static void place_wreck( int col, int row )
{
    int coff, roff;
    do
    {
        coff = getRand( MAPWIN_COL_SIZE );
        roff = getRand( MAPWIN_ROW_SIZE );
    }
    while( !is_cell_empty( col+coff, row+roff ) );

    create_wreck_entity( col+coff, row+roff, get_wreck_resources( get_level( ) ) );

    return;
}

void create_map_entities( void )
{
    // Create wrecks in the environment.
    int wrecks = get_wreck_count( get_level( ) );

    while ( wrecks )
    {
        int sector_col = getRand( MAP_SEC_NCOLS );
        int sector_row = getRand( MAP_SEC_NROWS );

        place_wreck( sector_col * MAPWIN_COL_SIZE, sector_row * MAPWIN_ROW_SIZE );
        wrecks--;
    }

    // Other entity creation.

    // Create map exit entity.
    if ( get_level( ) < get_max_level( ) )
    {
        create_exit_entity( );
    }

    return;
}

// Remove all entities that are not player and friendly.
void cleanup_entities( void )
{
    // Skip offset 0 which is the player (Borg)
    for ( int entity = 1 ; entity < MAX_ENTITIES ; entity++ )
    {
        if ( world.mask[ entity ] & COMPONENT_FRIENDLY )
        {
            if ( world.mask[ entity ] & COMPONENT_RENDER )
            {
                // Only save drones that are docked (RENDER means undocked...).
                destroy_entity( entity );
            }
        }
        else
        {
            destroy_entity( entity );
        }
    }

    return;
}

static void create_entities( void )
{
    if ( get_level( ) == 0 )
    {
        // Player is first (entity 0).
        create_player_entity( );
        create_sdrone_entity( 2, 1, 4, 1 );
    }

    create_map_entities( );

    return;
}

void init_entities( void )
{
    int entity;

    for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
    {
        destroy_entity( entity );
    }

    create_entities( );

    return;
}

bool get_player_inv( int entity, char *object, char *state, int *lvl, int *hp, int *max_hp )
{
    bool status = false;

    *lvl = world.xp[ entity ].level;
    *hp  = world.health[ entity ].value;
    *max_hp = world.health[ entity ].max_health;

    // TODO: Add player, combat drone, etc.
    if ( world.mask[ entity ] & COMPONENT_SDRONE )
    {
        strcpy( object, "Scavenger " );

        if ( world.mask[ entity ] & COMPONENT_RENDER )
        {
            strcpy( state, "Undocked  " );
        }
        else
        {
            strcpy( state, "Docked    " );
        }

        status = true;
    }
    else if ( world.mask[ entity ] & COMPONENT_PLAYER )
    {
        strcpy( object, "Borg [@]  " );
        strcpy( state, "Operating " );

        status = true;
    }

    return status;
}


// Migrate this into systems for general use...
void player_move( int cold, int rowd )
{
   location_t player_loc;

   player_loc.col = get_player_col( );
   player_loc.row = get_player_row( );

   // First, check to see if an entity is in the new location.
   int entity = get_entity_at( player_loc.col - cold, player_loc.row - rowd );

   if ( entity != NO_ENTITY )
   {
      if ( world.callbacks[ entity ].on_attack != ( on_verb_callback) 0 )
      {
         (world.callbacks[ entity ].on_attack)( entity, 0 );
      }

      return;
   }

   if ( !passable( player_loc.col - cold, player_loc.row - rowd ) )
   {
      return;
   }

   clear_cell_entity( player_loc.col, player_loc.row );

   player_loc.row -= rowd;
   player_loc.col -= cold;

   if ( player_loc.row < 0 )
   {
      player_loc.row = 0;
   }
   else if ( player_loc.col < 0 )
   {
      player_loc.col = 0;
   }
   else if ( player_loc.row >= MAP_MAX_NROWS )
   {
      player_loc.row = MAP_MAX_NROWS - 1;
   }
   else if ( player_loc.col >= MAP_MAX_NCOLS )
   {
      player_loc.col = MAP_MAX_NCOLS - 1;
   }

   set_player_col( player_loc.col );
   set_player_row( player_loc.row );

   set_cell_entity( player_loc.col, player_loc.row, 0 );

   return;
}

void target_system( void  )
{
   // iterate enemie drones.
   //   if a drone is within X distance to player, the attack (set target to player or drone loc).
}

void move_system( void )
{
   // given a target exists for the entity, a* to that target and move one step.

}
