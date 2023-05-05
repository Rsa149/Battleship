/****************************************************
Programmer : Ramanpreet Singh
Student # : 200384219
Course : ENSE 352
Project Name : Battleship
****************************************************/

/***********************************************
Description : I designed a game name battleship where 
Player 1 have to set specific lenght of ships which 
are placed on a 2d array sea. Player 2 has to guess
the rows and column where the ship is placed. When 
Player 2 guess the position of the ship it will be an
hit otherwise it will be a miss. Player 2 has to hit
all the co-ordinates of the ship to sunk it. Once
Player 2 sunk all the ships of Player 1 he will win.
****************************************************/

/****************************************************
Hardware Specifications for Output:
- PA0 -----> 1st LED (RED)  ------> MISS
- PA1 -----> 2nd LED (GREEN)------> HIT
- PA2 -----> 3rd LED (RED)  ------> SUNK
- PA3 -----> 4TH LED (GREEN)------> GAME OVER
****************************************************/

/****************************************************
HARWARE SPECIFICATION FOR INPUT
- PC0 -----> SW0
- PC1 -----> SW1
- PC1 -----> SW2
- PC3 -----> SW3
- PC13-----> BLUE BUTTON TO SEND INPUT
****************************************************/

// LIBRARIES USED
#include "../include/battleship.h"
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include <stdlib.h>
#ifdef HARDWARE
#include "../include/io_hw.h"
#else
#include "../include/io.h"
#endif

static struct Vessel vessels[5];

//**************** Main Function*****************
int main(){
		powerPeripherals();
		configureIO();
		setupShips();


		int col,row;   // local variable to take row and column
		bool yes = true;   // is game on ?

		while(yes){         
			bool i_press = false;                         // to check blue buttton pressed
					while(i_press == false){
								i_press = is_Pressed();
								if(i_press == true){
										col = user_input_col();         // take col value
										delay();
									}
							}
			i_press = false;
					while(i_press == false){
						i_press = is_Pressed();
							if(i_press == true){
										row = user_input_row();         // take row value
										delay();
								}
						}

		bool re = false;
					
		switch (shoot(col,row)){
				case true :

						hit_led();                               // hit ship
						//for( int i = 0 ; i < 5 ; i++){         // uncomment this for 5 ships
								if (vessels[4].track == 0){
										hit_sunk_led();                  // sunk ship
										vessels[4].track--;
									}
								//}                                  // uncomment this for 5 ships
						//for( int i = 0 ; i < 5 ; i++){          // uncomment this for 5 ships
								if(game_over() == true){
										game_over_led();                 // game over
									}
								//}
							
				break;
								
				case false :
					    if(error() == true)
						{
							re_hit_led();
						}
						else{
							miss_led();                           // miss hit
						re = false;
						}
			break;
			}
	}
	return 0;
}

//*************Set Up Ships ****************************   // uncomment this for 5 ships
void setupShips(void){
/*strcpy(vessels[0].name, "Carrier");
vessels[0].sunk = false;
vessels[0].length = 5;
vessels[0].track = 5;
vessels[0].vesselLocations[0].c = 2;
vessels[0].vesselLocations[0].r = 2;
vessels[0].vesselLocations[1].c = 2;
vessels[0].vesselLocations[1].r = 3;
vessels[0].vesselLocations[2].c = 2;
vessels[0].vesselLocations[2].r = 4;
vessels[0].vesselLocations[3].c = 2;
vessels[0].vesselLocations[3].r = 5;
vessels[0].vesselLocations[4].c = 2;
vessels[0].vesselLocations[4].r = 6;

strcpy(vessels[1].name, "Battleship");
vessels[1].sunk = false;
vessels[1].length = 4;
vessels[1].track = 4;
vessels[1].vesselLocations[0].c = 0x5;
vessels[1].vesselLocations[0].r = 1;
vessels[1].vesselLocations[1].c = 6;
vessels[1].vesselLocations[1].r = 1;
vessels[1].vesselLocations[2].c = 7;
vessels[1].vesselLocations[2].r = 1;
vessels[1].vesselLocations[3].c = 8;
vessels[1].vesselLocations[3].r = 1;

strcpy(vessels[2].name, "Cruiser");
vessels[2].sunk = false;
vessels[2].length = 3;
vessels[2].track = 3;
vessels[2].vesselLocations[0].c = 5;
vessels[2].vesselLocations[0].r = 4;
vessels[2].vesselLocations[1].c = 5;
vessels[2].vesselLocations[1].r = 5;
vessels[2].vesselLocations[2].c = 5;
vessels[2].vesselLocations[2].r = 6;


strcpy(vessels[3].name, "Submarine");
vessels[3].sunk = false;
vessels[3].length = 3;
vessels[3].track = 3;
vessels[3].vesselLocations[0].c = 0;
vessels[3].vesselLocations[0].r = 1;
vessels[3].vesselLocations[1].c = 1;
vessels[3].vesselLocations[1].r = 1;
vessels[3].vesselLocations[2].c = 2;
vessels[3].vesselLocations[2].r = 1;
*/
strcpy(vessels[4].name, "Destroyer");
vessels[4].sunk = false;
vessels[4].length = 2;
vessels[4].track = 2;
vessels[4].vesselLocations[0].c = 4;
vessels[4].vesselLocations[0].r = 3;
vessels[4].vesselLocations[1].c = 3;
vessels[4].vesselLocations[1].r = 3;

}

