/*
 * ao_led.h
 *
 *  Created on: Jun 30, 2024
 *      Author: lpmeoli
 */

#ifndef AO_LED_H_
#define AO_LED_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "cmsis_os.h"

/********************** macros ***********************************************/

/********************** typedef **********************************************/

typedef enum {
  AO_LED_MESSAGE_ON,
  AO_LED_MESSAGE_OFF,
  AO_LED_MESSAGE__N,
} ao_led_message_t;

typedef struct {
    QueueHandle_t hqueue;
    TimerHandle_t htimer;
    uint16_t time_led_on;
    GPIO_TypeDef* led_port;
    uint16_t led_pin;
} ao_led_handle_t;

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

bool ao_led_send(ao_led_handle_t* hao, ao_led_message_t msg);

void ao_led_init(ao_led_handle_t* hao);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* AO_LED_H_ */
/********************** end of file ******************************************/

