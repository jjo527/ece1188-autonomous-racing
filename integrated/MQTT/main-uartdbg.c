

// Standard includes
#include <stdlib.h>
#include <string.h>


static void displayBanner();



int main_uartdbg(int argc, char** argv)
{


    /* Stop WDT and initialize the system-clock of the MCU */
    stopWDT();
    initClk();

    /* Configure command line interface */
    CLI_Configure();

    displayBanner();
}


static void displayBanner()
{
    UART0_OutString("\n\r\n\r");
    UART0_OutString(" MQTT Twitter Controlled RGB LED - Version ");
    UART0_OutString("\n\r*******************************************************************************\n\r");
}
