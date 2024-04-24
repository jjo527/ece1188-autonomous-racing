// Lab11_UARTmain.c
// Runs on MSP432
// Test the functions in UART0.c by printing various
// Busy-wait device driver for the UART UCA0.
// Daniel Valvano
// May 24, 2019

/* This example accompanies the book
   "Embedded Systems: Introduction to Robotics,
   Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2019, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/UART0.h"
#include "../inc/LaunchPad.h"

#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/SysTick.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include "../inc/Motor.h"
#include "../inc/TimerA1.h"
#include "../inc/TExaS.h"
#include "../inc/BumpInt.h"

#include "mqtt_main.h"

// Standard includes
#include <stdlib.h>
#include <string.h>

#include "driverlib.h"
#include "simplelink.h"
#include "sl_common.h"
#include "MQTTClient.h"



#define SIZE 20

extern Client hMQTTClient;
//extern

uint8_t CollisionData, CollisionFlag;  // mailbox
void HandleCollision2(uint8_t bumpSensor){
   Motor_Forward(0,0);
   CollisionData = bumpSensor;
   CollisionFlag = 1;
   P4->IFG &= ~0xED;
   char name [30] = "Bump Sensor Input!";

   UART0_OutString(name);
   Clock_Delay1ms(1500);
}

void main_main(void) {
    mqtt_init();

    // -------------------------------------------------
        // Publish to Server Test

        int rc;
        rc = MQTTYield(&hMQTTClient, 10);
        if (rc != 0) {
            UART0_OutString(" MQTT failed to yield \n\r");
            LOOP_FOREVER();
        }

        MQTTMessage msg;
        msg.dup = 0;
        msg.id = 0;
        msg.payload = "yeet";
        msg.payloadlen = 5;
        msg.qos = QOS0;
        msg.retained = 0;
        rc = MQTTPublish(&hMQTTClient, "daredevil_start_time", &msg);

        if (rc != 0) {
            UART0_OutString(" Failed to publish unique ID to MQTT broker \n\r");
            LOOP_FOREVER();
        }
        UART0_OutString(" Published Data to Server 2! \n\r");

        UART0_OutString(" DONE \n\r");

        while(1) {}

}
