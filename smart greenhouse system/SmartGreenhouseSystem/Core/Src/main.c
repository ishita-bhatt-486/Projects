/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */

#include <stdio.h>
#include "../../ECUAL/LCD16X2/LCD16X2.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN PD */

#define DHT22_PORT GPIOA
#define DHT22_PIN GPIO_PIN_4
#define MyLCD LCD16X2_1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

int airQ_threshold=2978-693;
int temp_threshold=29;
int light_threshold=1200;

int airQ;
int temperature;
int hum1, hum2, temp1, temp2, sumMQ, checkMQ;
int temp_Celsius, temp_Fahrenheit, Humidity;
int ldr_val;

int pMillis, cMillis;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);

/* USER CODE BEGIN PFP */

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/

/* USER CODE BEGIN 0 */

// microsecond delay generate

void microDelay (uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < delay);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Changed to HIGH for better signal edges
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP; // Enable internal pullup just in case
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

//DHT22 Start Signal

uint8_t DHT22_Start (void)
{
	uint8_t Response = 0;

	Set_Pin_Output(DHT22_PORT, DHT22_PIN);
	HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, 0);

	HAL_Delay(18);

	HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, 1);

	microDelay (30);

	Set_Pin_Input(DHT22_PORT, DHT22_PIN);

	microDelay (40);

	if (!(HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))
	{
		microDelay (80);
		if ((HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN))) Response = 1;
		else Response = -1;
	}

// Wait for the sensor to finish its response (High signal)

// We use a simple timeout loop instead of HAL_GetTick to be faster

	uint32_t timeout = 0;

	while ((HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))
	{
		timeout++;
		if(timeout > 10000) break; // Prevent hanging
	}

	return Response;
}

// DHT22 Read Data

uint8_t DHT22_Read (void)
{
	uint8_t x,y = 0;
	for (x=0; x<8; x++)
	{
		uint32_t timeout = 0;

// when pin goes high - Start of bit transmission)

		while (!(HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))
		{
			timeout++;
			if(timeout > 10000) return 0;
		}
		microDelay(40);

// If bit is 0, signal is high for 26us

// If bit is 1, signal is high for 70us

		if (!(HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))
			y&= ~(1<<(7-x)); // bit 0
		else
			y|= (1<<(7-x)); // bit 1

// when  pin goes low- End of transmission

		timeout = 0;

		while ((HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)))
		{
			timeout++;
			if(timeout > 10000) return 0;
		}
	}
	return y;
}

/* USER CODE END 0 */

/**
* @brief The application entry point.
* @retval int
*/

int main(void)
{
	/* USER CODE BEGIN 1 */
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	HAL_Init();

	/* USER CODE BEGIN Init */
	/* USER CODE END Init */
	/* Configure the system clock */

	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	/* USER CODE END SysInit */
	/* Initialize all configured peripherals */

	MX_GPIO_Init();

	MX_USART2_UART_Init();

	MX_TIM2_Init();

	MX_ADC1_Init();
	MX_ADC2_Init();
	MX_ADC3_Init();

	/* USER CODE BEGIN 2 */

	HAL_TIM_Base_Start(&htim2);

//LCD

	LCD16X2_Init(MyLCD);
	LCD16X2_Clear(MyLCD);

	char lcd_buffer[32];

	char AirQ_string[30];
	sprintf(AirQ_string, "%d", airQ);

	char temperatureCelsius_string[30];
	sprintf(temperatureCelsius_string, "%d", temp_Celsius);

	char temperatureFahrenheit_string[30];
	sprintf(temperatureFahrenheit_string, "%d", temp_Fahrenheit);

	char humidity_string[30];
	sprintf(humidity_string, "%d", Humidity);

	char ldr_string[30];
	sprintf(ldr_string, "%d", ldr_val);

	LCD16X2_Set_Cursor(MyLCD, 1, 1);

	/* USER CODE END 2 */

	/* Infinite loop */

	/* USER CODE BEGIN WHILE */

	while (1)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_Start(&hadc3);

		DHT22_Start();

//MQ-135
		airQ = HAL_ADC_GetValue(&hadc1);

		if(airQ>airQ_threshold) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		}
		else {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		}
