#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "AD.h"
#include "Serial.h"
#include "Key.h"
#include "LED.h"
#include "OLED.h"

uint8_t mode = 0;				// 0=原始AD值 1=电压mV
uint8_t serial_en = 1;			// 串口输出开关

#define TASK_KEY_PRIO     4
#define TASK_KEY_SIZE     128
#define TASK_ADC_PRIO     3
#define TASK_ADC_SIZE     128
#define TASK_DISP_PRIO    2
#define TASK_DISP_SIZE    128
#define TASK_UART_PRIO    2
#define TASK_UART_SIZE    128
#define TASK_LED_PRIO     1
#define TASK_LED_SIZE     64

TaskHandle_t StartTask_Handler;

/* 任务函数前向声明（C 要求先声明后使用） */
static void start_task(void *pvParameters);
static void key_task(void *pvParameters);
static void adc_task(void *pvParameters);
static void disp_task(void *pvParameters);
static void uart_task(void *pvParameters);
static void led_task(void *pvParameters);

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);   // 必须！放在所有外设初始化前
    OLED_Init();
    AD_Init();
    Serial_Init();
    Key_Init();
    LED_Init();
    xTaskCreate((TaskFunction_t)start_task, "start_task", 128, NULL, 1,
                (TaskHandle_t *)&StartTask_Handler);
    vTaskStartScheduler();   // 启动调度器，不会返回
}

/* 启动任务：创建5个子任务后自杀 */
static void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();
    xTaskCreate(key_task, "key", TASK_KEY_SIZE, NULL, TASK_KEY_PRIO, NULL);
    xTaskCreate(adc_task, "adc", TASK_ADC_SIZE, NULL, TASK_ADC_PRIO, NULL);
    xTaskCreate(disp_task, "disp", TASK_DISP_SIZE, NULL, TASK_DISP_PRIO, NULL);
    xTaskCreate(uart_task, "uart", TASK_UART_SIZE, NULL, TASK_UART_PRIO, NULL);
    xTaskCreate(led_task, "led", TASK_LED_SIZE, NULL, TASK_LED_PRIO, NULL);
    vTaskDelete(StartTask_Handler);
    taskEXIT_CRITICAL();
}

/* 按键任务：KEY1 切换显示模式 / KEY2 开关串口（消抖在任务里做） */
static void key_task(void *pvParameters)
{
    while (1)
    {
        if (key1_flag == 1)
        {
            key1_flag = 0;
            vTaskDelay(20);                                         // 消抖
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)      // 确认真的按下
            {
                while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
                    vTaskDelay(10);                                 // 等松手也让出CPU
                mode = !mode;
            }
        }
        if (key2_flag == 1)
        {
            key2_flag = 0;
            vTaskDelay(20);
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
            {
                while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
                    vTaskDelay(10);
                serial_en = !serial_en;
            }
        }
        vTaskDelay(10);          // 主循环让出CPU，否则饿死低优先级任务
    }
}

/* 采集任务：只采样，OLED刷新由disp_task统一负责 */
static void adc_task(void *pvParameters)
{
    while (1)
    {
        AD_GetValue();      // 读取 AD 各通道 → 更新全局数组
        vTaskDelay(100);
    }
}

/* 显示任务：OLED唯一写者 */
static void disp_task(void *pvParameters)
{
    while (1)
    {
        if (mode == 0)
        {
            OLED_ShowString(1, 1, "AD0:");
            OLED_ShowNum(1, 5, AD_Value[0], 4);
            OLED_ShowString(2, 1, "AD1:");
            OLED_ShowNum(2, 5, AD_Value[1], 4);
            OLED_ShowString(3, 1, "AD2:");
            OLED_ShowNum(3, 5, AD_Value[2], 4);
            OLED_ShowString(4, 1, "AD3:");
            OLED_ShowNum(4, 5, AD_Value[3], 4);
        }
        else
        {
            OLED_ShowString(1, 1, "V0:  ");
            OLED_ShowNum(1, 5, AD_Value[0] * 3300 / 4095, 4);
            OLED_ShowString(2, 1, "V1:  ");
            OLED_ShowNum(2, 5, AD_Value[1] * 3300 / 4095, 4);
            OLED_ShowString(3, 1, "V2:  ");
            OLED_ShowNum(3, 5, AD_Value[2] * 3300 / 4095, 4);
            OLED_ShowString(4, 1, "V3:  ");
            OLED_ShowNum(4, 5, AD_Value[3] * 3300 / 4095, 4);
        }
        vTaskDelay(100);
    }
}

/* 串口任务：每秒打印带解读的数据 */
static void uart_task(void *pvParameters)
{
    uint16_t sec = 0;
    while (1)
    {
        sec++;
        if (serial_en == 1)
        {
            printf("\r\n===== 环境数据 第%ds =====\r\n", sec);
            printf("AD0=%d  电压=%dmV  电位器通道\r\n", AD_Value[0], AD_Value[0] * 3300 / 4095);
            printf("AD1=%d  电压=%dmV  光敏通道\r\n", AD_Value[1], AD_Value[1] * 3300 / 4095);
            printf("AD2=%d  电压=%dmV  热敏通道\r\n", AD_Value[2], AD_Value[2] * 3300 / 4095);
            printf("AD3=%d  电压=%dmV  反射式红外通道\r\n", AD_Value[3], AD_Value[3] * 3300 / 4095);
            printf("===========================\r\n");
        }
        vTaskDelay(1000);
    }
}

/* LED 任务：500ms 翻转 */
static void led_task(void *pvParameters)
{
    while (1)
    {
        LED_Turn();
        vTaskDelay(500);
    }
}
