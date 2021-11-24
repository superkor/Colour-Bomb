#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include <time.h>

#include "ece198.h"

//Function to set the specific LED (A-G) to a specific colour. All LEDs that should be on are set to false
void SevenSegment_Update(int8_t number){
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, false); //PA12 (11)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, false); //PC2 (10)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, false); //PC13 (5)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, false); //PB7 (4)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, false); //PA14 (2)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, false); //PA13 (1)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, false); //PC3 (7)
    //on a specific digit, show the number
    switch (number){
            case 0:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, true); //PC13 (5)
                break;
            case 1:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, true); //PA12 (11)
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, true); //PC2 (10)
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, true); //PC13 (5)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, true); //PA14 (2)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, true); //PA13 (1)
                break;
            case 2:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, true); //PC2 (10)
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, true); //PB7 (4)
                break;
            case 3:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, true); //PC2 (10)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, true); //PA13 (1)
                break;
            case 4:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, true); //PA14 (2)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, true); //PA13 (1)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, true); //PA12 (11)
                break;
            case 5:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, true); //PA13 (1)
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, true); //PC3 (7)
                
                break;
            case 6:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, true); //PC3 (7)
                break;
            case 7:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, true); //PC2 (10)
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, true); //PC13 (5)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, true); //PA14 (2)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, true); //PA13 (1)
                break;
            case 8:
                break;
            case 9:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, true); //PA14 (2)
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, true); //PA13 (1)
                break;
        }
}

//Function to set the RGB LED a colour based on RGB
uint8_t RGBRan(int8_t seed){
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,false);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, false);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
        int ran = 0;
        uint8_t output = 0;
        srand(seed);
        //generates random number
        ran = rand() %4;
        //depending on ran (random number), set the RGB LED to a colour
        switch(ran){
            case 0 :
                //purple
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,true);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
                output = 0;
                break;
            case 1:
                //teal
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,true);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, true);
                output = 1;
                break;
            case 2:
                //lime
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,true);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, true);
                output = 2;
                break;
            case 3:
                //white
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,true);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, true);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
                output = 3;
                break;
            /* had to remove the single colour options due to compeleting more than one puzzle (since the buttons are held during input so it automatically clears the next puzzle) 
            case 4:
                //red
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,true);
                output = 4;
                break;
            case 5:
                //blue
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
                output = 5;
                break;
            case 6:
                //green
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, true);
                output = 6;
                break; */
        }
        //return what colour the RGB is showing
        return output;
}

