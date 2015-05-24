#ifndef KEYB_H
#define KEYB_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include "main.h"

#define DELAY 50

bool keyPressed(Uint8 *keystates);
void delay(int *delay_array, int *press_date, Uint8 *keystates);

#endif
