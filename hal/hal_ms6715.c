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
 
#include "osal.h"
#include "spl.h"

#include "hal_config.h"
#include "hal_assert.h"
#include "hal_ms6715.h"

#include "main.h"

#include "stdstr.h"
#include "stringx.h"
#include "bufmgr.h"

#if (HAL_MS6715_EN > 0)

#define MS6715_ADDR_WR          0x88

#define MS6715_HEAD_VOL         0x00
#define MS6715_HEAD_ATTL        0x80
#define MS6715_HEAD_ATTR        0xA0
#define MS6715_HEAD_LOUDNESS    0x40
#define MS6715_HEAD_BASS        0x60
#define MS6715_HEAD_TREBLE      0x70

static code uint8_t tb_setting_table[] = {
    0x00,   //-14dB, index = 0  
    0x01,   //-12dB, index = 1  
    0x02,   //-10dB      .      
    0x03,   //-8dB       .      
    0x04,   //-6dB       .      
    0x05,   //-4dB       .      
    0x06,   //-2dB       .      
    0x07,   // 0dB       .      
    0x0E,   //+2dB       .      
    0x0D,   //+4dB       .      
    0x0C,   //+6dB       .      
    0x0B,   //+8dB       .      
    0x0A,   //+10dB      .      
    0x09,   //+12dB, index = 13
    0x08    //+14dB, index = 14
};

static void hal_ms6715_write( uint8_t byte )
{
    uint8_t err;
    
    err = spl_i2c_start();
    HAL_ASSERT( err == SPL_I2C_ERR_NONE );

    err = spl_i2c_wr_addr( MS6715_ADDR_WR );
    HAL_ASSERT( err == SPL_I2C_ERR_NONE );

    err = spl_i2c_wr_data( byte );
    HAL_ASSERT( err == SPL_I2C_ERR_NONE );

    err = spl_i2c_stop();
    HAL_ASSERT( err == SPL_I2C_ERR_NONE );
}

extern void hal_ms6715_init( void )
{

}

//vol = 0~63, -78.75dB ~ 0dB, -1.25dB for each level
extern void hal_ms6715_set_vol( uint8_t vol )
{
    uint8_t vol_setting;
    
    if( vol > HAL_MS6715_VOL_MAX )
        vol = HAL_MS6715_VOL_MAX;
    
    vol_setting = HAL_MS6715_VOL_MAX-vol;
    hal_ms6715_write( MS6715_HEAD_VOL | vol_setting );
}

//vol = 0~31, -37.5dB ~ 0dB , -1.25dB for each level, 0 is mute
extern void hal_ms6715_set_voll( uint8_t vol )
{
    uint8_t vol_setting;
    
    if( vol > HAL_MS6715_VOL_LR_MAX )
        vol = HAL_MS6715_VOL_LR_MAX;

    vol_setting = HAL_MS6715_VOL_LR_MAX-vol;
    hal_ms6715_write( MS6715_HEAD_ATTL | vol_setting );
}

//vol = 0~31, -37.5dB ~ 0dB , -1.25dB for each level, 0 is mute
extern void hal_ms6715_set_volr( uint8_t vol )
{
    uint8_t vol_setting;
    
    if( vol > HAL_MS6715_VOL_LR_MAX )
        vol = HAL_MS6715_VOL_LR_MAX;

    vol_setting = HAL_MS6715_VOL_LR_MAX-vol;
    hal_ms6715_write( MS6715_HEAD_ATTR | vol_setting );
}

//HAL_MS6715_LOUDNESS_ON, HAL_MS6715_LOUDNESS_OFF
extern void hal_ms6715_set_loudness( uint8_t loudness_on_off )
{
    hal_ms6715_write( MS6715_HEAD_LOUDNESS | loudness_on_off );
}

//dblvl = -7 ~ +7, -14dB ~ 14dB, 2dB for each level
extern void hal_ms6715_set_bass( int8_t dblvl )
{
    if( dblvl < HAL_MS6715_TB_MIN )
        dblvl = HAL_MS6715_TB_MIN;
    else if( dblvl > HAL_MS6715_TB_MAX )
        dblvl = HAL_MS6715_TB_MAX;

    dblvl -= HAL_MS6715_TB_MIN;

    HAL_ASSERT( dblvl >= 0 );
    HAL_ASSERT( dblvl <= (HAL_MS6715_TB_MAX - HAL_MS6715_TB_MIN) );

    hal_ms6715_write( MS6715_HEAD_BASS | tb_setting_table[dblvl] );
}

//dblvl = -7 ~ +7, -14dB ~ 14dB, 2dB for each level
extern void hal_ms6715_set_treble( int8_t dblvl )
{
    if( dblvl < HAL_MS6715_TB_MIN )
        dblvl = HAL_MS6715_TB_MIN;
    else if( dblvl > HAL_MS6715_TB_MAX )
        dblvl = HAL_MS6715_TB_MAX;

    dblvl -= HAL_MS6715_TB_MIN;

    HAL_ASSERT( dblvl >= 0 );
    HAL_ASSERT( dblvl <= (HAL_MS6715_TB_MAX - HAL_MS6715_TB_MIN) );

    hal_ms6715_write( MS6715_HEAD_TREBLE | tb_setting_table[dblvl] );
}

#endif /* (HAL_MS6715_EN > 0) */

