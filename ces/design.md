# CES Design for BorgRL

BorgRL will use a simple component-entity-system to drive the behaviors of objects in its universe.

## Entity

An entity is an ID that refers to a cross section of components.  Not all components are used for each entity.

## Components

Components are the attributes of entities (such as location, target, energy (HP), etc.).

```
typedef enum
{
   COMP_LOCATION = 1,
   COMP_TARGET = 2,
   COMP_HP = 4,

} components_t;
```

Initial components are:

```
typedef struct
{
   int col;
   int row;
} comp_location;
```

```
typedef struct
{
   int target_col;
   int target_row;
} comp_target_next_step;
```

```
typedef struct
{
   int energy;
} comp_energy;
```


## Systems

SYSTEM_MOVEMENT,
SYSTEM_USER_INPUT,



