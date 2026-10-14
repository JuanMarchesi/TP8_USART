#include "usart.h"

int volatile mantissa;
int volatile fraction; 
int volatile valor;
int volatile PCLK;
int PA9 = 1;
int PA10 = 2;
int PA2 = 3;
int PA3 = 4;
int PB10 = 5;
int PB11 = 6;

void usart_init(USART_TypeDef * USARTx, uint32_t baudrate){

    if (USARTx == USART1)
    {
        PCLK = 72000000;
        RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
        RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
        RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
        GPIOA->CRH&=~(0XF<<PA9*4);
        GPIOA->CRH |=(0XB<<PA9*4);
        GPIOA->CRH&=~(0XF<<PA10*4);
        GPIOA->CRH |=(0XB<<PA10*4);
        USART1 -> BRR= (mantissa << 4)| fraction;
        USART1 -> CR1 |= USART_CR1_UE;
        USART1 -> CR1 |= USART_CR1_TE;
        USART1 -> CR1 |= USART_CR1_RE;
    }
        
    if (USARTx == USART2)
    {
        PCLK = 36000000;
        RCC -> APB1ENR |= RCC_APB2ENR_USART1EN;
        RCC -> APB1ENR |= RCC_APB2ENR_AFIOEN;
        RCC -> APB1ENR |= RCC_APB2ENR_IOPAEN;
        GPIOA->CRH&=~(0XF<<PA2*4);
        GPIOA->CRH |=(0XB<<PA2*4);
        GPIOA->CRH&=~(0XF<<PA3*4);
        GPIOA->CRH |=(0XB<<PA3*4);;
        valor =(16*baudrate)/PCLK;
        USART1 -> CR1 |= USART_CR1_UE;
        USART1 -> CR1 |= USART_CR1_TE;
        USART1 -> CR1 |= USART_CR1_RE;
    }

    if (USARTx == USART3)
    {
        PCLK = 36000000;
        RCC -> APB1ENR |= RCC_APB2ENR_USART1EN;
        RCC -> APB1ENR |= RCC_APB2ENR_AFIOEN;
        RCC -> APB1ENR |= RCC_APB2ENR_IOPAEN;
        GPIOA->CRH&=~(0XF<<PB10*4);
        GPIOA->CRH |=(0XB<<PB10*4);
        GPIOA->CRH&=~(0XF<<PB11*4);
        GPIOA->CRH |=(0XB<<PB11*4);;
        valor =(16*baudrate)/PCLK;
        USART1 -> CR1 |= USART_CR1_UE;
        USART1 -> CR1 |= USART_CR1_TE;
        USART1 -> CR1 |= USART_CR1_RE;
    }
        mantissa = valor;
        fraction = (valor-mantissa)*100;
        USARTx ->BRR = (mantissa << 4)| fraction;
        USARTx->CR1|=USART_CR1_UE;
        USARTx->CR1|=USART_CR1_TE;
        USARTx->CR1|=USART_CR1_RE;
}

void usart_send_char(USART_TypeDef * USARTx, uint8_t data){
    while(!(USARTx -> SR & USART_SR_TXE))
    USARTx -> DR = 'data';
}

void usart_send_string(USART_TypeDef* USARTx, char* texto ){
    
    while (*texto){
        usart_send(USARTx, *texto);
        texto++;
    }
}

uint8_t usart_receive_char(USART_TypeDef * USARTx) {
        while(!(USART1 -> SR & USART_SR_RXNE));
        char c = USART1->DR;
    }

