/*
 * ao_led.c
 *
 *  Created on: Jun 30, 2024
 *      Author: lpmeoli
 */


/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"
#include "timers.h"
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "ao_led.h"

/********************** macros and definitions *******************************/

#define QUEUE_LENGTH_            (1)
#define QUEUE_ITEM_SIZE_         (sizeof(ao_led_message_t))

#define TASK_PERIOD_MS_           (1000)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

/********************** internal functions definition ************************/
static void timer_callback(TimerHandle_t pxTimer) {
	ao_led_handle_t* hao = (ao_led_handle_t*)pvTimerGetTimerID(pxTimer);
	LOGGER_INFO("Timer finished");
	ao_led_send(hao, AO_LED_MESSAGE_OFF);
}

static void task_(void *argument) {
    ao_led_handle_t* hao = (ao_led_handle_t*)argument;

    while (true) {
        ao_led_message_t msg;
        if (pdPASS == xQueueReceive(hao->hqueue, &msg, portMAX_DELAY)) {
            GPIO_PinState led_state;
            switch (msg) {
                case AO_LED_MESSAGE_ON:
                    led_state = GPIO_PIN_SET;
                    LOGGER_INFO("AO LED - led on");
                    xTimerStart(hao->htimer, 0);
                    break;

                case AO_LED_MESSAGE_OFF:;
                    led_state = GPIO_PIN_RESET;
                    LOGGER_INFO("AO LED - led off");
                    break;

                default:
                    LOGGER_INFO("AO LED - error");
                    break;
            }
            HAL_GPIO_WritePin(hao->led_port, hao->led_pin, led_state);
        }
    }
}

/********************** external functions definition ************************/

bool ao_led_send(ao_led_handle_t* hao, ao_led_message_t msg) {
    return (pdPASS == xQueueSend(hao->hqueue, (void*)&msg, 0));
}

void ao_led_init(ao_led_handle_t* hao) {
    hao->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);
    while(NULL == hao->hqueue) {
      // error
    }

    hao->htimer = xTimerCreate("LED_Timer", pdMS_TO_TICKS(hao->time_led_on), false, (void* const)hao, timer_callback);

    BaseType_t status;
    status = xTaskCreate(task_, "task_ao_led", 128, (void* const)hao, tskIDLE_PRIORITY, NULL);
    while (pdPASS != status) {
        // error
    }
}

/********************** end of file ******************************************/
