// ces.h

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

typedef struct component_location
{
    double col;
    double row;
} component_location_t;

typedef struct component_health
{
    int value;
    int max_health;
} component_health_t;

typedef struct component_attack
{
    int value;
    int armor;
} component_attack_t;

typedef enum
{
   TYPE_TARGET = 0,
   TYPE_ORBIT  = 1,
} cmovement_type;

typedef struct component_movement
{
    int speed;
    int state;
    cmovement_type type;
} component_movement_t;

typedef struct component_xp
{
    int value;
    int xp2nextlevel;
    int level;
} component_xp_t;

typedef struct component_resources
{
    int value;
} component_resources_t;

typedef struct component_target
{
    int dCol; // dY
    int dRow; // dX
    int distance;
    int entity_id;
} component_target_t;

typedef struct component_render
{
   char cell;
   int  attr;
} component_render_t;

typedef struct component_sdrone
{
   int capacity;
   int max_capacity;
   int scav_speed;
} component_sdrone_t;

typedef void (*on_verb_callback)( int dest_entity, int source_entity );

typedef struct entity_callbacks
{
   on_verb_callback on_attack; // source_entity attacks dest_entity.
   on_verb_callback on_death;  // dest_entity killed by source_entity.
} entity_callbacks_t;

typedef enum
{
    COMPONENT_NONE       = 0,
    COMPONENT_USER_INPUT = 1 <<  0,
    COMPONENT_LOCATION   = 1 <<  1,
    COMPONENT_HEALTH     = 1 <<  2,
    COMPONENT_ATTACK     = 1 <<  3, // Enemy Combat Drone Attack
    COMPONENT_MOVEMENT   = 1 <<  4,
    COMPONENT_XP         = 1 <<  5,
    COMPONENT_RESOURCES  = 1 <<  6,
    COMPONENT_TARGET     = 1 <<  7,
    COMPONENT_RENDER     = 1 <<  8,
    COMPONENT_PLAYER     = 1 <<  9,
    COMPONENT_FRIENDLY   = 1 << 10,
    COMPONENT_ENEMY      = 1 << 11,
    COMPONENT_CDRONE     = 1 << 12, // Combat Drone
    COMPONENT_MDRONE     = 1 << 13, // Mining Drone
    COMPONENT_SDRONE     = 1 << 14, // Scavenger Drone
    // ...

} Component;

#define NUMBER_OF_BORG        1
#define NUMBER_OF_WRECKS     20
#define NUMBER_OF_DRONES     30
#define NUMBER_OF_PLANETS     6
#define NUMBER_OF_STARBASES   1

#define NO_ENTITY            -1

#define MAX_ENTITIES \
            ( NUMBER_OF_BORG + NUMBER_OF_WRECKS + NUMBER_OF_DRONES + \
              NUMBER_OF_PLANETS + NUMBER_OF_STARBASES )

typedef struct World
{
    int mask[ MAX_ENTITIES ];

    int id  [ MAX_ENTITIES ];

    component_location_t   location  [ MAX_ENTITIES ];
    component_health_t     health    [ MAX_ENTITIES ];
    component_attack_t     attack    [ MAX_ENTITIES ];
    component_movement_t   movement  [ MAX_ENTITIES ];
    component_xp_t         xp        [ MAX_ENTITIES ];
    component_resources_t  resources [ MAX_ENTITIES ];
    component_target_t     target    [ MAX_ENTITIES ];
    component_render_t     render    [ MAX_ENTITIES ];
    component_sdrone_t     scavdrone [ MAX_ENTITIES ];
    entity_callbacks_t     callbacks [ MAX_ENTITIES ];

} World;

void init_entities( );
chtype get_entity_render( int entity );
void   create_wreck_entity( int col, int row, int resources );
bool   get_player_inv( int entity, char *object, char *state, int *level, int *hp, int *max_hp );

#endif // __COMPONENT_H__


