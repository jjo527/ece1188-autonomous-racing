#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/Motor.h"
#include "../inc/TimerA1.h"
#include "../inc/Bump.h"

//Duty Cycle can range from 0 to 15,000
uint16_t LeftDuty2;
uint16_t RightDuty2;

void mainMS(void)
{
  Clock_Init48MHz(); // set system clock to 48 MHz

  Bump_Init();
  Motor_Init();
  EnableInterrupts();

  while(1)
  {

        //Ensure motors are stopped
        Motor_Forward(0,0);
        Clock_Delay1ms(1000);

        //Enter loop if any of the bump sensors are pressed
        uint8_t read = Bump_Read();
        uint8_t readAnd = read&0x3F;
        while(readAnd != 0x3F)
        {

//            //  3,750/15,000  = 25% Duty Cycle
//            LeftDuty2  = 3750;
//            RightDuty2 = 3750;
//            Motor_Forward(LeftDuty2, RightDuty2);
//            Clock_Delay1ms(1000); // delay 1 second
//
//            //  7,500/15,000  = 50% Duty Cycle
//            LeftDuty2  = 7500;
//            RightDuty2 = 7500;
//            Motor_Forward(LeftDuty2, RightDuty2);
//            Clock_Delay1ms(1000); // delay 1 second

            //  11,250/15,000  = 75% Duty Cycle
            LeftDuty2  = 9999;
            RightDuty2 = 9999;
            Motor_Forward(LeftDuty2, RightDuty2);
            Clock_Delay1ms(1000); // delay 1 second

            read = Bump_Read();
            readAnd = read&0x3F;

        }

        Motor_Forward(0,0);
  }
}


