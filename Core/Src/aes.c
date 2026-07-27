/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    aes.c
  * @brief   This file provides code for the configuration
  *          of the AES instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "aes.h"

/* USER CODE BEGIN 0 */
//    A1B2C3D4 E5F60718 293A4B5C 6D7E8F90
/* USER CODE END 0 */

CRYP_HandleTypeDef hcryp;
__ALIGN_BEGIN static const uint32_t pKeySAES[4] __ALIGN_END = {
                            0xA1B2C3D4,0xE5F60718,0x293A4B5C,0x6D7E8F90};
__ALIGN_BEGIN static const uint32_t pInitVectSAES[4] __ALIGN_END = {
                            0x00000000,0x00000000,0x00000000,0x00000000};

/* SAES init function */

void MX_SAES_AES_Init(void)
{

  /* USER CODE BEGIN SAES_Init 0 */

  /* USER CODE END SAES_Init 0 */

  /* USER CODE BEGIN SAES_Init 1 */
	hcryp.Init.pInitVect = (uint32_t *)pInitVectSAES;
  /* USER CODE END SAES_Init 1 */
  hcryp.Instance = SAES;
  hcryp.Init.DataType = CRYP_NO_SWAP;
  hcryp.Init.KeySize = CRYP_KEYSIZE_128B;
  hcryp.Init.pKey = (uint32_t *)pKeySAES;
  hcryp.Init.pInitVect = (uint32_t *)pInitVectSAES;
  hcryp.Init.Algorithm = CRYP_AES_CBC;
  hcryp.Init.DataWidthUnit = CRYP_DATAWIDTHUNIT_BYTE;
  hcryp.Init.KeyIVConfigSkip = CRYP_KEYIVCONFIG_ALWAYS;
  hcryp.Init.KeyMode = CRYP_KEYMODE_NORMAL;
  hcryp.Init.KeySelect = CRYP_KEYSEL_NORMAL;
  hcryp.Init.KeyProtection = CRYP_KEYPROT_DISABLE;
  if (HAL_CRYP_Init(&hcryp) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SAES_Init 2 */

  /* USER CODE END SAES_Init 2 */

}

void HAL_CRYP_MspInit(CRYP_HandleTypeDef* crypHandle)
{

  if(crypHandle->Instance==SAES)
  {
  /* USER CODE BEGIN SAES_MspInit 0 */

  /* USER CODE END SAES_MspInit 0 */
    /* SAES clock enable */
    __HAL_RCC_SAES_CLK_ENABLE();
  /* USER CODE BEGIN SAES_MspInit 1 */

  /* USER CODE END SAES_MspInit 1 */
  }
}

void HAL_CRYP_MspDeInit(CRYP_HandleTypeDef* crypHandle)
{

  if(crypHandle->Instance==SAES)
  {
  /* USER CODE BEGIN SAES_MspDeInit 0 */

  /* USER CODE END SAES_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SAES_CLK_DISABLE();
  /* USER CODE BEGIN SAES_MspDeInit 1 */

  /* USER CODE END SAES_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

