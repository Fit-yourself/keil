#include "key.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define PUSH1 GPIO_PIN1
#define PUSH2 GPIO_PIN4
#define RED_LED GPIO_PIN0
#define BLUE_LED GPIO_PIN2

#define RED_HIGH GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED_LED);
#define BLUE_HIGH GPIO_setOutputHighOnPin(GPIO_PORT_P2, BLUE_LED);

#define RED_LOW GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED_LED);
#define BLUE_LOW GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE_LED);
void LedWait()
{
  RED_HIGH // ºìµÆÁÁ
  BLUE_LOW   // ÂÌµÆÃð
}
void LEDRun()
{
  RED_LOW // ºìµÆÃð
  BLUE_HIGH // ÂÌµÆÁÁ
}
void KEY_INIT(void)
{
    //RED_LED
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, RED_LED);
    //BLUE_LED
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, BLUE_LED);
    LedWait();
    
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, PUSH1); // PUSH1
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, PUSH1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, PUSH1);
    MAP_Interrupt_enableInterrupt(INT_PORT1);


    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, PUSH2); // PUSH2 ÉÏÀ­
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, PUSH2);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, PUSH2);
    MAP_Interrupt_enableInterrupt(INT_PORT1);

    /* Enabling SRAM Bank Retention */
    MAP_SysCtl_A_enableSRAMRetention(0x20002000, 0x20002000);
    
    /* Enabling MASTER interrupts */
    MAP_Interrupt_enableMaster();   
}

/* GPIO ISR */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    /* Toggling the output on the LED */
    if(status & PUSH1)
    {
        LEDRun();
        /*¿ªÊ¼ADC×ª»»*/
    }

    if(status & PUSH2)
    {
        LedWait();
        /*Í£Ö¹ADC×ª»»*/
    }
}
