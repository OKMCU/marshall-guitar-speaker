/******************************************************************************

 @file  hal.c

 @brief Describe the purpose and contents of the file.

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/


/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "spl.h"

/* ------------------------------------------------------------------------------------------------
 *                                       Local Prototypes
 * ------------------------------------------------------------------------------------------------
 */

extern void hal_mcu_init( void )
{
    spl_mcu_init();

#if (SPL_UART0_EN > 0)
    spl_uart_init( SPL_UART_PORT_0 );
    spl_uart_open( SPL_UART_PORT_0 );
#endif

#if (SPL_UART1_EN > 0)
    spl_uart_init( SPL_UART_PORT_1 );
    spl_uart_open( SPL_UART_PORT_1 );
#endif

#if (SPL_I2C_MASTER_EN > 0 || SPL_I2C_SLAVE_EN > 0)
    spl_i2c_init();
    spl_i2c_open();
#endif

#if (SPL_EXTINT_EN > 0)
    spl_extint_init();
#endif
}

extern void hal_mcu_reset( void )
{
    spl_mcu_reset();
}

extern void hal_mcu_delayus( uint32_t us)
{
    spl_mcu_delayus(us);
}

/**************************************************************************************************
*/