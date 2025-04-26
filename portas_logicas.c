#define BOTAO_A 5
#define BOTAO_B 6

#define LED_VERMELHO 13
#define LED_VERDE 11

// Simula a porta AND (E ou Conjunção)
void porta_and() {
    if (gpio_get(BOTAO_A) && gpio_get(BOTAO_B)) {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    } else {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    }
}

// Simula a porta OR (Ou ou Disjunção)
void porta_or() {
    if (gpio_get(BOTAO_A) || gpio_get(BOTAO_B)) {
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
    if (gpio_get(BOTAO_A) && gpio_get(BOTAO_B)) {
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 0);
    } else {
        gpio_put(LED_VERMELHO, 0);
        gpio_put(LED_VERDE, 1);
    }
}

// Simula a porta NOR 
void porta_nor() {
    if (gpio_get(BOTAO_A) == 0 && gpio_get(BOTAO_B) == 0) {
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