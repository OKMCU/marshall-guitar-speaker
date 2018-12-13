/******************************************************************************

 @file  hal_headphone.c

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
#include "osal.h"
#include "spl.h"

#include "hal_config.h"
#include "hal_assert.h"
#include "hal_headphone.h"

#include "main.h"

#include <string.h>
#include "stringx.h"
#include "bufmgr.h"

/* ------------------------------------------------------------------------------------------------
 *                                       Local Prototypes
 * ------------------------------------------------------------------------------------------------
 */

extern void hal_headphone_init( void )
{
    SPL_GPIO_SET_MODE_P03_OUTPUT();
    spl_gpio_write_pin( SPL_GPIO_PIN_P03, 0 );

    SPL_GPIO_SET_MODE_P01_QUASI();
    spl_gpio_write_pin( SPL_GPIO_PIN_P01, 1 );
}

extern uint8_t hal_headphone_inserted( void )
{
    return (spl_gpio_read_pin( SPL_GPIO_PIN_P01 ) == 0);
}

extern void hal_headphone_enable_power_amp( void )
{
    spl_gpio_write_pin( SPL_GPIO_PIN_P03, 1 );
}

extern void hal_headphone_disable_power_amp( void )
{
    spl_gpio_write_pin( SPL_GPIO_PIN_P03, 0 );
}

/**************************************************************************************************
*/
