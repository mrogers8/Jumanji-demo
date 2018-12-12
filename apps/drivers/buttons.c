/*
 * buttons.c
 */
#include "../include/buttons.h"


//*****************************************************************************
// PUSH BUTTONS WITH LEDS
//*****************************************************************************
int buttons_read_all (void)
{
  return ece453_reg_read(BUTTONS_REG);
}

int buttons_read_red (void)
{
  return (ece453_reg_read(BUTTONS_REG) & BUTTONS_RED) >> 3;
} 

int buttons_read_orange (void)
{
  return (ece453_reg_read(BUTTONS_REG) & BUTTONS_ORA) >> 2;
}

int buttons_read_green (void)
{
  return (ece453_reg_read(BUTTONS_REG) & BUTTONS_GRE) >> 1;
}

int buttons_read_blue (void)
{
  return (ece453_reg_read(BUTTONS_REG) & BUTTONS_BLU);
}


//*****************************************************************************
// SWITCHES FOR XY PLOTTER 
//*****************************************************************************
int buttons_read_x_min (void)
{
//  printf("DEBUG: buttons_read_x_min [%i] masked [%i] shifted [%i]\n", ece453_reg_read(SWITCHES_REG), (ece453_reg_read(SWITCHES_REG) & BUTTONS_X_MIN),  (ece453_reg_read(SWITCHES_REG) & BUTTONS_X_MIN));
  return (ece453_reg_read(SWITCHES_REG) & BUTTONS_X_MIN);
} 

int buttons_read_x_max (void)
{
  return (ece453_reg_read(SWITCHES_REG) & BUTTONS_X_MAX) >> 1;
}

int buttons_read_y_min (void)
{
//  printf("DEBUG: buttons_read_y_min [%i] masked [%i] shifted [%i]\n", ece453_reg_read(SWITCHES_REG), (ece453_reg_read(SWITCHES_REG) & BUTTONS_Y_MIN),  (ece453_reg_read(SWITCHES_REG) & BUTTONS_Y_MIN) >> 2);
  return (ece453_reg_read(SWITCHES_REG) & BUTTONS_Y_MIN) >> 2;
}

int buttons_read_y_max (void)
{
  return (ece453_reg_read(SWITCHES_REG) & BUTTONS_Y_MAX) >> 3;
}


