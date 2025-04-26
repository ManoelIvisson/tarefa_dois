#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

#define BOTAO_A 5
#define BOTAO_B 6

#define LED_VERMELHO 13
#define LED_VERDE 11

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

    while (true) {
        porta_xnor();

        sleep_ms(100);
    }
}
