/*
 * drivers.h
 *
 *  Created on: Oct 21, 2024
 *      Author: jcool
 */

#ifndef DRIVERS_H_
#define DRIVERS_H_

#include <stdint.h>


typedef struct{
	uint32_t MODER;   // offset: 0x00
	uint32_t OTYPER;  // offset: 0x04
	uint32_t OSPEEDR; // offset: 0x08
	uint32_t PUPDR;   // offset: 0x0C
	uint32_t IDR;     // offset: 0x10
	uint32_t ODR;     // offset: 0x14
} Port;

// Address of the Advanced High-performance Bus 2 Enable Register
#define AHB2ENR ((uint32_t*) 0x4002104C)

// Base addresses of the GPIO Port control registers (SFRs)
#define GPIOA ((Port*) 0x48000000) // base address of GPIOA
#define GPIOB ((Port*) 0x48000400) // base address of GPIOB
#define GPIOC ((Port*) 0x48000800) // base address of GPIOC

//functions prototypes
void GPIOA_ClkEnable(void);
void GPIOB_ClkEnable(void);
void GPIOC_ClkEnable(void);
void GPIO_Mode(Port* GPIOx, uint32_t pin, uint32_t mode);
void GPIO_Pull(Port* GPIOx, uint32_t pin, uint32_t pull);
void GPIO_TogglePin(Port* GPIOx, uint32_t pin);
void GPIO_WritePin(Port* GPIOx, uint32_t pin, uint32_t state);
uint32_t GPIO_ReadPin(Port* GPIOx, uint32_t pin);

//Value macros for MODER
#define GPIO_MODE_INPUT 0
#define GPIO_MODE_OUTPUT 1

// Value macros for PUPDR
#define GPIO_NOPULL   0 // No Pull resistor
#define GPIO_PULLUP   1 // Pull-up resistor
#define GPIO_PULLDOWN 2 // Pull-down resistor


// bitmask macros
#define BITMASK(x) (1 << x)
#define BITPAIR(x) (0b11 << (x*2))
#define UBIT(x) (0b10 << (x*2))
#define LBIT(x) (0b01 << (x*2))
#endif /* DRIVERS_H_ */
