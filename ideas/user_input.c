#include "headers.h"

static enum ActionState action_state = NoState;

static void emit_help( )
{
   init_msg_log( );

   add_message( "Move the Borg with the arrow keys.  Use the mouse to select actions (or press their key)." );
   add_message( "Some actions require selecting a target.  You can also select a drone and then a target" );
   add_message( "to perform it's action (for example, select a combat drone and then an enemy on the map)." );
   add_message( "Make your way to the right side of the sector to escape to the next.  Good luck." );

}

enum ActionState get_action_state( void )
{
   return action_state;
}

void handle_user_input( void )
{
   int c;
   MEVENT event;

   // Check keyboard input.
   c = get_user_char( );

   if ( c == 0 )
   {
      // No character received.
      return;
   }
   else if ( c == KEY_MOUSE )
   {
      // Handle mouse event.
      if ( getmouse( &event ) == OK )
      {
          // Temporary...
          add_message( "Mouse at %d, %d, %d", event.x, event.y, event.z );

          // Check to see if the context needs to be updated (based upon mouse position).
          if ( event.x >= LOGWIN_COL_START && 
               event.x < (LOGWIN_COL_START+LOGWIN_COL_SIZE) && 
               event.y >= LOGWIN_ROW_START && 
               event.y < (LOGWIN_ROW_START+LOGWIN_ROW_SIZE) )
          {
              set_context( "Log window..." );
          }
          else if ( event.x >= MAPWIN_COL_START && 
                    event.x < (MAPWIN_COL_START+MAPWIN_COL_SIZE) && 
                    event.y >= MAPWIN_ROW_START && 
                    event.y < (MAPWIN_ROW_START+MAPWIN_ROW_SIZE) )
          {
              set_context( "Map window showing your surroundings." );
          }
          else if ( event.x >= INVWIN_COL_START && 
                    event.x < (INVWIN_COL_START+INVWIN_COL_SIZE) && 
                    event.y >= INVWIN_ROW_START && 
                    event.y < (INVWIN_ROW_START+INVWIN_ROW_SIZE) )
          {
              set_context( "Inventory window showing drones and their attributes." );
          }
          else if ( event.x >= STATSWIN_COL_START && 
                    event.x < (STATSWIN_COL_START+STATSWIN_COL_SIZE) && 
                    event.y >= STATSWIN_ROW_START && 
                    event.y < (STATSWIN_ROW_START+STATSWIN_ROW_SIZE) )
          {
              set_context( "Stats window showing various game resources and Borg upgrades." );
          }
          else if ( event.x >= ACTIONSWIN_COL_START && 
                    event.x < (ACTIONSWIN_COL_START+ACTIONSWIN_COL_SIZE) && 
                    event.y >= ACTIONSWIN_ROW_START &&
                    event.y < (ACTIONSWIN_ROW_START+ACTIONSWIN_ROW_SIZE) )
          {
              set_context( "Actions window..." );
          }
          else
          {
              // If the mouse position isn't in a contextual area, ignore it and clear context.
              clear_context( );
          }


          // Handle mouse clicks
          if ( event.bstate == BUTTON1_PRESSED )
          {


          }


      }
   }
   else
   {
      switch( c )
      {
         case 'x':
            end_game( );
            break;
         case '?':
            emit_help( );
            break;
         case 'h':
            // Enter the heal state
            action_state = HealState;
            break;
         case 27: // Esc
            action_state = NoState;
            break;
         default:
            break;
      }
   }

   return;
}

