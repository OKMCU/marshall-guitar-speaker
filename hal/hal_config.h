/******************************************************************************

 @file  hal_config.h

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 2016-06-09 06:57:09
 *****************************************************************************/

#ifndef __HAL_CONFIG_H__
#define __HAL_CONFIG_H__

#define HAL_ASSERT_EN                    1

#define HAL_MCU_RESET_EN                 0
#define HAL_MCU_DELAYUS_EN               0
#define HAL_MCU_HSI_TRIM_EN              0

#define HAL_CLI_EN                       1
#define HAL_CLI_PRINT_EN                 1
#define HAL_CLI_RX_BUF_SIZE              8      //size should be < 255
#define HAL_CLI_TX_BUF_SIZE              0      //size should be < 255

#define HAL_KEY_EN                       1
#define HAL_VR_EN                        1
#define HAL_MS6715_EN                    1
#define HAL_HEADPHONE_EN                 1

/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

#endif

