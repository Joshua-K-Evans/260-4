// function defintions (aka implementations)
#include "drivers.h"
 void GPIO_Mode(Port* GPIOx, uint32_t pin, uint32_t mode){

	 if (mode == GPIO_MODE_INPUT){
		 GPIOx->MODER &= ~BITPAIR(pin);

	 } else if (mode == GPIO_MODE_OUTPUT){
		uint32_t temp = GPIOx ->MODER;
		temp |= LBIT(pin); 	// reset the lower bits
		temp &= ~UBIT(pin);	// set the upper bits
		GPIOx->MODER = temp;		//start MODER
	 }
 }

 void GPIOA_ClkEnable(void){
	 *AHB2ENR |= 0b001; // set bit 0 for Port A
 }

 void GPIOB_ClkEnable(void){
 	 *AHB2ENR |= 0b010; // set bit 1 for Port B
  }

 void GPIOC_ClkEnable(void){
 	 *AHB2ENR |= 0b100; // set bit 2 for Port C
  }

 void GPIO_Pull(Port* GPIOx, uint32_t pin, uint32_t pull){
	 if (pull == GPIO_NOPULL){
		 GPIOx->PUPDR &= ~BITPAIR(pin);// set null
	 }  else if (pull == GPIO_PULLUP) {
			uint32_t temp = GPIOx->PUPDR; 	// read PUPDR
			temp |=  LBIT(pin);		// set the lower bit
			temp &= ~UBIT(pin); 	// set the upper bit
			GPIOx->PUPDR = temp;			// store PUPDR

		} else if (pull == GPIO_PULLDOWN) {
			uint32_t temp = GPIOx->PUPDR; 	// read PUPDR
			temp &= ~BITPAIR(pin);		// set the lower bit
			temp |= UBIT(pin); 			// set the upper bit
			GPIOx->PUPDR = temp;			// store PUPDR
	}
 }

 void GPIO_TogglePin(Port* GPIOx, uint32_t pin){
	 GPIOx->ODR ^= BITMASK(pin);
 }
 void GPIO_WritePin(Port* GPIOx, uint32_t pin, uint32_t state){
	 if(state != 0){
		 GPIOx->ODR |= BITMASK(pin);
	 }else{
		 GPIOx->ODR &= ~BITMASK(pin);
	 }
 }

 uint32_t GPIO_ReadPin(Port* GPIOx, uint32_t pin){
	 uint32_t value = 0;
	 if((GPIOx->IDR & (BITMASK(pin))) != 0){
		 value = 1;
	 }else {
		 value = 0;
	 }
 return value;
}
