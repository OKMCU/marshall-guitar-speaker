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
static int8_t vr_pos_2_tb_level( uint16_t vr_pos );

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/
#define VR_POS_DEBOUNCE_TOLERANCE   10

/**************************************************************************************************
 * MACROS
 **************************************************************************************************/
#define VR_POS_IIR( x, y )         (uint16_t)(((uint32_t)x*31+(uint32_t)y)>>5)  //31:1 IIR filter

/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static code uint16_t tb_level_lut[16] = {
    0,      //-7, must be 0
    273,    //-6
    546,    //-5
    819,    //-4
    1092,   //-3
    1365,   //-2
    1638,   //-1
    1911,   // 0
    2184,   //+1
    2457,   //+2
    2730,   //+3
    3003,   //+4
    3276,   //+5
    3549,   //+6
    3822,   //+7
    4095    //must be 4095
};




extern void app_event_main_por( void )
{
    hal_cli_print_str( "\r\nThis is Marshall Guitar Speaker project.\r\n" );
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
    hal_ms6715_set_bass( 0 );
    hal_ms6715_set_treble( 0 );

    app_info.bass_level = 0;
    app_info.treble_level = 0;
    app_info.bass_vr_pos = 0;
    app_info.treble_vr_pos = 0;

    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_IDLE_PROCESS );
}

extern void app_event_main_idle_process( void )
{
    uint16_t vr_pos;
    int8_t tb_level;
    uint8_t flag;

    //Check BASS level
    flag = 0;
    vr_pos = hal_vr_read( HAL_VR_0 );
    app_info.bass_vr_pos = VR_POS_IIR( app_info.bass_vr_pos, vr_pos );
    tb_level = vr_pos_2_tb_level( app_info.bass_vr_pos );
    if( tb_level > app_info.bass_level )
    {
        if( app_info.bass_vr_pos - tb_level_lut[tb_level+HAL_MS6715_TB_MAX] > VR_POS_DEBOUNCE_TOLERANCE )
        {
            flag = 1;
        }
    }
    else if( tb_level < app_info.bass_level )
    {
        if( tb_level_lut[app_info.bass_level+HAL_MS6715_TB_MAX] - app_info.bass_vr_pos > VR_POS_DEBOUNCE_TOLERANCE )
        {
            flag = 2;
        }
    }

    if( flag )
    {
        app_info.bass_level = tb_level;
        hal_cli_print_str( "BASS_LEVEL=" );
        hal_cli_print_sint( app_info.bass_level );
        hal_cli_print_str( ";" );
        hal_cli_print_str( "BASS_VR_POS=" );
        hal_cli_print_uint( app_info.bass_vr_pos );
        hal_cli_print_str( ".\r\n" );
        hal_ms6715_set_bass( app_info.bass_level );
    }

    //Check TREBLE level
    flag = 0;
    vr_pos = hal_vr_read( HAL_VR_1 );
    app_info.treble_vr_pos = VR_POS_IIR( app_info.treble_vr_pos, vr_pos );
    tb_level = vr_pos_2_tb_level( app_info.treble_vr_pos );
    if( tb_level > app_info.treble_level )
    {
        if( app_info.treble_vr_pos - tb_level_lut[tb_level+HAL_MS6715_TB_MAX] > VR_POS_DEBOUNCE_TOLERANCE )
        {
            flag = 1;
        }
    }
    else if( tb_level < app_info.treble_level )
    {
        if( tb_level_lut[app_info.treble_level+HAL_MS6715_TB_MAX] - app_info.treble_vr_pos > VR_POS_DEBOUNCE_TOLERANCE )
        {
            flag = 2;
        }
    }
    
    if( flag )
    {
        app_info.treble_level = tb_level;
        hal_cli_print_str( "TREBLE_LEVEL=" );
        hal_cli_print_sint( app_info.treble_level );
        hal_cli_print_str( ";" );
        hal_cli_print_str( "TREBLE_VR_POS=" );
        hal_cli_print_uint( app_info.treble_vr_pos );
        hal_cli_print_str( ".\r\n" );
        hal_ms6715_set_treble( app_info.treble_level );
    }
    
}

static int8_t vr_pos_2_tb_level( uint16_t vr_pos )
{

    int8_t tb_level;

    for( tb_level = 0; tb_level < sizeof(tb_level_lut)/sizeof(uint16_t)-1; tb_level++ )
    {
        if( vr_pos >= tb_level_lut[tb_level] && vr_pos < tb_level_lut[tb_level+1] )
        {
            break;
        }
    }

    if( tb_level > HAL_MS6715_TB_MAX - HAL_MS6715_TB_MIN )
    {
        tb_level = HAL_MS6715_TB_MAX - HAL_MS6715_TB_MIN;
    }

    tb_level -= HAL_MS6715_TB_MAX;

    return tb_level;
}

/**************************************************************************************************
**************************************************************************************************/