// ********* Oprning the specific ports********************
void powerPeripherals(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;  // Open Port A and B and C
}

//************ Configure the clock **************************
void configureIO(){
GPIOA->CRL |=  GPIO_CRL_MODE5_0 |  GPIO_CRL_MODE5_1;      //STM Green Led
GPIOA->CRL &= ~GPIO_CRL_CNF5_0 &~ GPIO_CRL_CNF5_1;

GPIOA->CRL |=  GPIO_CRL_MODE0_0 |  GPIO_CRL_MODE0_1;     // First Led
GPIOA->CRL &= ~GPIO_CRL_CNF0_0 &~ GPIO_CRL_CNF0_1;

GPIOA->CRL |=  GPIO_CRL_MODE1_0 |  GPIO_CRL_MODE0_1;     // Second Led
GPIOA->CRL &= ~GPIO_CRL_CNF1_0 &~ GPIO_CRL_CNF0_1;

GPIOA->CRL |=  GPIO_CRL_MODE4_0 |  GPIO_CRL_MODE0_1;     // Third Led
GPIOA->CRL &= ~GPIO_CRL_CNF4_0 &~ GPIO_CRL_CNF0_1;

GPIOA->CRL |=  GPIO_CRL_MODE6_0 |  GPIO_CRL_MODE0_1;     // fOURTH Led
GPIOA->CRL &= ~GPIO_CRL_CNF6_0 &~ GPIO_CRL_CNF0_1;
	
	GPIOA->CRL |=  GPIO_CRL_MODE5_0 |  GPIO_CRL_MODE0_1;     // error Led
GPIOA->CRL &= ~GPIO_CRL_CNF5_0 &~ GPIO_CRL_CNF0_1;

}


/**************** GLOW LED'S*****************
Thses functions will glow the led's
*********************************************/
void miss_led(){
	GPIOA->ODR |= GPIO_ODR_ODR0;
	delay();
	GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR0;
	delay();
}
void hit_led(){
  GPIOA->ODR |= GPIO_ODR_ODR1;
	delay();
	GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR1;
	delay();
}
void hit_sunk_led(){
	GPIOA->ODR |= GPIO_ODR_ODR4;
	delay();
	GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR4;
	delay();
}
void game_over_led(){
	GPIOA->ODR |= GPIO_ODR_ODR6;
	delay();

}

void re_hit_led(){
	GPIOA->ODR |= GPIO_ODR_ODR5;
	delay();

}

//************Take input row from user*******************
int user_input_row(){
	int address = 0x40011008;
	int *p = address;
	int input = *p & 0x0000000F;
	return input;
}

//************Take input col from user*******************
int user_input_col(){
	int address = 0x40011008;
	int *p = address;
	int input = *p & 0x0000000F;
	return input;
}


// To check if button is pressed 
bool is_Pressed(){
	int pressed = (GPIOC -> IDR & GPIO_IDR_IDR13);
		if (pressed == 0x0){
			return true;
			}
		else {
			return false;
			}
}

//*******To delay the process **************
void delay(){
unsigned volatile int c, d;
     for (c = 1; c <= 3000; c++)
       for (d = 1; d <= 3000; d++)
       {}
}

// *************To shoot on ships ******************************
bool shoot(int col, int row){
		for( int i = 0 ; i < 5 ; i++){
				for( unsigned  int j = 0 ; j < vessels[i].length ; j++ ){
								if (( vessels[i].vesselLocations[j].c == col) && (vessels[i].vesselLocations[j].r == row)) {   // if hit
											//if(( vessels[i].vesselLocations[j].c == 0) && (vessels[i].vesselLocations[j].r == 0)){      
												//	return false;  // re-hit
												//}
											vessels[i].vesselLocations[j].c = 0;  // hit once then change to zero
											vessels[i].vesselLocations[j].r = 0;  // hit once then change to zero
											vessels[i].track = vessels[i].track - 1 ; // track of ships
											if (vessels[i].track == 0){						// if hit all co-ordinates of ship
														vessels[i].sunk = true;  
													}
										return true;   // hit
									}
						}
			}
return false;     // miss hit
}

bool error(){
	for( int i = 0 ; i < 5 ; i++){
				for( unsigned  int j = 0 ; j < vessels[i].length ; j++ ){
						if(( vessels[i].vesselLocations[j].c == 0) && (vessels[i].vesselLocations[j].r == 0)){      
													return true;  // re-hit
												}
						else {
						return false;
						}
				}
			}

}

//***********GAME OVER *******************************************
bool game_over(){
			if(( vessels[4].sunk)  == true){     // Put this in if statement for 5 ships ( ( vessels[0].sunk) && vessels[1].sunk) && vessels[2].sunk) && vessels[3].sunk) && vessels[4].sunk) ) 
					return true;
				}
			else{
			return false;
			}
}

// **************END CODE ***********************************