//DHT22

		hum1 = DHT22_Read();
		hum2 = DHT22_Read();
		temp1 = DHT22_Read();
		temp2 = DHT22_Read();
		sumMQ = DHT22_Read();
		checkMQ = hum1 + hum2 + temp1 + temp2;

		if (checkMQ == sumMQ)
		{
			if (temp1>127)
			{
				temp_Celsius = temp2/10*(-1);
			}
			else
			{
				temp_Celsius = ((temp1<<8)|temp2)/10;
			}

			temp_Fahrenheit = temp_Celsius * 9/5 + 32;

			if(temp_Celsius > temp_threshold) {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
			}
			else {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
			}

			Humidity = (float) ((hum1<<8)|hum2)/10;
		}

//debug block- dht-22

 	uint8_t presence = DHT22_Start();

		if(presence == 1)
		{
// Sensor Responded! Now read.
			hum1 = DHT22_Read();
			hum2 = DHT22_Read();
			temp1 = DHT22_Read();
			temp2 = DHT22_Read();
			sumMQ = DHT22_Read();

// Calculate
			checkMQ = hum1 + hum2 + temp1 + temp2;

// Combine bytes

			Humidity = (float)((hum1<<8)|hum2)/10;
			if (temp1>127) temp_Celsius = temp2/10*(-1);
			else temp_Celsius = ((temp1<<8)|temp2)/10;

			printf("Sensor Status: OK | Hum: %d %% | Temp: %d C\r\n", Humidity, temp_Celsius);
		}

		else
		{
			printf("Sensor Status: ERROR. (Response: %d)\r\n", presence);
		}

		HAL_Delay(500); // Read every 2 seconds (DHT22 is slow)

//ldr

 	ldr_val = HAL_ADC_GetValue(&hadc3);

		if(ldr_val > light_threshold) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		}
		else {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		}

//print-serial monitor

		printf("Air Quality: %d\n\r", airQ-airQ_threshold);
		printf("Temperature: %d deg C | %d deg F\n\r", temp_Celsius, temp_Fahrenheit);
		printf("Humidity: %d %%\n\r", Humidity);
		printf("Light: %d \n\r", ldr_val-light_threshold);

//LCD

			  // Air and Temp printing
			  LCD16X2_Clear(MyLCD);

			  LCD16X2_Set_Cursor(MyLCD, 1, 1);
			  sprintf(lcd_buffer, "Air Q: %d", airQ-airQ_threshold);
			  LCD16X2_Write_String(MyLCD, lcd_buffer);

			  LCD16X2_Set_Cursor(MyLCD, 2, 1);
			  sprintf(lcd_buffer, "Temp: %d C", temp_Celsius);
			  LCD16X2_Write_String(MyLCD, lcd_buffer);

			  HAL_Delay(1500);

			  // Humidity and Light print
			  LCD16X2_Clear(MyLCD);

			  LCD16X2_Set_Cursor(MyLCD, 1, 1);
			  sprintf(lcd_buffer, "Hum: %d %%", Humidity);
			  LCD16X2_Write_String(MyLCD, lcd_buffer);

			  LCD16X2_Set_Cursor(MyLCD, 2, 1);
			  sprintf(lcd_buffer, "Light: %d ", ldr_val-light_threshold);
			  LCD16X2_Write_String(MyLCD, lcd_buffer);

			  HAL_Delay(1500);

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}

	/* USER CODE END 3 */
}

/**

* @brief System Clock Configuration
* @retval None
*/

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the RCC Oscillators according to the specified parameters

	* in the RCC_OscInitTypeDef structure.

	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	*/

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK

	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_ADC12

	                                     |RCC_PERIPHCLK_ADC34|RCC_PERIPHCLK_TIM2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
	PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
	PeriphClkInit.Tim2ClockSelection = RCC_TIM2CLK_HCLK;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}

}

