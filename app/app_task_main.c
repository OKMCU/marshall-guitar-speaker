/******************************************************************************

 @file  app_task_main.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/

/**************************************************************************************************
 * INCLUDES
 **************************************************************************************************/
#include "osal.h"
#include "hal.h"
#include "app.h"

#include "main.h"
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/


/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
extern void app_task_main_init( void )
{
    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_POR );
}


extern void app_task_main ( uint8_t task_id, uint8_t event_id )
{
    switch (event_id)
    {
        case TASK_EVT_APP_MAIN_POR:
        {
            app_event_main_por();
        }
        break;


        case TASK_EVT_APP_MAIN_OSAL_EXCEPTION:
        {
            hal_cli_print_str( "ERROR!\r\n" );
            hal_cli_print_str( "OSAL_EXCEPTION!\r\n" );
        }
        break;

        case TASK_EVT_APP_MAIN_HAL_EXCEPTION:
        {
            hal_cli_print_str( "ERROR!\r\n" );
            hal_cli_print_str( "HAL EXCEPTION!\r\n" );
        }
        break;

        case TASK_EVT_APP_MAIN_APP_EXCEPTION:
        {
            hal_cli_print_str( "ERROR!\r\n" );
            hal_cli_print_str( "APP EXCEPTION!\r\n" );
        }
        break;

        case TASK_EVT_APP_MAIN_IDLE_PROCESS:
        {
            app_event_main_idle_process();
            osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_IDLE_PROCESS );
        }
        break;
        

        default:
            APP_ASSERT_FORCED();
        break;
    }
}



/**************************************************************************************************
**************************************************************************************************/

