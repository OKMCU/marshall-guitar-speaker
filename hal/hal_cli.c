/******************************************************************************

 @file  

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/
 
#include "osal.h"
#include "spl.h"

#include "hal_config.h"
#include "hal_assert.h"
#include "hal_cli.h"

#include "main.h"

#include <string.h>
#include "stringx.h"
#include "bufmgr.h"

#if (HAL_CLI_EN > 0)

//#define HAL_CLI_RX_DATA_BLK_SIZE    8

//static void *tx_fifo;
//#define IS_CHAR(x)  ( x > 0 && x <= 127 )


extern void hal_cli_init( void )
{   
    
}

extern void hal_cli_print_char(char c)
{
    spl_uart_txd( SPL_UART_PORT_0, (uint8_t)c );
}

extern void hal_cli_print_str(const char *s)
{
    while(*s)
    {
        hal_cli_print_char(*s++);
    }
}

extern void hal_cli_print_sint(int32_t num)
{
    char str[SINT_STR_LEN_MAX];
    uint8_t len;
    uint8_t i;
    
    len = sintstr(num, str);
    
    for(i = 0; i < len; i++)
    {
        hal_cli_print_char(str[i]);
    }
    
}

extern void hal_cli_print_uint(uint32_t num)
{
    char str[UINT_STR_LEN_MAX];
    uint8_t len;
    uint8_t i;
    
    len = uintstr(num, str);
    
    for(i = 0; i < len; i++)
    {
        hal_cli_print_char(str[i]);
    }
}

extern void hal_cli_print_hex8(uint8_t num)
{
    char str[HEX8_STR_LEN_MAX];
    uint8_t len;
    uint8_t i;
    
    len = hex8str(num, str);
    
    for(i = 0; i < len; i++)
    {
        hal_cli_print_char(str[i]);
    }
}


extern void hal_cli_print_hex16(uint16_t num)
{
    char str[HEX16_STR_LEN_MAX];
    uint8_t len;
    uint8_t i;
    
    len = hex16str(num, str);
    
    for(i = 0; i < len; i++)
    {
        hal_cli_print_char(str[i]);
    }
}

extern void hal_cli_print_hex32(uint32_t num)
{
    char str[HEX32_STR_LEN_MAX];
    uint8_t len;
    uint8_t i;
    
    len = hex32str(num, str);
    
    for(i = 0; i < len; i++)
    {
        hal_cli_print_char(str[i]);
    }
}

extern void hal_cli_driver_handle_rxne( void )
{
    char c;
    
    while( !spl_uart_rxd_empty(SPL_UART_PORT_0) )
    {
        c = spl_uart_rxd( SPL_UART_PORT_0 );
        spl_uart_txd( SPL_UART_PORT_0, (uint8_t)c );        //echo
    }
}

extern void spl_uart0_callback( uint8_t event )
{
    switch (event)
    {
        case SPL_UART_ISR_EVT_RXD:
            osal_event_set( TASK_ID_HAL_DRIVER_BASIC, TASK_EVT_HAL_DRIVER_BASIC_CLI_RXNE );
        break;

        //case SPL_UART_ISR_EVT_TXD_EMPTY:
        //    osal_event_set( TASK_ID_HAL_DRIVER_BASIC, TASK_EVT_HAL_DRIVER_BASIC_CLI_TXE );
        //break;
        
        case SPL_UART_ISR_EVT_RXD_FULL:
            //osal_event_set( OSAL_TASK_ID_HAL_DRIVERS, OSAL_TASK_EVT_HAL_CLI_RXF );
        break;

        default:
        break;
    }
    
}

#endif /* (HAL_CLI_EN > 0) */

