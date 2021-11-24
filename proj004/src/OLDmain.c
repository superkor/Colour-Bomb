//Colour Bomb by Mike Kim and Justin Chow

//#define BUTTON_BLINK
//#define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD_CONTROL
//#define SEVEN_SEGMENT
#define COLOR_LED

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

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

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    //Pins for LEDs
    InitializePin(GPIOC, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // PC10
    InitializePin(GPIOC, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PC12
    InitializePin(GPIOC, GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); //PC11

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




    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

#ifdef BUTTON_BLINK
    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)
    /* while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
    {
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
    } */

    /* while (1) // loop forever, blinking the LED
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        HAL_Delay(500);  // 500 milliseconds == 1/2 second
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
        HAL_Delay(500);  // 500 milliseconds == 1/2 second
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);
        HAL_Delay(500);  // 500 milliseconds == 1/2 seconds
    }
 */
        
#endif

#ifdef LIGHT_SCHEDULER
    // Turn on the LED five seconds after reset, and turn it off again five seconds later.

    while (true) {
        uint32_t now = HAL_GetTick();
        if (now > 1000 && now < 2000)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);  // turn off LED
    }
#endif

#ifdef TIME_RAND
    // This illustrates the use of HAL_GetTick() to get the current time,
    // plus the use of random() for random number generation.
    
    // Note that you must have "#include <stdlib.h>"" at the top of your main.c
    // in order to use the srand() and random() functions.

    // while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press
    // srand(HAL_GetTick());  // set the random seed to be the time in ms that it took to press the button
    // if the line above is commented out, your program will get the same sequence of random numbers
    // every time you run it (which may be useful in some cases)

    while (true) // loop forever
    {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press

        // Display the time in milliseconds along with a random number.
        // We use the sprintf() function to put the formatted output into a buffer;
        // see https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm for more
        // information about this function
        char buff[100];
        sprintf(buff, "Time: %lu ms   Random = %ld\r\n", HAL_GetTick(), random());
        // lu == "long unsigned", ld = "long decimal", where "long" is 32 bit and "decimal" implies signed
        SerialPuts(buff); // transmit the buffer to the host computer's serial monitor in VSCode/PlatformIO

        while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button to be released
    }
#endif

#ifdef SEVEN_SEGMENT
    //Creates Macros for the pins connected to D1-D4 on the Segment Display
    #define D1_HIGH() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)
    #define D1_LOW() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)
    #define D2_HIGH() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET)
    #define D2_LOW() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET)
    #define D3_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
    #define D3_LOW() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
    #define D4_HIGH() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET)
    #define D4_LOW() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET)
    //Seven Segement Number Array
    int8_t temp4 = 9;
    int8_t temp3 = 9;
    int8_t temp2 = 9;
    int8_t temp1 = 9;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);

    // Display the numbers 0 to 9 inclusive on the 7-segment display, pausing for a second between each one.
    // (remember that the GND connection on the display must go through a 220 ohm current-limiting resistor!)
    while (1){
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
        if (temp4 < 0){
            temp3--;
            temp4 = 9;
            //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        }
        if (temp3 < 0){
            temp2--;
            temp3 = 9;
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
        }
        if (temp2 < 0){
            temp1--;
            temp2 = 9;
        }
        if (temp1 < 0){
            temp1 = 9;
            temp2 = 9;
            temp3 = 9;
            temp4 = 9;
        }
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);

        /* HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        HAL_Delay(500);  // 500 milliseconds == 1/2 second
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
        HAL_Delay(500);  // 500 milliseconds == 1/2 second
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);
        HAL_Delay(500);  // 500 milliseconds == 1/2 seconds */
        
    }
#endif

#ifdef COLOR_LED
    // Cycle through all 8 possible colors (including off and white) as the on-board button is pressed.
    // This example assumes that the color LED is connected to pins D11, D12 and D13.

    // Remember that each of those three pins must go through a 220 ohm current-limiting resistor!
    // Also remember that the longest pin on the LED should be hooked up to GND.

    InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins

    /* //purple
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true); */

    /* //teal
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true); */

    /* //lime
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true); */

    //white
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);




    /* while (true) {
        for (int color = 0; color < 8; ++color) {
            // bottom three bits indicate which of the three LEDs should be on (eight possible combinations)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, color & 0x01);  // blue  (hex 1 == 0001 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, color & 0x02);  // green (hex 2 == 0010 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, color & 0x04);  // red   (hex 4 == 0100 binary)
            HAL_Delay(100);

            //while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));   // wait for button press 
            //while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button release
        }
    } */
#endif
    return 0;
}
// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}