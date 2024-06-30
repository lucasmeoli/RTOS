/*
 * ao_ui.c
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
#include "board.h"
#include "logger.h"
#include "dwt.h"

#include "ao_ui.h"
#include "ao_led.h"

/********************** macros and definitions *******************************/

#define QUEUE_LENGTH_            (1)
#define QUEUE_ITEM_SIZE_         (sizeof(ao_ui_message_t))

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data definition *****************************/

extern ao_led_handle_t hao_ledR;
extern ao_led_handle_t hao_ledG;
extern ao_led_handle_t hao_ledB;

/********************** internal functions definition ************************/

static void task_(void *argument)
{
  ao_ui_handle_t* hao = (ao_ui_handle_t*)argument;
  while (true)
  {
    ao_ui_message_t msg;
    if (pdPASS == xQueueReceive(hao->hqueue, &msg, portMAX_DELAY))
    {
        switch (msg) {
          case AO_UI_MESSAGE_BUTTON_NONE:
            break;
          case AO_UI_MESSAGE_BUTTON_PULSE:
            LOGGER_INFO("AO UI - button pulse");
            ao_led_send(&hao_ledR, AO_LED_MESSAGE_ON);
            break;
          case AO_UI_MESSAGE_BUTTON_SHORT:
            LOGGER_INFO("AO UI - button short");
            ao_led_send(&hao_ledG, AO_LED_MESSAGE_ON);
            break;
          case AO_UI_MESSAGE_BUTTON_LONG:
            LOGGER_INFO("AO UI - button long");
            ao_led_send(&hao_ledB, AO_LED_MESSAGE_ON);
            break;
          default:
            LOGGER_INFO("AO UI - button error");
            break;
        }
    }
  }
}

/********************** external functions definition ************************/

bool ao_ui_send(ao_ui_handle_t* hao, ao_ui_message_t msg)
{
  return (pdPASS == xQueueSend(hao->hqueue, (void*)&msg, 0));
}

void ao_ui_init(ao_ui_handle_t* hao)
{
  hao->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_);
  while(NULL == hao->hqueue)
  {
    // error
  }

  BaseType_t status;
  status = xTaskCreate(task_, "task_ao_ui", 128, (void* const)hao, tskIDLE_PRIORITY, NULL);
  while (pdPASS != status)
  {
    // error
  }
}

/********************** end of file ******************************************/
