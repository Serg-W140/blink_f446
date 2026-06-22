void SystemInit(void) {}
void _init(void) {}

// Регистры тактирования
#define RCC_AHB1ENR *((volatile unsigned int*)(0x40023800 + 0x30))

// Регистры порта А (светодиод РА5)
#define GPIOA_MODER *((volatile unsigned int*)(0x40020000 + 0x00))
#define GPIOA_ODR *((volatile unsigned int*)(0x40020000 + 0x14))

// Регистры порта В (кнопка РС13)
#define GPIOC_MODER *((volatile unsigned int*)(0x40020800 + 0x00))
#define GPIOC_IDR *((volatile unsigned int*)(0x40020810))

int main(void) {
    RCC_AHB1ENR |= (1 << 0) | (1 << 2);

    GPIOA_MODER &= ~(3 << (5 * 2));
    GPIOA_MODER |= (1 << (5 * 2));

    // Настраиваем ножку кнопки РС13 на вход (биты 00) - очищаем биты 27 и 26 (13 * 2 = 26)
    GPIOC_MODER &= ~(3 << (13 * 2));

    while (1) {
        // Проверяем 13-й бит в регистре ввода GPIOC_IDR.
        // Сдвигаем регистр вправо на 13 позиций и отсекаем маской & 1
        int button_state = (GPIOC_IDR >> 13) & 1;

        if(button_state == 0) {
            GPIOA_ODR |= (1 << 5);
        } else {
            GPIOA_ODR &= ~(1 << 5);
        }
    }

    return 0;
    
}