/*
 * ao_ui.h
 *
 *  Created on: Jun 30, 2024
 *      Author: lpmeoli
 */

#ifndef INC_AO_UI_H_
#define INC_AO_UI_H_


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
    AO_UI_MESSAGE_BUTTON_NONE,
    AO_UI_MESSAGE_BUTTON_PULSE,
    AO_UI_MESSAGE_BUTTON_SHORT,
    AO_UI_MESSAGE_BUTTON_LONG,
    AO_UI_MESSAGE__N,
} ao_ui_message_t;

typedef struct {
    QueueHandle_t hqueue;
} ao_ui_handle_t;

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

bool ao_ui_send(ao_ui_handle_t* hao, ao_ui_message_t msg);

void ao_ui_init(ao_ui_handle_t* hao);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* INC_AO_UI_H_ */
