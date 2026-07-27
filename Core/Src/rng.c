/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rng.c
  * @brief   This file provides code for the configuration
  *          of the RNG instances.
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
#include "rng.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RNG_HandleTypeDef hrng;

/* RNG init function */
void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */
	/* Abilita clock RNG */
	__HAL_RCC_RNG_CLK_ENABLE();

	/* Disabilita RNG */
	CLEAR_BIT(RNG->CR, RNG_CR_RNGEN);
	while(READ_BIT(RNG->SR, RNG_SR_BUSY));

	/* Config B con CONDRST=1 */
	WRITE_REG(RNG->CR,
			(1U   << 30) |  /* CONDRST */
			(0x83U<< 20) |  /* CONFIG1 */
			(0U   << 16) |  /* CLKDIV=0 */
			(0U   << 13) |  /* CONFIG2=0 */
			(1U   << 12) |  /* NISTC=1 */
			(0xFU <<  8) |  /* CONFIG3=0xF */
			(0U   <<  7) |  /* ARDIS=0 */
			(0U   <<  5));  /* CED abilitato */

	/* HTCR0 Config B — scrittura valida solo con CONDRST=1 */
	WRITE_REG(RNG->HTCR[0], 0x0000AAC7U);

	/* Abbassa CONDRST */
	CLEAR_BIT(RNG->CR, (1U << 30));
	while(READ_BIT(RNG->SR, RNG_SR_BUSY));
  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */
	/* Disabilita RNG */
	CLEAR_BIT(RNG->CR, RNG_CR_RNGEN);
	while(READ_BIT(RNG->SR, RNG_SR_BUSY));

	/* Applica configurazione NIST candidata */
	WRITE_REG(RNG->CR, RNG_CAND_NIST_CR_VALUE | RNG_CR_CONDRST);
	WRITE_REG(RNG->HTCR[0], RNG_CAND_NIST_HTCR_VALUE);
	WRITE_REG(RNG->NSCR, RNG_CAND_NIST_NSCR_VALUE);
	CLEAR_BIT(RNG->CR, RNG_CR_CONDRST);
	while(READ_BIT(RNG->SR, RNG_SR_BUSY));

	/* Abilita RNG */
	SET_BIT(RNG->CR, RNG_CR_RNGEN);

	uint32_t sr = RNG->SR;
	  /* USER CODE END RNG_Init 1 */


	hrng.Instance = RNG;
	hrng.Init.ClockErrorDetection = RNG_CED_DISABLE;


	if (HAL_RNG_Init(&hrng) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN RNG_Init 2 */
	CLEAR_BIT(RNG->CR, RNG_CR_RNGEN);
	while(READ_BIT(RNG->SR, RNG_SR_BUSY));

	/* Applica configurazione German BSI */
	WRITE_REG(RNG->CR, RNG_CAND_GermanBSI_CR_VALUE | RNG_CR_CONDRST);
	WRITE_REG(RNG->HTCR[0], RNG_CAND_GermanBSI_HTCR_VALUE);
	WRITE_REG(RNG->NSCR, RNG_CAND_GermanBSI_NSCR_VALUE);

	/* Abbassa CONDRST e abilita */
	CLEAR_BIT(RNG->CR, RNG_CR_CONDRST);
	while(READ_BIT(RNG->SR, RNG_SR_BUSY));

	SET_BIT(RNG->CR, RNG_CR_RNGEN);
	HAL_Delay(50);

	/* Aspetta DRDY */
	uint32_t tickstart = HAL_GetTick();
	while(!READ_BIT(RNG->SR, RNG_SR_DRDY))
	{
	    if((HAL_GetTick() - tickstart) > 100) break;
	}

	uint32_t sr_final = RNG->SR;
	uint32_t htsr0 = RNG->HTSR[0];  /* RPERR - repetition errors */
	uint32_t htsr1 = RNG->HTSR[1];  /* ADERR - adaptive proportion errors */
	uint32_t cr_final = RNG->CR;

	uint32_t rnd1, rnd2, rnd3;
	HAL_RNG_GenerateRandomNumber(&hrng, &rnd1);
	HAL_RNG_GenerateRandomNumber(&hrng, &rnd2);
	HAL_RNG_GenerateRandomNumber(&hrng, &rnd3);
	__NOP(); /* breakpoint */

	cr_final = cr_final;

	__NOP(); /* breakpoint */

  /* USER CODE END RNG_Init 2 */

}

void HAL_RNG_MspInit(RNG_HandleTypeDef* rngHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(rngHandle->Instance==RNG)
  {
  /* USER CODE BEGIN RNG_MspInit 0 */

  /* USER CODE END RNG_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RNG;
    PeriphClkInit.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* RNG clock enable */
    __HAL_RCC_RNG_CLK_ENABLE();
  /* USER CODE BEGIN RNG_MspInit 1 */

  /* USER CODE END RNG_MspInit 1 */
  }
}

void HAL_RNG_MspDeInit(RNG_HandleTypeDef* rngHandle)
{

  if(rngHandle->Instance==RNG)
  {
  /* USER CODE BEGIN RNG_MspDeInit 0 */

  /* USER CODE END RNG_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RNG_CLK_DISABLE();
  /* USER CODE BEGIN RNG_MspDeInit 1 */

  /* USER CODE END RNG_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

