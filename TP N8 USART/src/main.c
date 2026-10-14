#include "usart.h"
#include "stm32f103xb.h"
#include "clk_maximizer.h"

int main (void){

    clock_72MHz;
    usart_init(USART1, 9600);

    while (1)
    {
        usart_send_char(1, 'K');
    }
}