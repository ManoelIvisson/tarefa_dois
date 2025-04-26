#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/adc.h"

#include "portas_logicas.c"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

int main()
{
    stdio_init_all();

    // Configuração dos botões A e B
    gpio_init(BOTAO_A);
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);

    // Configuração dos leds
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    uint8_t ssd[ssd1306_buffer_length];

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    calculate_render_area_buffer_length(&frame_area);

    // zera o display inteiro
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // Configuração do Joystick
    adc_init();

    adc_gpio_init(26);
    adc_gpio_init(27);

    uint porta = 0;

    while (true) {
        adc_select_input(0);
        uint adc_y_raw = adc_read();
        
        // Verifica se o usuário direcionou o Joystick para cima
        if (adc_y_raw > 4000) {
            if (porta < 6) {
                porta += 1;
                memset(ssd, 0, ssd1306_buffer_length);
            }  
        } else if (adc_y_raw < 100) {
            if (porta > 0) {
                porta -= 1;
                memset(ssd, 0, ssd1306_buffer_length);
            }  
        }

        switch (porta)
        {
        case 0:
            porta_and();
            ssd1306_draw_string(ssd, 50, 25, "AND");
            break;
        case 1: {
            porta_or();
            ssd1306_draw_string(ssd, 50, 25, "OR");
            break;
        }
        case 2: {
            porta_not();
            ssd1306_draw_string(ssd, 50, 25, "NOT");
            break;
        }
        case 3: {
            porta_nand();
            ssd1306_draw_string(ssd, 50, 25, "NAND");
            break;
        }
        case 4: {
            porta_nor();
            ssd1306_draw_string(ssd, 50, 25, "NOR");
            break;
        }
        case 5: {
            porta_xor();
            ssd1306_draw_string(ssd, 50, 25, "XOR");
            break;
        }
        case 6: {
            porta_xnor();
            ssd1306_draw_string(ssd, 50, 25, "XNOR");
            break;
        }
        default:
            break;
        }

        render_on_display(ssd, &frame_area);
        sleep_ms(100);
    }
}
