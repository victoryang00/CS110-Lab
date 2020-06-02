#include "lcd/lcd.h"
#include <string.h>

void draw();

void Inp_init(void) {
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
}

void Adc_init(void) {
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_init(GPIOA, GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
    RCU_CFG0 |= (0b10 << 14) | (1 << 28);
    rcu_periph_clock_enable(RCU_ADC0);
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;
}

void IO_init(void) {
    Inp_init(); // inport init
    Adc_init(); // A/D init
    Lcd_Init(); // LCD init
}

int Get_Button(int ch) {
    ADC_RSQ2(ADC0) = 0;
    ADC_RSQ2(ADC0) = ch;
    ADC_CTL1(ADC0) |= ADC_CTL1_ADCON;
    while (!(ADC_STAT(ADC0) & ADC_STAT_EOC))
        ;
    uint16_t ret = ADC_RDATA(ADC0) & 0xFFFF;
    ADC_STAT(ADC0) &= ~ADC_STAT_EOC;
    return (ret == 4095);
}

int Get_BOOT0(void) { return (int)(gpio_input_bit_get(GPIOA, GPIO_PIN_8)); }

int rand() {
    static unsigned long reg = 123; /*reg must be unsigned so right
                                       shift works properly.*/
    /*reg should be initialized with some random value.*/
    reg = ((((reg >> 31) /*Shift the 32nd bit to the first
                                     bit*/
             ^ (reg >> 6) /*XOR it with the seventh bit*/
             ^ (reg >> 4) /*XOR it with the fifth bit*/
             ^ (reg >> 2) /*XOR it with the third bit*/
             ^ (reg >> 1) /*XOR it with the second bit*/
             ^ reg) /*and XOR it with the first bit.*/
            & 0x0000001) /*Strip all the other bits off and*/
           << 31) /*move it back to the 32nd bit.*/
          | (reg >> 1); /*Or with the reg shifted
                               right.*/
    return reg; /*Return the first bit.*/
}

int main(void) {
    IO_init(); // init OLED
    LCD_Clear(BLACK);
    BACK_COLOR = BLACK;

    LCD_ShowString(0, 0, (u8 *)("Hello World1!"), WHITE);
    LCD_ShowString(0, 16, (u8 *)("Hello World2!"), BLUE);
    LCD_ShowString(0, 32, (u8 *)("Hello World3!"), BRED);
    LCD_ShowString(0, 48, (u8 *)("Hello World4!"), GBLUE);
    LCD_ShowString(0, 64, (u8 *)("Hello World5!"), RED);

    int r = 0, g = 0, b = 0, p = 3, x = 80, y = 40;
    while (1) {
        while (!Get_BOOT0()) {
            delay_1ms(50);
            if (Get_BOOT0()) break;
        }

        // LCD_Clear(BLACK);
        draw(x, y, p, (r << 11) + (g << 5) + b);
        p = (p + ((rand() & 0x3fffffff)%3 - 1) + 20) % 20 + 1;
        r = (r + ((rand() & 0x3fffffff)%3 - 1)) & 0b11111;
        g = (g + ((rand() & 0x3fffffff)%3 - 1)) & 0b111111;
        b = (b + ((rand() & 0x3fffffff)%3 - 1)) & 0b11111;
        x = (x + ((rand() & 0x3fffffff)%3 - 1) + 160) % 160;
        y = (y + ((rand() & 0x3fffffff)%3 - 1) + 80) % 80;
    }
}
