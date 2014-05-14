// Created by Mustafa Tosun
#ifndef HW_H
#define HW_H

#include <bcm2835.h>
#include <stdlib.h>
#include <stdio.h>

#define BUTTON_0 RPI_GPIO_P1_16
#define BUTTON_1 RPI_GPIO_P1_18

#define LED_0 RPI_GPIO_P1_15
#define LED_1 RPI_GPIO_P1_22
#define LED_2 RPI_GPIO_P1_24
#define LED_3 RPI_GPIO_P1_26

// Functions for Raspberry PI lab
void initButtons( void );
void initLEDs( void );
uint8_t getButton( uint8_t pin );
void setLED(uint8_t pin, uint8_t on);

#endif
