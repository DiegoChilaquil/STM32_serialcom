#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdio.h>

static void clock_config(void){

    rcc_clock_setup_in_hse_8mhz_out_72mhz();

    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART1);

}


static void __set_gpio(void){

    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, 
                GPIO_CNF_OUTPUT_PUSHPULL,
                GPIO13);
}

static void __usart_setup(void){

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                GPIO_USART1_TX);

    usart_set_baudrate(USART1, 38400);
    usart_set_databits(USART1, 8);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_mode(USART1, USART_MODE_TX);

    usart_enable(USART1);
}

static void
send_data(char *c){

    if(*c != '\0'){
        usart_send(USART1, *c);
        
        c++;

        for(int j=0; j<=7200000;j++){
            __asm__("nop");
        }
    }


    

}

int main(void){

    clock_config();
    __set_gpio();
    __usart_setup();

    char dato[] = "hola Compu";
    
    while(1){
        send_data(dato);
    }
}

