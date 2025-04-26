#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

#define BOTAO_A 5
#define BOTAO_B 6

#define LED_VERMELHO 13
#define LED_VERDE 11

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

// Simula a porta AND (E ou Conjunção)
void porta_and() {
    if (gpio_get(BOTAO_A) == 0 && gpio_get(BOTAO_B) == 0) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

// Simula a porta OR (Ou ou Disjunção)
void porta_or() {
    if (gpio_get(BOTAO_A) == 0 || gpio_get(BOTAO_B) == 0) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

// Simula a porta NOT (Negação)
void porta_not() {
    if (gpio_get(BOTAO_A) == 0) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

// Simula a porta NAND
void porta_nand() {
    if (gpio_get(BOTAO_A) == 0 && gpio_get(BOTAO_B) == 0) {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    } else {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    }
}

// Simula a porta NOR 
void porta_nor() {
    if (gpio_get(BOTAO_A) && gpio_get(BOTAO_B)) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

// Simula a porta XOR (Ou Exclusiva)
void porta_xor() {
    if (gpio_get(BOTAO_A) != gpio_get(BOTAO_B)) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

// Simula a porta XNOR
void porta_xnor() {
    if (gpio_get(BOTAO_A) == gpio_get(BOTAO_B)) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

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

    ssd1306_draw_string(ssd, 80, 80, "Bem-vindos!");
    render_on_display(ssd, &frame_area);

    while (true) {
        porta_xnor();

        sleep_ms(100);
    }
}
