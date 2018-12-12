#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/ece453.h"

//*****************************************************************************
//*****************************************************************************
int main(int argc, char **argv)
{
  char response[80];


  //Wait for the user to indicate how many steps to move
  while(1) {
      printf("Enter decode card : ");
      fgets(response, 79,stdin);
      decode(repsonse);
  }


  return 0;
}

int decode(char * string) {
    int buttonsVal;
    char code[5];


    for(int i = 0; i < 11; i++) {
          for(int j = 0; j < 4; j++) {
         if (string[j] != cardDefinitions[i].code[j]) break;
         else if (j == 3) return i;
    }

    system(cardDefinitions[i].mpv_inst);
}
