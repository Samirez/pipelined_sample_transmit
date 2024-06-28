#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include <esp_adc_cal.h>
#include <driver/adc.h>
#include <time.h>
#include <math.h>

#define DELAY(ms) ((ms) / portTICK_PERIOD_MS)
#define DEFAULT_VREF 1100
#define TX_BUFFER_SIZE 10

QueueHandle_t tx_queue;
static esp_adc_cal_characteristics_t *adc1_chars;

void TaskSample(void* pvParameters){
    QueueHandle_t output_queue = (QueueHandle_t) pvParameters;
    adc1_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc1_chars);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    while(1) {
        int read_raw = adc1_get_raw(ADC1_CHANNEL_6);
        if (read_raw) {
            printf("%d\n", read_raw );
            vTaskDelay(DELAY(1000));
            int value = read_raw;
            while (xQueueSendToBack(output_queue, &value, 10) != pdTRUE) ;
        } else {
            printf("ADC1 used by Wi-Fi.\n");
        }
    }
    //free(adc1_chars);
    //vTaskDelete(NULL);
}


void TaskTransmit(void* pvParameters){
    QueueHandle_t input_queue = (QueueHandle_t) pvParameters;
    int value;
    while(1){
        while (xQueueReceive(input_queue, &value, 10) != pdPASS);
        uint32_t voltage = 0;
        voltage = esp_adc_cal_raw_to_voltage(value, adc1_chars);
        printf("ADC1_CHANNEL_6: %" PRIu32 " mV\n", voltage);
        float voltage_mV = (float)voltage;
        //float temperature = ((voltage_mV - 1885) / (50 - 20)) + 30;
        float temperature = ((10.888-sqrt(pow(-10.888, 2.0)+(4*0.00347*(1777.3-voltage_mV))))/(2*(-0.00347)))+30;
        printf("Temperature is %.2f°C\n", temperature);
    }
}

void app_main(void)
{
    tx_queue = xQueueCreate(TX_BUFFER_SIZE, sizeof(int));
    xTaskCreate(TaskSample, "Sample", 4096, tx_queue, 1, NULL);
    xTaskCreate(TaskTransmit, "Transmit", 4096, tx_queue, 1, NULL);
}