/**

* @brief ADC1 Initialization Function
* @param None
* @retval None
*/

static void MX_ADC1_Init(void)
{
	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_MultiModeTypeDef multimode = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */

	/** Common config

	*/

	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;

	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc1.Init.LowPowerAutoWait = DISABLE;
	hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure the ADC multi-mode
	*/

	multimode.Mode = ADC_MODE_INDEPENDENT;
	if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Regular Channel

	*/

	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_DIFFERENTIAL_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */
}

/**

* @brief ADC2 Initialization Function
* @param None
* @retval None
*/

static void MX_ADC2_Init(void)
{

	/* USER CODE BEGIN ADC2_Init 0 */

	/* USER CODE END ADC2_Init 0 */
	ADC_ChannelConfTypeDef sConfig = {0};

	/* USER CODE BEGIN ADC2_Init 1 */

	/* USER CODE END ADC2_Init 1 */

	/** Common config

	*/

	hadc2.Instance = ADC2;
	hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc2.Init.Resolution = ADC_RESOLUTION_12B;
	hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc2.Init.ContinuousConvMode = DISABLE;
	hadc2.Init.DiscontinuousConvMode = DISABLE;
	hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc2.Init.NbrOfConversion = 1;
	hadc2.Init.DMAContinuousRequests = DISABLE;
	hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc2.Init.LowPowerAutoWait = DISABLE;
	hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

	if (HAL_ADC_Init(&hadc2) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Regular Channel

	*/

	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_DIFFERENTIAL_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN ADC2_Init 2 */

	/* USER CODE END ADC2_Init 2 */

}

/**
* @brief ADC3 Initialization Function
* @param None
* @retval None
*/

static void MX_ADC3_Init(void)
{
	/* USER CODE BEGIN ADC3_Init 0 */

	/* USER CODE END ADC3_Init 0 */

	ADC_MultiModeTypeDef multimode = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	/* USER CODE BEGIN ADC3_Init 1 */

	/* USER CODE END ADC3_Init 1 */

	/** Common config

	*/

	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc3.Init.ContinuousConvMode = DISABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = DISABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc3.Init.LowPowerAutoWait = DISABLE;
	hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

	if (HAL_ADC_Init(&hadc3) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure the ADC multi-mode

	*/

	multimode.Mode = ADC_MODE_INDEPENDENT;

	if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK)
	{
		Error_Handler();
	}

	/** Configure Regular Channel

	*/

	sConfig.Channel = ADC_CHANNEL_12;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN ADC3_Init 2 */

	/* USER CODE END ADC3_Init 2 */

}



/**

* @brief TIM2 Initialization Function

* @param None

* @retval None

*/

static void MX_TIM2_Init(void)

{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};


	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 71;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 65535;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

	HAL_TIM_MspPostInit(&htim2);

}



/**

* @brief USART2 Initialization Function

* @param None

* @retval None

*/

static void MX_USART2_UART_Init(void)
{
	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**

* @brief GPIO Initialization Function

* @param None

* @retval None

*/

static void MX_GPIO_Init(void)

{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* USER CODE BEGIN MX_GPIO_Init_1 */



	/* USER CODE END MX_GPIO_Init_1 */



	/* GPIO Ports Clock Enable */

	__HAL_RCC_GPIOF_CLK_ENABLE();

	__HAL_RCC_GPIOC_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();



	/*Configure GPIO pin Output Level */

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5

	                  |GPIO_PIN_6, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA6 PA8 PA9 PA10 */

	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB10 PB3 PB4 PB5
	PB6 */

	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5

	                      |GPIO_PIN_6;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */

}

/* USER CODE BEGIN 4 */

PUTCHAR_PROTOTYPE

{	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

/* USER CODE END 4 */

/**
* @brief This function is executed in case of error occurrence.
* @retval None
*/

void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();

	while (1)	{	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
* @brief Reports the name of the source file and the source line number
* where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval None
*/

void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}

#endif /* USE_FULL_ASSERT */
