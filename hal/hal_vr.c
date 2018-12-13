/******************************************************************************

 @file  hal_vr.c

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
#include "hal_vr.h"

#include "main.h"

#include <string.h>
#include "stringx.h"
#include "bufmgr.h"

/* ------------------------------------------------------------------------------------------------
 *                                       Local Prototypes
 * ------------------------------------------------------------------------------------------------
 */

extern void hal_vr_init( void )
{
    
    
}

extern uint16_t hal_vr_read( uint8_t vr_x )
{
    uint16_t val = 0;
    
    switch ( vr_x )
    {
        case HAL_VR_0:
            val = SPL_ADC_VALUE_MAX - spl_adc_read( SPL_ADC_CH_4 );
        break;
        
        case HAL_VR_1:
            val = SPL_ADC_VALUE_MAX - spl_adc_read( SPL_ADC_CH_7 );
        break;
    }
    
    return val;
}

/**************************************************************************************************
*/
