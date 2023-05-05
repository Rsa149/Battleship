#include "stdbool.h"

void powerPeripherals(void);
void configureIO(void);
void turnOnLED(void);
void delay(void);
bool is_Pressed(void);
int user_input_row(void);
int user_input_col(void);
void miss_led(void);
void hit_led(void);
void hit_sunk_led(void);
void game_over_led(void);
bool shoot(int, int);
void sunk(void);
bool game_over(void);
void re_hit_led(void);
void setupShips(void);
bool error(void);



struct Location {
	int c;
	int r;
};

struct Vessel {
	char name[20];
	bool sunk;
	unsigned int length;
	int track;
	struct Location vesselLocations[5];
	bool hits[5];
};

