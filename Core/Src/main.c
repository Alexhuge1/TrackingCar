/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN PD */
#define TS0 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)
#define TS1 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)
#define TS2 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)
#define TS3 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)
#define TS4 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)

#define standard0 300
#define rotation0 300
#define supportrotation0 -275
#define start 220
#define smallrotation 150

#define standard1 340
#define rotation1 340
#define supportrotation1 -295

/* USER CODE END PD */

/* Private macro -----------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int16_t pwm[4];
int8_t array[5];

int8_t counter_fork=0;//��������

int8_t last_is_fork=0;
int8_t flag=0;
int8_t is_open;
uint32_t time;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void pwmoutput(int16_t * pwm)
{
    if(pwm[0]>=0)
    {
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,0);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,pwm[1]);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,pwm[0]);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,0);
    }
    else
    {
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,-pwm[0]);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,0);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,0);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,-pwm[1]);
    }


    if(pwm[2]>=0)
    {
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,pwm[2]);
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,pwm[3]);
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,0);
    }
    else
    {
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,0);
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_4,0);
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,-pwm[2]);
        __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,-pwm[3]);
    }
    return;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
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
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM8_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);


    is_open=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10);
    if(is_open==1)
    {
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,1);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,1);

        for(int8_t i =0; i<21; i++)
        {
            pwm[0]=start+4*i;
            pwm[1]=start+4*i;
            pwm[2]=start+4*i;
            pwm[3]=start+4*i;
            pwmoutput(pwm);
            HAL_Delay(35);
        }

        HAL_Delay(800);
    }

    else if(is_open==0)
    {

        for(int8_t i =0; i<21; i++)
        {
            pwm[0]=start+6*i;
            pwm[1]=start+6*i;
            pwm[2]=start+6*i;
            pwm[3]=start+6*i;
            pwmoutput(pwm);
            HAL_Delay(25);
        }

    }


    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        array[0]=TS0;
        array[1]=TS1;
        array[2]=TS2;
        array[3]=TS3;
        array[4]=TS4;

        if(is_open==1)
        {

            if((array[0]==0&&array[1]==1&&array[2]==0)||
                    (array[1]==0&&array[2]==1&&array[3]==0)||
                    (array[2]==0&&array[3]==1&&array[4]==0)||
                    (array[0]==0&&array[1]==1&&array[2]==1&&array[3]==0)||
                    (array[1]==0&&array[2]==1&&array[3]==1&&array[4]==0)||
                    (array[0]==0&&array[1]==1&&array[2]==1&&array[3]==1&&array[4]==0)||
                    (array[0]==1&&array[1]==0&&array[2]==0&&array[3]==0&&array[4]==1)||
                    (array[0]==1&&array[1]==1&&array[2]==0&&array[3]==0&&array[4]==0)
              )//�ֲ����ж�
            {
                time=HAL_GetTick();

                if(time>14000)
                {
                    if(last_is_fork==1)
                    {
                        counter_fork+=1;
                    }

                    if(counter_fork>5)
                    {
                        pwm[0]=standard0;
                        pwm[1]=standard0;
                        pwm[2]=standard0;
                        pwm[3]=standard0;
                        pwmoutput(pwm);
                    }
                }

				
                if(time>8000&&time<12000)
                {
                    if(last_is_fork==1)
                    {
                        counter_fork+=1;
                    }

                    if(counter_fork==3)
                    {
                        pwm[0]=standard0-50;
                        pwm[1]=standard0-50;
                        pwm[2]=standard0-50;
                        pwm[3]=standard0-50;
                        pwmoutput(pwm);
                        HAL_Delay(100);
                        while(!((TS4==1||TS3==1)&&(TS0==1||TS1==1)))
                        {
                            HAL_Delay(3);

                        }
                        pwm[0]=rotation0;
                        pwm[1]=rotation0;
                        pwm[2]=supportrotation0;
                        pwm[3]=supportrotation0;
                        pwmoutput(pwm);
                        HAL_Delay(300);
                        flag+=1;
                        while(!(TS0==1&&TS4==1))
                        {
                            HAL_Delay(3);
                        }
                    }
                }
                last_is_fork=1;
            }

			
            else if(array[0]==1&&array[1]==0&&array[3]==1&&array[4]==1)//Сƫ
            {
                pwm[0]=smallrotation;
                pwm[1]=smallrotation;
                pwm[2]=standard0;
                pwm[3]=standard0;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }
			
			
            else if(array[0]==1&&array[1]==1&&array[3]==0&&array[4]==1)//Сƫ
            {
                pwm[0]=standard0;
                pwm[1]=standard0;
                pwm[2]=smallrotation;
                pwm[3]=smallrotation;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }
			
			
            else if((array[0]==0&&array[2]==1&&array[3]==1&&array[4]==1))//��ƫ����ת
            {
                pwm[0]=supportrotation0;
                pwm[1]=supportrotation0;
                pwm[2]=rotation0;
                pwm[3]=rotation0;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }
			
			
            else if((array[0]==1&&array[1]==1&&array[2]==1&&array[4]==0))//��ƫ����ת
            {
                pwm[0]=rotation0;
                pwm[1]=rotation0;
                pwm[2]=supportrotation0;
                pwm[3]=supportrotation0;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }

			
            else
            {
                pwm[0]=standard0;
                pwm[1]=standard0;
                pwm[2]=standard0;
                pwm[3]=standard0;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }

        }

		
		
		
        else if(is_open==0)
        {
            if((array[0]==0&&array[1]==1&&array[2]==0)||
                    (array[1]==0&&array[2]==1&&array[3]==0)||
                    (array[2]==0&&array[3]==1&&array[4]==0)||
                    (array[0]==0&&array[1]==1&&array[2]==1&&array[3]==0)||
                    (array[1]==0&&array[2]==1&&array[3]==1&&array[4]==0)||
                    (array[0]==0&&array[1]==1&&array[2]==1&&array[3]==1&&array[4]==0)||
                    (array[0]==1&&array[1]==0&&array[2]==0&&array[3]==0&&array[4]==1)||
                    // (array[0]==1&&array[1]==0&&array[2]==0&&array[3]==0)
                    (array[0]==0&&array[1]==0&&array[2]==0&&array[3]==1&&array[4]==1)
              )//�ֲ����ж�
            {
                time=HAL_GetTick();

                if(time<5000)
                {
                    if(last_is_fork==1)
                    {
                        counter_fork+=1;
                    }

                    if(counter_fork==5)
                    {
                        pwm[0]=supportrotation1;
                        pwm[1]=supportrotation1;
                        pwm[2]=rotation1;
                        pwm[3]=rotation1;
                        pwmoutput(pwm);
                        HAL_Delay(250);
                        while(!(TS0==1&&TS4==1))
                        {
                            HAL_Delay(5);
                        }
                    }
                }

                if(time>14000)
                {
                    if(last_is_fork==1)
                    {
                        counter_fork+=1;
                    }

                    if(counter_fork==5)
                    {
                        pwm[0]=standard1;
                        pwm[1]=standard1;
                        pwm[2]=standard1;
                        pwm[3]=standard1;
                        pwmoutput(pwm);
                        HAL_Delay(150);


                        pwm[0]=supportrotation1;
                        pwm[1]=supportrotation1;
                        pwm[2]=rotation1;
                        pwm[3]=rotation1;
                        pwmoutput(pwm);
                        HAL_Delay(75);
                        while(!(TS2==0&&TS0==1&&TS4==1))
                        {
                            HAL_Delay(5);
                        }
                    }
                }
                last_is_fork=1;
            }

			
            else if((array[0]==0&&array[2]==1&&array[3]==1&&array[4]==1))//��ƫ����ת
            {
                pwm[0]=supportrotation1;
                pwm[1]=supportrotation1;
                pwm[2]=rotation1;
                pwm[3]=rotation1;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }
            else if((array[0]==1&&array[1]==1&&array[2]==1&&array[4]==0))//��ƫ����ת
            {
                pwm[0]=rotation1;
                pwm[1]=rotation1;
                pwm[2]=supportrotation1;
                pwm[3]=supportrotation1;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }

            else
            {
                pwm[0]=standard1;
                pwm[1]=standard1;
                pwm[2]=standard1;
                pwm[3]=standard1;
                pwmoutput(pwm);

                counter_fork=0;
                last_is_fork=0;
            }
        }

        HAL_Delay(5);
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

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {

    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
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
