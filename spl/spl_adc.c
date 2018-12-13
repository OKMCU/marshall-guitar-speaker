/******************************************************************************

 @file  

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/
#include "Common.h"
#include "Function_Define.h"
#include "N76E003.h"
#include "SFR_Macro.h"
#include "spl_config.h"
#include "spl_adc.h"

#if (SPL_ADC_EN > 0)

extern uint16_t spl_adc_read( uint8_t ch )
{
    switch( ch )
    {
#if (SPL_ADC_CH0_EN > 0)
        case SPL_ADC_CH_0:
            Enable_ADC_AIN0;
        break;
#endif
#if (SPL_ADC_CH1_EN > 0)
        case SPL_ADC_CH_1:
            Enable_ADC_AIN1;
        break;
#endif
#if (SPL_ADC_CH2_EN > 0)
        case SPL_ADC_CH_2:
            Enable_ADC_AIN2;
        break;
#endif
#if (SPL_ADC_CH3_EN > 0)
        case SPL_ADC_CH_3:
            Enable_ADC_AIN3;
        break;
#endif
#if (SPL_ADC_CH4_EN > 0)
        case SPL_ADC_CH_4:
            Enable_ADC_AIN4;
        break;
#endif
#if (SPL_ADC_CH5_EN > 0)
        case SPL_ADC_CH_5:
            Enable_ADC_AIN5;
        break;
#endif
#if (SPL_ADC_CH6_EN > 0)
        case SPL_ADC_CH_6:
            Enable_ADC_AIN6;
        break;
#endif
#if (SPL_ADC_CH7_EN > 0)
        case SPL_ADC_CH_7:
            Enable_ADC_AIN7;
        break;
#endif
#if (SPL_ADC_BANDGAP_EN > 0)
        default:
            Enable_ADC_BandGap;
        break;
#endif
    }
    
    clr_ADCF;
	set_ADCS;
    while(ADCF == 0);
    return ((uint16_t)ADCRH << 4) | (uint16_t)(ADCRL&0x0F);//ADCRH[11:4] stores MSB, ADCRL[3:0] stores LSB;

}


#endif //(SPL_ADC_EN > 0)