//Fail function
void fail(void){
    //Turn off all the LEDs and turn on the red LED to indicate game is over.
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
}

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    //Pins for LEDs
    InitializePin(GPIOC, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // White LED
    InitializePin(GPIOC, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //Blue LED
    InitializePin(GPIOC, GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //Yellow LED
    InitializePin(GPIOB, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);// Red LED
    InitializePin(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //Green LED

    //RGB LED
    InitializePin(GPIOB, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins (RED, GREEN, BLUE)

    //Buttons
    InitializePin(GPIOA, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //Button on 35 rail
    InitializePin(GPIOC, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //Button on the 30 rail
    InitializePin(GPIOB, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //Button on the 25 rail


    //Pins for LEDs on the Segment Display
    InitializePin(GPIOA, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // PA13 (1)
    InitializePin(GPIOA, GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PA14 (2)
    //InitializePin(GPIOA, GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PA15 (3) <-- DP point but not needed
    InitializePin(GPIOB, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // PB7 (4)
    InitializePin(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PC13 (5)
    InitializePin(GPIOA, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PA12 (11)
    InitializePin(GPIOC, GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // PC2 (10)
    InitializePin(GPIOC, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PC3 (7)

    //Pins for the Digits on the Segment Display
    InitializePin(GPIOC, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PB8 (6/D2)
    InitializePin(GPIOB, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // PB9 (12/D1)
    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PA5 (9/D3)
    InitializePin(GPIOC, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PC9 (6/D4)

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);


    //Creates Macros for the pins connected to D1-D4 on the Segment Display
    #define D1_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)
    #define D1_LOW() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)
    #define D2_HIGH() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET)
    #define D2_LOW() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET)
    #define D3_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
    #define D3_LOW() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
    #define D4_HIGH() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET)
    #define D4_LOW() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET)

    //initialize temp variables for timer (one for each digit)
    int8_t temp4 = 9;
    int8_t temp3 = 5;
    int8_t temp2 = 3;
    int8_t temp1 = 3;
    //game loop (game only runs while the timer is running until it runs out or all of the puzzles are completed)
    bool timeOn = true;
    
    //initialize variables
    int RGB = 0;
    int LED = 0;
    bool in = false;
    int oldRGB = 6;
    int8_t seedIncrement = 1;
    //call the RGBRan function to randomly set a colour for the player to solve. the seed is based on the current time (to help with randomization)
    RGB = RGBRan(temp4+temp3+temp2+temp1);
    oldRGB = RGB;
    //yellow, blue, and white LEDs turn on (indicates how many puzzles are left)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, true);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, true);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, true);

    while (timeOn){
        //check which buttons are held (from left to right facing the timer, red, green, and blue)
        /* red = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
        blue = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
        green = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7); */
        //4-bit 7 segment display timer update (from the first digit is the left most digit)
        SevenSegment_Update(temp4);
        D4_HIGH();
        HAL_Delay(5);
        D4_LOW();
        SevenSegment_Update(temp3);
        D3_HIGH();
        HAL_Delay(5);
        D3_LOW();       
        SevenSegment_Update(temp2);
        D2_HIGH();
        HAL_Delay(5);
        D2_LOW();
        SevenSegment_Update(temp1);
        D1_HIGH();
        HAL_Delay(5);
        D1_LOW();
        temp4--;
        //if fourth digit reached 0, reset to 9 and decrease third digit by 1
        if (temp4 < 0){
            temp3--;
            temp4 = 9;
        }
        //if third digit reached 0, reset to 9 and decrease second digit by 1
        if (temp3 < 0){
            temp2--;
            temp3 = 9;
        }
        //if second digit reached 0, reset to 9 and decrease first digit by 1
        if (temp2 < 0){
            temp1--;
            temp2 = 9;
        }
        //check if timer is done
        if (temp1 < 0){
            fail();
            timeOn = false;
            break;
        }
        //check which colour was chosen and compare it to the user input.
        switch(RGB){
            case 0: //purple
                if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)){
                    if (LED == 0){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, false);
                        in = true;
                    } else if (LED == 1){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, false);
                        in = true;
                    } else if (LED ==2) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, false);
                        in = true;
                    }
                }
                break;
            case 1: //teal
                if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)){
                    if (LED == 0){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, false);
                        in = true;
                    } else if (LED == 1){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, false);
                        in = true;
                    } else if (LED ==2) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, false);
                        in = true;
                    }
                }
                break;
            case 2: //lime
                if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)){
                    if (LED == 0){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, false);
                        in = true;
                    } else if (LED == 1){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, false);
                        in = true;
                    } else if (LED ==2) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, false);
                        in = true;
                    } 
                }
                break;
            case 3: //white
                if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)&HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)){
                    if (LED == 0){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, false);
                        in = true;
                    } else if (LED == 1){
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, false);
                        in = true;
                    } else if (LED ==2) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, false);
                        in = true;
                    }
                }
                break;
        }        

        //if a puzzle was solved, get a new puzzle
        if (in){
            RGB = RGBRan(temp4+temp3+temp2+temp1+seedIncrement);
            while(oldRGB == RGB){
                RGB = RGBRan(temp4+temp3+temp2+temp1+seedIncrement);
                seedIncrement ++;
            }
            oldRGB = RGB;
            LED++;
            in = false;
        }
        //If there are no more LEDs on (to show remaining amount of puzzles to solve), then end game.
        if (LED >= 3){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, true);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, false);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
            break;
        } 
    }
    return 0;
}

void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}