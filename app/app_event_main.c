/******************************************************************************

 @file  app_event_main.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

/**************************************************************************************************
 * INCLUDES
 **************************************************************************************************/
#include "osal.h"
#include "hal.h"
#include "app.h"

#include "main.h"

#include <string.h>
#include "stringx.h"
/**************************************************************************************************
 * TYPE DEFINES
 **************************************************************************************************/

 /**************************************************************************************************
 * LOCAL API DECLARATION
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/

extern void app_event_main_por( void )
{
    hal_cli_print_str( "\r\nThis is OSAL demo project on Nuvoton 8051 series MCU.\r\n" );
    hal_cli_print_str( "Power on reset.\r\n" );

    hal_cli_print_str( "Firmware Version " );
    hal_cli_print_str( FIRMWARE_VER );
    hal_cli_print_str( "\r\n" );

    hal_cli_print_str( "Hardware Version " );
    hal_cli_print_str( HARDWARE_VER );
    hal_cli_print_str( "\r\n" );

    hal_vr_init();
    hal_ms6715_init();
    hal_ms6715_set_vol( HAL_MS6715_VOL_MAX );
    hal_ms6715_set_voll( HAL_MS6715_VOL_LR_MAX );
    hal_ms6715_set_volr( HAL_MS6715_VOL_LR_MAX );
    hal_ms6715_set_loudness( HAL_MS6715_LOUDNESS_ON );

    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_READ_VR );
}

extern void app_event_main_read_vr( void )
{
    uint16_t u16tmp;
    
    u16tmp = hal_vr_read( HAL_VR_0 );
    //hal_cli_print_str( "VR0=" );
    //hal_cli_print_uint( u16tmp );
    //hal_cli_print_str( ";" );
    u16tmp = hal_vr_read( HAL_VR_1 );
    //hal_cli_print_str( "VR1=" );
    //hal_cli_print_uint( u16tmp );
    //hal_cli_print_str( "\r\n" );
    
    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_READ_VR );
}

/**************************************************************************************************
**************************************************************************************************/

