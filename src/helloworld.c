#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "pinmap.h"

#define LED_PIN 25

void dpins_high() { 
    gpio_put(ACSI_D_DIR,0); /* Output */
    for (int i=ACSI_D0;i<=ACSI_D7;i++) {
        gpio_set_dir(i,GPIO_OUT);
        gpio_put(i, 1);
    }

}

void dpins_low() {
    gpio_put(ACSI_D_DIR,0); /* Output */
    for (int i=ACSI_D0;i<=ACSI_D7;i++) {
        gpio_set_dir(i,GPIO_OUT);
        gpio_put(i, 0);
    }
}

int setup_acsi_gpio() {

    gpio_init(ACSI_IRQ);
    gpio_set_dir(ACSI_IRQ, GPIO_OUT);
    gpio_disable_pulls(ACSI_IRQ);
    gpio_put(ACSI_IRQ,1);

    for (int i=ACSI_D0;i<=ACSI_D7;i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
        gpio_put(i,0);
    }
    /* ACSI RW (from ST) direction of data pins 
        We need to change ACSI_D_DIR as well */
    gpio_init(ACSI_RW);
    gpio_set_dir(ACSI_RW, GPIO_IN);

    /* DIR on 74LS641-1 (Data pins)*/
    gpio_init(ACSI_D_DIR);
    gpio_set_dir(ACSI_D_DIR, GPIO_OUT);
    gpio_put(ACSI_D_DIR,1);  /* HIGH = INPUT */

    /* Reset from ST (active low)*/
    gpio_init(ACSI_RESET);
    gpio_set_dir(ACSI_RESET,GPIO_IN);

    /* A1 New command packet on bus*/
    gpio_init(ACSI_A1);
    gpio_set_dir(ACSI_A1, GPIO_IN);
 
    /* DMA Signals*/
    gpio_init(ACSI_ACK);
    gpio_set_dir(ACSI_ACK, GPIO_IN);

    gpio_init(ACSI_CS);
    gpio_set_dir(ACSI_CS, GPIO_IN);

    gpio_init(ACSI_DRQ);
    gpio_set_dir(ACSI_DRQ,GPIO_OUT);
    gpio_put(ACSI_DRQ,1);

} /* setup_acsi_gpio() */

int main() {
    stdio_init_all();
    //sleep_ms(8000);
    printf("Pico ACSI controller\n\n");
    printf("Init GPIOs...\n\n");
    
    setup_acsi_gpio();
    
    printf("Init LED..\n\n");   
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN,GPIO_OUT);
    gpio_put(LED_PIN,0);
    while(1) {
      /*  gpio_put(LED_PIN,1);
        gpio_put(ACSI_IRQ,1);
        printf("Led On! D-pins high!\n");
        //dpins_high();
        sleep_ms(1000);
        printf("Led Off! D-pins low!\n");
        //dpins_low();
        gpio_put(LED_PIN,0);
        gpio_put(ACSI_IRQ,1);
        sleep_ms(1000); */
        if(!gpio_get(ACSI_CS)) {
           
            //sleep_us(1);
            gpio_put(ACSI_IRQ,0);
            sleep_us(50);
            gpio_put(ACSI_IRQ,1);
            //gpio_put(LED_PIN,1);
            //printf("CS detected.\n");
            //sleep_us(20);
            //gpio_put(LED_PIN,0);
        }
    }
    return 0;
}