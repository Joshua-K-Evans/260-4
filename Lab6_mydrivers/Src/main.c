
// include the drivers header file
#include "drivers.h"

// input pin macros
#define ARM_BUTTON_PORT    GPIOC
#define ARM_BUTTON_PIN     13
#define DISARM_BUTTON_PORT GPIOA
#define DISARM_BUTTON_PIN  0
#define FRONT_SENSOR_PORT  GPIOA
#define FRONT_SENSOR_PIN   1
#define BACK_SENSOR_PORT   GPIOA
#define BACK_SENSOR_PIN    4
#define WINDOW_SENSOR_PORT GPIOA
#define WINDOW_SENSOR_PIN  6

// output pin macros
#define ARM_STATUS_PORT   GPIOA
#define ARM_STATUS_PIN    5
#define FRONT_ALARM_PORT  GPIOA
#define FRONT_ALARM_PIN   7
#define BACK_ALARM_PORT   GPIOA
#define BACK_ALARM_PIN    8
#define WINDOW_ALARM_PORT GPIOA
#define WINDOW_ALARM_PIN  9

// This program adapts the alarm code from Lab 5 for use in Lab 6 with drivers
int main(void)
{
    // Turn on GPIO clocks (Ports A, B, and C)
    GPIOA_ClkEnable();
    GPIOB_ClkEnable();
    GPIOC_ClkEnable();

    // Configure button pins as inputs
    GPIO_Mode(ARM_BUTTON_PORT,    ARM_BUTTON_PIN,    GPIO_MODE_INPUT);
    GPIO_Mode(DISARM_BUTTON_PORT, DISARM_BUTTON_PIN, GPIO_MODE_INPUT);

    // Configure reed switch pins as inputs
    GPIO_Mode(FRONT_SENSOR_PORT,  FRONT_SENSOR_PIN,  GPIO_MODE_INPUT);
    GPIO_Mode(BACK_SENSOR_PORT,   BACK_SENSOR_PIN,   GPIO_MODE_INPUT);
    GPIO_Mode(WINDOW_SENSOR_PORT, WINDOW_SENSOR_PIN, GPIO_MODE_INPUT);

    // Configure LED pins as outputs
    GPIO_Mode(ARM_STATUS_PORT,   ARM_STATUS_PIN,   GPIO_MODE_OUTPUT);
    GPIO_Mode(FRONT_ALARM_PORT,  FRONT_ALARM_PIN,  GPIO_MODE_OUTPUT);
    GPIO_Mode(BACK_ALARM_PORT,   BACK_ALARM_PIN,   GPIO_MODE_OUTPUT);
    GPIO_Mode(WINDOW_ALARM_PORT, WINDOW_ALARM_PIN, GPIO_MODE_OUTPUT);

    // Enable pull-up resistors for inputs
    GPIO_Pull(DISARM_BUTTON_PORT, DISARM_BUTTON_PIN, GPIO_PULLUP);
    GPIO_Pull(FRONT_SENSOR_PORT,  FRONT_SENSOR_PIN,  GPIO_PULLUP);
    GPIO_Pull(BACK_SENSOR_PORT,   BACK_SENSOR_PIN,   GPIO_PULLUP);
    GPIO_Pull(WINDOW_SENSOR_PORT, WINDOW_SENSOR_PIN, GPIO_PULLUP);

    // Initialize Alarm Status (turn off all LEDs)
    GPIO_WritePin(ARM_STATUS_PORT,   ARM_STATUS_PIN,   0);
    GPIO_WritePin(FRONT_ALARM_PORT,  FRONT_ALARM_PIN,  0);
    GPIO_WritePin(BACK_ALARM_PORT,   BACK_ALARM_PIN,   0);
    GPIO_WritePin(WINDOW_ALARM_PORT, WINDOW_ALARM_PIN, 0);

    // armed state (initialize to disarm)
    int armed = 0;

    // infinite loop
    while(1){

        // check if ArmButton is pressed
        if (GPIO_ReadPin(ARM_BUTTON_PORT, ARM_BUTTON_PIN) == 0){

            // arm system
            armed = 1; // set arm state
            GPIO_WritePin(ARM_STATUS_PORT, ARM_STATUS_PIN, 1); // turn on ArmStatus LED
        }

        // check if DisarmButton is pressed
        if (GPIO_ReadPin(DISARM_BUTTON_PORT, DISARM_BUTTON_PIN) == 0){

            // disarm system
            armed = 0; // reset arm state
            GPIO_WritePin(ARM_STATUS_PORT,   ARM_STATUS_PIN,   0); // turn off ArmStatus LED
            GPIO_WritePin(FRONT_ALARM_PORT,  FRONT_ALARM_PIN,  0); // turn off FrontAlarm LED
            GPIO_WritePin(BACK_ALARM_PORT,   BACK_ALARM_PIN,   0); // turn off BackAlarm LED
            GPIO_WritePin(WINDOW_ALARM_PORT, WINDOW_ALARM_PIN, 0); // turn off WindowAlarm LED
        }

        // if system is armed, check sensors
        if (armed){

            // check the FrontSensor
            if (GPIO_ReadPin(FRONT_SENSOR_PORT, FRONT_SENSOR_PIN) != 0){

                // system armed & front door is open:
                GPIO_WritePin(FRONT_ALARM_PORT, FRONT_ALARM_PIN, 1); // turn on FrontAlarm LED
            }

            // check the BackSensor
            if (GPIO_ReadPin(BACK_SENSOR_PORT, BACK_SENSOR_PIN) != 0){

                // system armed & back door is open:
                GPIO_WritePin(BACK_ALARM_PORT, BACK_ALARM_PIN, 1); // turn off BackAlarm LED
            }

            // check the WindowSensor
            if (GPIO_ReadPin(WINDOW_SENSOR_PORT, WINDOW_SENSOR_PIN) != 0){

                // system armed & window is open:
                GPIO_WritePin(WINDOW_ALARM_PORT, WINDOW_ALARM_PIN, 1); // turn on WindowAlarm LED
            }
        }
    }
}



