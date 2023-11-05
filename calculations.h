/*STAN Andrei - 314CC*/
#include <stdio.h>

#include "data.h"

unsigned char avereage_red(IMAGE *pic, int x, int y, int size);
unsigned char avereage_green(IMAGE *pic, int x, int y, int size);
unsigned char avereage_blue(IMAGE *pic, int x, int y, int size);
unsigned long long calculate_mean(IMAGE *pic,int x,int y,int size);