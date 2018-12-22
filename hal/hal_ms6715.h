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
 
#ifndef __HAL_MS6715_H__
#define __HAL_MS6715_H__


#include "stdint.h"
#include "hal_config.h"

#if (HAL_MS6715_EN > 0)

#define HAL_MS6715_VOL_MIN      0
#define HAL_MS6715_VOL_MAX      63
#define HAL_MS6715_VOL_LR_MIN   0
#define HAL_MS6715_VOL_LR_MAX   31
#define HAL_MS6715_TB_MIN       -7
#define HAL_MS6715_TB_MAX       7

#define HAL_MS6715_LOUDNESS_ON  0x00
#define HAL_MS6715_LOUDNESS_OFF 0x04

extern void hal_ms6715_init( void );
extern void hal_ms6715_set_vol( uint8_t vol );
extern void hal_ms6715_set_voll( uint8_t vol );
extern void hal_ms6715_set_volr( uint8_t vol );
extern void hal_ms6715_set_loudness( uint8_t loudness_on_off );
extern void hal_ms6715_set_bass( int8_t dblvl );
extern void hal_ms6715_set_treble( int8_t dblvl );
#endif /* (HAL_MS6715_EN > 0) */

#endif /* __HAL_MS6715_H__ */

