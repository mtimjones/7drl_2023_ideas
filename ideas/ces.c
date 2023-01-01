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

    return entity;
}

int get_free_entity( void )
{
    int entity;

    for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
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

        if ( is_map_empty( *col, *row ) && get_entity_at( *col, *row ) == MAX_ENTITIES )
        {
            break;
        }
    }

    return;
}

void create_wreck_entity( int resources )
{
    int col, row, entity;

    // Find an empty spot within this sector
    find_empty_space( getRand( MAP_SEC_NCOLS ), getRand( MAP_SEC_NROWS ), &col, &row );
    
    add_message(" Added wreck at %d, %d", col, row );

    entity = get_free_entity( );
    
    // Create a wreck entity
    world.id[ entity ] = entity;
    world.mask[ entity ] = COMPONENT_LOCATION | COMPONENT_RENDER | COMPONENT_RESOURCES;

    world.resources[ entity ].value = resources;

    world.location[ entity ].col = 0; //col;
    world.location[ entity ].row = 0; //row;

    world.render[ entity ].cell = '%';
    world.render[ entity ].attr = COLOR_PAIR( COLOR_WRECK );

    return;
}

#if 0
void create_player_entity( )
{
    int col, row, entity;

    entity = get_free_entity( );

    // Create the player entity
    world.id[ entity ] = entity;
    world.mask[ entity ] = COMPONENT_LOCATION | COMPONENT_USER_INPUT | COMPONENT_HEALTH |
                           COMPONENT_ATTACK | COMPONENT_MOVEMENT | COMPONENT_TARGET |
                           COMPONENT_RENDER;

    world.location[ entity ].col = 
    world.location[ entity ].row =

    world.health[ entity ].value =

    world.render[ entity ].attr = COLOR_PAIR( COLOR_BORG ) | A_BOLD;


#endif

void init_entities( void )
{
    int entity;

    for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
    {
        destroy_entity( entity );
    }

    create_wreck_entity( 5 );

    return;
}

void render_system( void  )
{
    int entity;
    int mask = COMPONENT_LOCATION | COMPONENT_RENDER;
    int scol, srow;

    // Offset 0,0 of the map in full coordinates.
    scol = get_player_col( ) - ( ( MAPWIN_COL_SIZE-2 ) >> 1 ) - 1;
    srow = get_player_row( ) - ( ( MAPWIN_ROW_SIZE-2 ) >> 1 ) - 1;

    add_message( "Player %d/%d, Scol = %d, Srow = %d", get_player_col(), get_player_row(), scol, srow );

    for ( entity = 0 ; entity < MAX_ENTITIES ; entity++ )
    {
        // If this entity is renderable
        if ( ( world.mask[ entity ] & mask ) == mask )
        {
add_message( "Entity %d loc %d/%d", entity, world.location[ entity ].col, world.location[entity].row);
            // If this entity's location is in the current map view
            if ( world.location[ entity ].col >= scol                   &&
                 world.location[ entity ].col < scol+MAPWIN_COL_SIZE-2  &&
                 world.location[ entity ].row >= srow                   &&
                 world.location[ entity ].row < srow+MAPWIN_ROW_SIZE-2 )
            {
//                put_char( scol - world.location[ entity ].col,
//                          srow - world.location[ entity ].row,
                put_char( world.location[ entity ].col+scol,
                          world.location[ entity ].row+srow,
                          world.render[ entity ].cell,
                          world.render[ entity ].attr );
            }
        }
    }

    return;
}
