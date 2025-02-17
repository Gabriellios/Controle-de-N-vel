#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

#define LED1_PIN 11
#define LED2_PIN 12
#define LED3_PIN 13

#define BTN1_PIN 3
#define BTN2_PIN 4
#define BTN3_PIN 5

#define RELE_PIN 15

volatile bool aciona_rele_btn1 = false;  // Flag para relé acionado pelo botão 1
volatile bool aciona_rele_btn3 = false;  // Flag para relé acionado pelo botão 3

// Função de interrupção para bordas
void gpio_irq_callback(uint gpio, uint32_t events) {
    if (gpio == BTN1_PIN) {
        aciona_rele_btn1 = true;  // Sinaliza acionamento pelo botão 1
    }
    if (gpio == BTN3_PIN) {
        aciona_rele_btn3 = true;  // Sinaliza acionamento pelo botão 3
    }
}

// Função para ligar o relé por 0,5 segundos
void acionar_rele() {
    gpio_put(RELE_PIN, 1);  // Liga o relé
    sleep_ms(500);          // Aguarda 0,5 segundos
    gpio_put(RELE_PIN, 0);  // Desliga o relé
}

int main() {
    stdio_init_all();

    // Configuração dos botões
    gpio_init(BTN1_PIN);
    gpio_set_dir(BTN1_PIN, GPIO_IN);

    gpio_init(BTN2_PIN);
    gpio_set_dir(BTN2_PIN, GPIO_IN);

    gpio_init(BTN3_PIN);
    gpio_set_dir(BTN3_PIN, GPIO_IN);

    // Configuração dos LEDs
    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_put(LED1_PIN, 0);

    gpio_init(LED2_PIN);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_put(LED2_PIN, 0);

    gpio_init(LED3_PIN);
    gpio_set_dir(LED3_PIN, GPIO_OUT);
    gpio_put(LED3_PIN, 0);

    // Configuração do relé
    gpio_init(RELE_PIN);
    gpio_set_dir(RELE_PIN, GPIO_OUT);
    gpio_put(RELE_PIN, 0);

    // Configuração das interrupções
    gpio_set_irq_enabled_with_callback(BTN1_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_irq_callback);
    gpio_set_irq_enabled_with_callback(BTN3_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_callback);

    while (1) {
        // Atualiza os LEDs com base nos estados dos botões
        gpio_put(LED1_PIN, gpio_get(BTN1_PIN));
        gpio_put(LED2_PIN, gpio_get(BTN2_PIN));
        gpio_put(LED3_PIN, gpio_get(BTN3_PIN));

        // Verifica flags de acionamento do relé
        if (aciona_rele_btn1) {
            acionar_rele();      // Aciona o relé para o botão 1
            aciona_rele_btn1 = false;  // Reseta a flag
        }

        if (aciona_rele_btn3) {
            acionar_rele();      // Aciona o relé para o botão 3
            aciona_rele_btn3 = false;  // Reseta a flag
        }
    }
}
