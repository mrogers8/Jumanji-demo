/*
 * stepper_control.c
 * 
 * Controller for Stepper Motors
 */
#include "../include/stepper.h"
#include "../include/stepper_control.h"


volatile int player_space[4] = {0,0,0,0}

//*****************************************************************************
// stepper_player_start 
// Moves Stepper Motor to Player's starting space
//
// player_num   which player 0-3 is being moved
//*****************************************************************************
int stepper_player_start (int player_num)
{
  int move_x, move_y;

  if (player_space[player_num] == 0) {
	move_x = SPACE_START_X[player_num];
	move_y = SPACE_START_Y[player_num];
  } else {
	//TODO Player Position struct

  }


  return step_position(move_x, move_y);
}


//*****************************************************************************
// stepper_control 
// Control stepper motors to move player to correct space
//
// **Assumption: Electromagnet already positioned in correct place
//
// player_num   which player 0-3 is being moved
// player_start space of player start
// player_end   space of player end
//*****************************************************************************
int stepper_control (int player_num, int player_start, int player_end)
{
  int temp_start = player_start;
  int temp_end = 0;

  // Activate Electromagnet
  electro_mag_on();

  while (temp_end != player_end) {
	//detect turns
	if (temp_start < SPACE_TURN_0 && player_end > SPACE_TURN_0) {
	   //turn 0
	   temp_end = SPACE_TURN_0;
	} else if (temp_start < SPACE_TURN_1 && player_end > SPACE_TURN_1) {
	   //turn 1
	   temp_end = SPACE_TURN_1;
	} else if (temp_start < SPACE_TURN_2 && player_end > SPACE_TURN_2) {
	   //turn 2
	   temp_end = SPACE_TURN_2;
	} else if (temp_start < SPACE_TURN_3 && player_end > SPACE_TURN_3) {
	   //turn 3
	   temp_end = SPACE_TURN_3;
	} else {
	   //no turns
	   temp_end = player_end;
	}
	
	//move one segment
	stepper_line_move(player_num, temp_start, temp_end);

	temp_start = temp_end;
  }

  // Deactivate Electromagnet
  electro_mag_off();

}


//*****************************************************************************
// stepper_line_move 
// Programs movement for 1D movement of a piece
//
//*****************************************************************************
int stepper_line_move (int player_num, int space_start, int space_end) 
{
  int direction;
  int steps;

  // Get Direction
  direction = determine_direction(player_num, space_start, space_end);
  if (direction == 5) return 1;

  // Get Steps
  steps = (space_end - space_start) * STEPS_PER_SPACE; 

  // Drag piece to correct spot
  if (direction < 2) 	return step_x(steps, direction);
  else 			return step_y(steps, direction);
}

//*****************************************************************************
// determine_direction 
// Returns numeric direction value based on player leg of movement
//   North : 0
//   South : 1
//   East  : 2
//   Wets  : 3
//
// Errors if turns are present in movement
//*****************************************************************************
int determine_direction (int player_num, int space_start, int space_end)
{
  if (space_end < SPACE_TURN_0 && space_start < SPACE_TURN_0) {
	switch (player_num) {
	   case 0 : return DIR_P0_LEG_0;
	   case 1 : return DIR_P1_LEG_0;
	   case 2 : return DIR_P2_LEG_0;
	   case 3 : return DIR_P3_LEG_0;
	} 
  } else if (space_end < SPACE_TURN_1 && space_start < SPACE_TURN_1) {
	switch (player_num) {
	   case 0 : return DIR_P0_LEG_1;
	   case 1 : return DIR_P1_LEG_1;
	   case 2 : return DIR_P2_LEG_1;
	   case 3 : return DIR_P3_LEG_1;
	} 
  } else if (space_end < SPACE_TURN_2 && space_start < SPACE_TURN_2) {
	switch (player_num) {
	   case 0 : return DIR_P0_LEG_2;
	   case 1 : return DIR_P1_LEG_2;
	   case 2 : return DIR_P2_LEG_2;
	   case 3 : return DIR_P3_LEG_2;
	} 
  } else if (space_end < SPACE_TURN_3 && space_start < SPACE_TURN_3) {
	switch (player_num) {
	   case 0 : return DIR_P0_LEG_3;
	   case 1 : return DIR_P1_LEG_3;
	   case 2 : return DIR_P2_LEG_3;
	   case 3 : return DIR_P3_LEG_3;
	} 
  } else if (space_end > SPACE_TURN_3 && space_start > SPACE_TURN_3) {
	switch (player_num) {
	   case 0 : return DIR_P0_LEG_4;
	   case 1 : return DIR_P1_LEG_4;
	   case 2 : return DIR_P2_LEG_4;
	   case 3 : return DIR_P3_LEG_4;
	} 
  } else { 
	printf("Invalid space line calculated: contains turn\n");
	return 5;
  }
}
