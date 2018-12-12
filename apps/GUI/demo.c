#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/ece453.h"

/*
 * lcd.c
 * LCD IMAGE PLAYER
 */
#include "../include/ece453.h"


//Magic Dice Numbers
// 1 = Flashlight
// 2 = Fire
// 3 = Axe
// 4 = Rope
// 5 = Sword
// 6 = Time


//*****************************************************************************
// Constants for Image File Commands
//*****************************************************************************

const Card cardDefinitions[12] = {
                                    {
                                        "RiverCrocodiles", //card name
                                        1,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        3,                //number to win
                                        3,                //number of spaces to move
                                        "RGBO",
                                        "mpv --image-display-duration=10 video/RiverCrocodiles.png",   //img command
                                        "mpv --image-display-duration=10 video/RiverCrocodilesPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/RiverCrocodilesFail.png",                  //img command fail
                                    },
                                    {
                                        "RiverFork", //card name
                                        1,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        1,                //number to win
                                        1,                //number of spaces to move
                                        "RGOB",
                                        "mpv --image-display-duration=10 video/RiverFork.png",                  //img command
                                        "mpv --image-display-duration=10 video/RiverForkPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/RiverForkFail.png",                  //img command fail
                                    },
                                    {
                                        "RiverPiranhas", //card name
                                        1,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        5,                //number to win
                                        3,                //number of spaces to move
                                        "RBGO",
                                        "mpv --image-display-duration=10 video/RiverPiranhas.png",                  //img command
                                        "mpv --image-display-duration=10 video/RiverPiranhasPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/RiverPiranhasPass.png",                  //img command fail
                                    },
                                    {
                                        "RiverRaft", //card name
                                        1,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        1,                //number to win
                                        1,                //number of spaces to move
                                        "RBOG",
                                        "mpv --image-display-duration=10 video/RiverRaft.png",                  //img command
                                        "mpv --image-display-duration=10 video/RiverRaft.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/RiverRaft.png",                  //img command fail
                                    },
                                    {
                                        "RiverWaterfall", //card name
                                        1,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        4,                //number to win
                                        2,                //number of spaces to move
                                        "GRBO",
                                        "mpv --image-display-duration=10 video/RiverWaterfall.png",                  //img command
                                        "mpv --image-display-duration=10 video/RiverWaterfallPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/RiverWaterfallFail.png",                  //img command fail
                                    },
                                    {
                                        "RiverWhirlpool", //card name
                                        1,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        4,                //number to win
                                        2,                //number of spaces to move
                                        "GROB",
                                        "mpv --image-display-duration=10 video/RiverWhirlpool.png"                  //img command
                                        "mpv --image-display-duration=10 video/RiverWhirlpoolPass.png"                  //img command pass
                                        "mpv --image-display-duration=10 video/RiverWhirlpoolFail.png"                  //img command fail
                                    },
                                    {
                                        "JungleBats",	  //card name
                                        0,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        1,                //number to win
                                        2,                //number of spaces to move
                                        "GBRO",
                                        "mpv --image-display-duration=10 video/JungleBats.png",                  //img command
                                        "mpv --image-display-duration=10 video/JungleBatsPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/JungleBatsFail.png",                  //img command fail
                                    },
                                    {
                                        "JunglePelican",  //card name
                                        0,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        4,                //number to win
                                        1,                //number of spaces to move
                                        "GBOR",
                                        "mpv --image-display-duration=10 video/JunglePelican.png",                  //img command
                                        "mpv --image-display-duration=10 video/JunglePelicanPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/JunglePelicanFail.png",                  //img command fail
                                    },
                                    {
                                        "JunglePlants",	  //card name
                                        0,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        3,                //number to win
                                        2,                //number of spaces to move
                                        "BGRO",
                                        "mpv --image-display-duration=10 video/JunglePlants.png",                  //img command
                                        "mpv --image-display-duration=10 video/JunglePlantsPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/JunglePlantsFail.png",                  //img command fail
                                    },
                                    {
                                        "JungleSnakes",   //card name
                                        0,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        5,                //number to win
                                        3,                //number of spaces to move
                                        "BGOR",
                                        "mpv --image-display-duration=10 video/JungleSnakes.png",                  //img command
                                        "mpv --image-display-duration=10 video/JungleSnakesPass.png",                  //img command pass
                                        "mpv --image-display-duration=10 video/JungleSnakesFail.png",                  //img command fail
                                    },
                                    {
                                        "JungleStampede", //card name
                                        0,                //card type 1 = River 0 = Jungle
                                        3,                //number of chances to Roll
                                        2,                //number to win
                                        3,                //number of spaces to move
                                        "BRGO",
                                        "mpv --image-display-duration=10 video/JungleStampede.png",                  //img command
                                        "mpv --image-display-duration=10 video/JungleStampedePass.png"  ,                //img command pass
                                        "mpv --image-display-duration=10 video/JungleStampedeFail.png"                  //img command fail
                                    },
                                    {
                                        "Quicksand",	  //card name
                                        2,                //card type 1 = River 0 = Jungle
                                        1,                //number of chances to Roll
                                        3,                //number to win
                                        1,                //number of spaces to move
                                        "OGBR",
                                        "mpv --image-display-duration=10 video/Quicksand.png",                  //img command
                                        "mpv --image-display-duration=10 video/QuicksandPass.png",                   //img command pass
                                        "mpv --image-display-duration=10 video/QuicksandFail.png"                   //img command fail
                                    }

                                };



//*****************************************************************************
//*****************************************************************************
int main(int argc, char **argv)
{
  char response[80];


  //Wait for the user to indicate how many steps to move
  while(1) {
      printf("\n\n********************************\nEnter decode card : ");
      fgets(response, 79,stdin);
	printf("\n********************************\n");
    int buttonsVal;
    char code[5];

    int card = 11;
    for(int i = 0; i < 11; i++) {
        	  for(int j = 0; j < 4; j++) {
		         if (response[j] != cardDefinitions[i].code[j]) {
				card = i;
				break;
			
			}
         		else if (j == 3) return i;
    		}

	}
    system(cardDefinitions[card].mpv_inst);

  }
}
