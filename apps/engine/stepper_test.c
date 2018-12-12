/*
 * integration.c
 * Game engine integration tests
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/ece453.h"
#include "../include/stepper_move.h"
#include "../include/electro_mag.h"

extern bool complete_X;
extern bool complete_Y;

int x_pos = 0;
int y_pos = 0;

int x_1 = 550;
int x_2 = 550;
int x_3 = 4100;
int x_4 = 4100;

int y_1 = 2650;
int y_2 = 750;
int y_3 = 2650;
int y_4 = 750;

uint32_t player_space[4] = {1, 1, 1, 1,};

int offset = 350;


int move(int x, int y, int mag) {
  if(mag == 1) {
    electro_mag_on();
  }
  stepper_position(x, y, x_pos, y_pos);
  x_pos = x;
  y_pos = y;
  while (!complete_X || !complete_Y);
  sleep(1);
  electro_mag_off();
  return 1;
}

int movePath(int player, int run, int moveNum) {

  switch (run)
  {
    case 1:

    switch (player)
    {
        case 1:
            move(x_1, y_1, 0);
            move(x_1 = x_1 + offset * moveNum, y_1, 1);
            break;

        case 2:
            move(x_2, y_2, 0);
            move(x_2 = x_2 + offset * moveNum, y_2, 1);
            break;

        case 3:
        move(x_3, y_3, 0);
           move(x_3 = x_3 - offset * moveNum, y_3, 1);
        break;

        case 4:
            move(x_4, y_4, 0);
            move(x_4 = x_4 - offset * moveNum, y_4, 1);
            break;
    }
    break;

    case 2:
      switch (player)
      {
          case 1:
              move(x_1, y_1, 0);
              move(x_1, y_1 = y_1 + offset * moveNum, 1);
              break;

          case 2:
              move(x_2, y_2, 0);
              move(x_2, y_2 = y_2 - offset * moveNum, 1);
              break;

          case 3:
              move(x_3, y_3, 0);
              move(x_3, y_3 = y_3 + offset * moveNum, 1);
              break;

          case 4:
              move(x_4, y_4, 0);
              move(x_4, y_4 = y_4 - offset * moveNum, 1);
              break;
      }
    break;

    case 3:
      switch (player)
      {
          case 1:
              move(x_1, y_1, 0);
              move(x_1 = x_1 - offset * moveNum + 31, y_1, 1);
              break;

          case 2:
              move(x_2, y_2, 0);
              move(x_2 = x_2 - offset * moveNum + 31, y_2, 1);
              break;

          case 3:
              move(x_3, y_3, 0);
              move(x_3 = x_3 + offset * moveNum, y_3, 1);
              break;

          case 4:
              move(x_4, y_4, 0);
              move(x_4 = x_4 + offset * moveNum, y_4, 1);
              break;
      }
    break;

    case 4:
      switch (player)
      {
          case 1:
              move(x_1, y_1, 0);
            move(x_1, y_1 = y_1 - offset * moveNum, 1);
              break;

          case 2:
              move(x_2, y_2, 0);
              move(x_2, y_2 = y_2 + offset * moveNum, 1);
              break;

          case 3:
              move(x_3, y_3, 0);
              move(x_3, y_3 = y_3 - offset * moveNum, 1);
              break;

          case 4:
              move(x_4, y_4, 0);
              move(x_4, y_4 = y_4 + offset * moveNum, 1);
              break;
      }
    break;

    case 5:
      switch (player)
      {
          case 1:
              move(x_1, y_1, 0);
              move(x_1 = x_1 + offset * moveNum, y_1, 1);
              break;

          case 2:
              move(x_2, y_2, 0);
              move(x_2 = x_2 + offset * moveNum, y_2, 1);
              break;

          case 3:
              move(x_3, y_3, 0);
              move(x_3 = x_3 - offset * moveNum, y_3, 1);
              break;

          case 4:
              move(x_4, y_4, 0);
              move(x_4 = x_4 - offset * moveNum, y_4, 1);
              break;
      }
    break;
  }
}

//*****************************************************************************
//*****************************************************************************
int move_player (int player, int startSpace, int endSpace) {
  //printf("Move_player %d -> %d\n", startSpace, endSpace);
    for(int i = startSpace; i < endSpace; i++) {
      if(i < 4) {
        movePath(player, 1, 1);
      } else if (i >= 4 && i < 6) {
          movePath(player, 2, 1);
      } else if (i >= 6 && i < 11) {
          movePath(player, 3, 1);
      } else if (i >= 11 && i < 15) {
          movePath(player, 4, 1);
      } else if (i >= 15 && i < 20) {
          movePath(player, 5, 1);
      } else {

      }
    }
    player_space[player-1] = endSpace;
}

//*****************************************************************************
int game_initialization_module ()
{
  //****************************
  // Game Initialization
  //****************************
  int button_press;
  int num_players;

  leds_set_all();
  printf("Welcome to Jumanji\n************************\n");
  printf("Press any button to continue\n");
  //leds_s
  //lcd_play_image();       //TODO: add press any button to continue
  while (!buttons_read_all());
  sleep(1);
  while (buttons_read_all());


  // Determine player count

  //lcd_play_image();       //TODO: add press for the number of players
  printf("Enter number of Players RED = 1, Orange = 2, Green = 3, Blue = 4\n************************\n");

  while (!(button_press = buttons_read_all()));
  sleep(1);
  while (buttons_read_all());

        if(button_press == 8) {
            num_players = 1;
            leds_clear_all();
            leds_set_red();
            sleep(1);
        } else if (button_press == 4) {
            num_players = 2;
            leds_clear_all();
            leds_set_orange();
            sleep(1);
        } else if (button_press == 2) {
            num_players = 3;
            leds_clear_all();
            leds_set_green();
            sleep(1);
        } else if (button_press == 1) {
            num_players = 4;
            leds_clear_all();
            leds_set_blue();
            sleep(1);
        } else {
            return -1;
            //printf("ERROR: invalid button value\n");
        }


  printf("You have selected %d players\n", num_players);
  return num_players;
}

int dice_module(int roll_max) {
    int dice_roll;
    // Initialize the dice module
    //lcd_play_image();              //TODO: add dice image
    dice_roll = generate_number(roll_max);

    // Wait for a button press
    leds_set_all();
    printf("Press button to roll\n************************\n");
    while (!buttons_read_all());
    sleep(1);
    leds_clear_all();
    while (buttons_read_all());

    printf("  You have rolled a %i\n", dice_roll);

    return dice_roll;
}

void buttons_debounce(void)
{
  while (!buttons_read_all());
  sleep(1);
}


int decode() {
    int buttonsVal;
    char code[5];

    leds_set_all();
    for(int i = 0; i < 4; i++) {
        while (!(buttonsVal = buttons_read_all()));
	buttons_debounce();
	//printf("DECODE: i=%i, buttonsVal=%i\n", i, buttonsVal);

        if(buttonsVal == 8) {
            code[i] = 'R';
            leds_clear_red();
        } else if (buttonsVal == 4) {
            code[i] = 'O';
            leds_clear_orange();
        } else if (buttonsVal == 2) {
            code[i] = 'G';
            leds_clear_green();
        } else if (buttonsVal == 1) {
            code[i] = 'B';
            leds_clear_blue();
        } else {
            return -1;
        }
    }


    for(int i = 0; i < 11; i++) {
    	for(int j = 0; j < 4; j++) {
	   if (code[j] != cardDefinitions[i].code[j]) break;
	   else if (j == 3) return i;
	}
    }

    //printf("DEFAULT: QUICKSAND\n");
    return 11;

}

const int RIVER_BEGIN = 11;
const int RIVER_END = 15;


int riddle_module(int player_num)
{
  uint16_t card_index;
  uint16_t dice_roll;

  leds_clear_all();
  if (player_space[player_num-1] >= RIVER_BEGIN && player_space[player_num-1] <= RIVER_END){
    //lcd_play_image("DRAW RIVER CARD") //SLIDESHOW
    // RIVER DECODE
    printf("Draw a River Card\n************************\n");
  } else {
    //lcd_play_image("DRAW A JUNGLE CARD") //SLIDESHOW
    printf("Draw a Jungle Card\n************************\n");
  }

  printf("Decode Card\n");
  card_index = decode();

  //lcd_play_image(cardDefinitions[card_index].mpv_inst);
  printf("You Drew: %s\nYou need to roll a %d to move %d spaces\n", cardDefinitions[card_index].name, cardDefinitions[card_index].magic_roll, cardDefinitions[card_index].space_reward);


  int pass = 0;

  //printf("Press any button to roll\n************************\n");
  for(int i = 0; i < 3; i++) {
    int dice_roll;
    if(dice_roll = dice_module(6) == cardDefinitions[card_index].magic_roll) {
        pass = 1;
        //printf("You rolled a: %d\n************************\n", dice_roll);
        //lcd_play_image dice shit
        break;
    }
  }

  if(pass == 1) {
      leds_set_all();
      sleep(1);
      leds_clear_all();
      sleep(1);
      leds_set_all();
      //lcd_play_image(cardDefinitions[card_index].mpv_win);
      printf("You pass! Move Forward: %d\n", cardDefinitions[card_index].space_reward);
      return move_player(player_num, player_space[player_num-1], player_space[player_num-1] + cardDefinitions[card_index].space_reward);
  } else {
      leds_set_all();
      sleep(1);
      leds_clear_all();
      sleep(1);
      leds_set_all();
      //lcd_play_image(cardDefinitions[card_index].mpv_lose);
      printf("You failed! Remain Here\n");
      //stepper_move_module(player_num, -1 * cardDefinitions[card_index].space_reward);
      return 0;
  }

}

//*****************************************************************************
int main(int argc, char **argv)
{
  // Local Variables
  char response[80];
  int dice_roll;
  int game_won = 0;
  int num_players;
  int player_curr = 1;

  // Hardware Initialization
  stepper_hw_init();


  //printf("MAIN: Testing Reset\n");
  stepper_reset();
  sleep(3);
  //printf("MAIN: Stepper reset complete\n");

  int offset = 350;


  num_players = game_initialization_module();



  while(!game_won) {
    printf("Player %d's turn has begun!\n", player_curr);
    //printf("[%d, %d, %d, %d]\n", player_space[0], player_space[1], player_space[2], player_space[3]);

    int endSpace;
    dice_roll = dice_module(6);

    endSpace = player_space[player_curr-1] + dice_roll;
    if (endSpace >= 20) {
      endSpace = 20;
    }
    move_player(player_curr, player_space[player_curr-1], endSpace);
    // CHECK FOR WIN
    if (player_space[player_curr-1] >= 20) {
      game_won = 1;
      printf("You have won Jumanji.\n");

    } else {
      riddle_module(player_curr);
    }
    player_curr ++;
    if (player_curr == 5) player_curr = 1;
  }

  while(1){
  leds_clear_all();
  leds_set_red();
  sleep(1);
  leds_set_orange();
  sleep(1);
  leds_set_green();
  sleep(1);
  leds_set_blue();
}

  return 0;
}
