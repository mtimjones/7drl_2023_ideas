#include "headers.h"

#define MAX_STATES 8

typedef enum
{
   type_static,
   type_dynamic,
} type_t;

typedef struct
{
   char cell;
} static_map_t;

typedef struct
{
   int state;
   int max_state;
   int cells[ MAX_STATES ];
} dynamic_map_t;

typedef struct
{
   type_t type;

   union {
      static_map_t static_map;
      dynamic_map_t dynamic_map;
   } u;

   location_t location;

   bool visited;
   bool passable;
   // bool visible; // Computed dynamically

   // entity_id_t entity; // handled dynamically with a rendering order.

} cell_t;

