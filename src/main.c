#define RCC_AHB1ENR *((volatile unsigned int*)(0x40023800 + 0x30))
#define GPIOA_MODER *((volatile unsigned int*)(0x40020000 + 0x00))
#define GPIOA_ODR *((volatile unsigned int*)(0x40020000 + 0x14))

void delay(volatile int count) {
    while (count--) {
        //
    }
}

int main(void) {
    RCC_AHB1ENR |= (1 << 0);

    GPIOA_MODER &= ~(3 << (5 * 2));
    GPIOA_MODER |= (1 << (5 * 2));

    while (1) {
        GPIOA_ODR |= (1 << 5);
        delay(500000);

        GPIOA_ODR &= ~(1 << 5);
        delay(500000);
    }

    return 0;
    
}