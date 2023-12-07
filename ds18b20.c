
#include "main.h"
#include "stm32f1xx_hal.h"

#define DS18B20_PIN GPIO_PIN_12
#define DS18B20_PORT GPIOA

GPIO_InitTypeDef GPIO_InitStruct;
//TIM_HandleTypeDef htim2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

void DS18B20_Init(void)
{
  GPIO_InitStruct.Pin = DS18B20_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
  HAL_Delay(100);

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
  HAL_Delay(500);

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
  HAL_Delay(100);
}

void DS18B20_StartConversion(void)
{
  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
  HAL_Delay(15);

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
}

uint8_t DS18B20_ReadBit(void)
{
  uint8_t bit = 0;

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
  HAL_Delay(10);

  if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
  {
    bit = 1;
  }

  HAL_Delay(45);
  return bit;
}

uint8_t DS18B20_ReadByte(void)
{
  uint8_t byte = 0;

  for (uint8_t i = 0; i < 8; i++)
  {
    byte |= (DS18B20_ReadBit() << i);
  }

  return byte;
}

int16_t DS18B20_ReadTemperature(void)
{
  DS18B20_StartConversion();

  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
  HAL_Delay(2);

  uint8_t tempLSB = DS18B20_ReadByte();
  uint8_t tempMSB = DS18B20_ReadByte();

  int16_t tempRaw = (tempMSB << 8) | tempLSB;
  float temperature = (float)tempRaw / 16.0;

  return (int16_t)temperature;
}
/*
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();

  DS18B20_Init();

  while (1)
  {
    int16_t temperature = DS18B20_ReadTemperature();
}
}
*/





/*
#include "main.h"
#include "stm32f1xx_hal.h"

#define DS18B20_GPIO_PORT GPIOA
#define DS18B20_GPIO_PIN GPIO_PIN_12

GPIO_InitTypeDef GPIO_InitStruct;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void DS18B20_Init(void)
{
  GPIO_InitStruct.Pin = DS18B20_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;  // Ch? d? d?u ra Open Drain
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStruct);

  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_SET);
  HAL_Delay(100);
}

void DS18B20_StartConversion(void)
{
  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);

  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_SET);
  HAL_Delay(15);

  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_RESET);
}

uint8_t DS18B20_ReadBit(void)
{
  uint8_t bit = 0;

  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);

  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_SET);
  HAL_Delay(10);

  if (HAL_GPIO_ReadPin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN))
  {
    bit = 1;
  }

  HAL_Delay(45);
  return bit;
}

uint8_t DS18B20_ReadByte(void)
{
  uint8_t byte = 0;

  for (uint8_t i = 0; i < 8; i++)
  {
    byte |= (DS18B20_ReadBit() << i);
  }

  return byte;
}

float DS18B20_ReadTemperature(void)
{
  DS18B20_StartConversion();

  HAL_GPIO_WritePin(DS18B20_GPIO_PORT, DS18B20_GPIO_PIN, GPIO_PIN_SET);
  HAL_Delay(2);

  uint8_t tempLSB = DS18B20_ReadByte();
  uint8_t tempMSB = DS18B20_ReadByte();

  int16_t tempRaw = (tempMSB << 8) | tempLSB;
  float temperature = (float)tempRaw / 16.0f;

  return temperature;
}

 int main(void)
{
  //HAL_Init();
  //SystemClock_Config();
  //MX_GPIO_Init();

  //DS18B20_Init();

  while (1)
  {
    //float temperature = DS18B20_ReadTemperature();
  }
}
*/










