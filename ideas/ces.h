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
} component_health_t;

typedef struct component_attack
{
    int value;
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

typedef struct render
{
   char cell;
   int  color;
} component_render_t;

typedef enum
{
    COMPONENT_NONE       = 0,
    COMPONENT_USER_INPUT = 1 << 1,
    COMPONENT_LOCATION   = 1 << 2,
    COMPONENT_HEALTH     = 1 << 3,
    COMPONENT_ATTACK     = 1 << 4,
    COMPONENT_MOVEMENT   = 1 << 5,
    COMPONENT_XP         = 1 << 6,
    COMPONENT_RESOURCES  = 1 << 7,
    COMPONENT_TARGET     = 1 << 8,
    COMPONENT_RENDER     = 1 << 9,
    // ...

} Component;

#define NUMBER_OF_BORG        1
#define NUMBER_OF_WRECKS     20
#define NUMBER_OF_DRONES     30
#define NUMBER_OF_PLANETS     6
#define NUMBER_OF_STARBASES   1

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

} World;

void init_entities( );

#endif // __COMPONENT_H__

