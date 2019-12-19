/*
* Licensee agrees that the example code provided to Licensee has been developed and released by Bosch solely as an example to be used as a potential reference for application development by Licensee.
* Fitness and suitability of the example code for any use within application developed by Licensee need to be verified by Licensee on its own authority by taking appropriate state of the art actions and measures (e.g. by means of quality assurance measures).
* Licensee shall be responsible for conducting the development of its applications as well as integration of parts of the example code into such applications, taking into account the state of the art of technology and any statutory regulations and provisions applicable for such applications. Compliance with the functional system requirements and testing there of (including validation of information/data security aspects and functional safety) and release shall be solely incumbent upon Licensee.
* For the avoidance of doubt, Licensee shall be responsible and fully liable for the applications and any distribution of such applications into the market.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are * met:
*
*     (1) Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer. *
* (2) Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in
* the documentation and/or other materials provided with the
* distribution. *
* (3)The name of the author may not be used to
* endorse or promote products derived from this software without
* specific prior written permission. *
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/ /*----------------------------------------------------------------------------*/ /**
 * @ingroup APPS_LIST
 *
 * @defgroup XDK_APPLICATION_TEMPLATE LED_Buttons_Effect
 * @{
 *
 * @brief XDK Application Template
 *

* @details XDK Application Template without any functionality.
* Could be used as a starting point to develop new application based on XDK platform.
*
* @file **/
/* module includes ********************************************************** */
/* own header files */
#include "XdkAppInfo.h"
#undef BCDS_MODULE_ID /* Module ID define before including Basics package*/ #define BCDS_MODULE_ID XDK_APP_MODULE_ID_APP_CONTROLLER
#include "XdkSensorHandle.h"
/* own header files */
#include "AppController.h"
/* system header files */
#include <stdio.h> #include <inttypes.h> #include <stdint.h>
/* additional interface header files */
#include "BCDS_CmdProcessor.h" #include "XDK_Utils.h" #include "FreeRTOS.h" #include "task.h"
#include "XDK_sensor.h" #include "XDK_LED.h" #include "XDK_Button.h" #include "math.h"
/* constant definitions ***************************************************** */
#define XDK_APP_DELAY UINT32_C(500)
/* local variables ********************************************************** */
static CmdProcessor_T * AppCmdProcessor;/**< Handle to store the main Command processor handle to be used by run-time event driven threads */
static xTaskHandle AppControllerHandle = NULL;/**< OS thread handle for Application controller to be used by run-time blocking threads */
static void bouton1(ButtonEvent_T); static void bouton2(ButtonEvent_T); static void Lum1 (ButtonEvent_T); static void Lum2 (ButtonEvent_T); static void game (ButtonEvent_T); static void luminosity (ButtonEvent_T);
/* global variables ********************************************************* */
typedef struct twoButtons { ButtonEvent_T first_button; ButtonEvent_T second_button;
}Two;

Two retour_Begin;
static Button_Setup_T boutonSetup = { // Structure for the game mode
works
works or not
works or not
pressed
pressed
};
.CmdProcessorHandle = NULL, // pointer that needs AppCmdprocessor to .InternalButton1isEnabled = true, // boolean which tells if the button 1 .InternalButton2isEnabled = true, // boolean which tells if the button 2 .InternalButton1Callback = bouton1, // function to call when button 1 is .InternalButton2Callback = bouton2, // function to call when button 2 is
static Button_Setup_T LumSetup = { // Structure for the light measurement mode .CmdProcessorHandle = NULL,
.InternalButton1isEnabled = true, .InternalButton2isEnabled = true, .InternalButton1Callback = Lum1, .InternalButton2Callback = Lum2,
};
static Button_Setup_T firstSetup = { // Structure for the main mode, when we choose between both modes
.CmdProcessorHandle = NULL, .InternalButton1isEnabled = true, .InternalButton2isEnabled = true, .InternalButton1Callback = game, .InternalButton2Callback = luminosity,
};
int stop = 1;
uint32_t lightValuemilli; uint32_t lightTrueValue; uint8_t statusRed = 0; uint8_t statusOrange = 0; uint8_t statusYellow = 0;
/* inline functions ********************************************************* */ /* local functions ********************************************************** */
void initLightSensor(void) {
LightSensor_init(xdkLightSensor_MAX44009_Handle); // Setup of light sensor /* ******************** Luminosity begin
*************************************************************** */
static void luminosity(ButtonEvent_T b1) { if(b1 == BUTTON_EVENT_PRESSED) {
}

stop = 0;
printf("Pret pour les calculs \r\n");
printf("If you want to return, press both buttons at the same time
LumSetup
} }
static void Lum1 (ButtonEvent_T b1) { // not a useful function because doing nothing switch(b1) {
case BUTTON_EVENT_PRESSED: retour_Begin.first_button = b1;
break;
case BUTTON_EVENT_RELEASED:
retour_Begin.first_button = b1; break;
default:
printf("Trying to block something ??? \r\n");
break;
} }
static void Lum2 (ButtonEvent_T b1) { // not a useful function because doing nothing switch(b1) {
case BUTTON_EVENT_PRESSED: retour_Begin.second_button = b1;
break;
case BUTTON_EVENT_RELEASED:
retour_Begin.second_button = b1; break;
default:
printf("Trying to block something ??? \r\n");
break;
} }
void modifie_LED(uint32_t val) { // modify the numbers of LEDs that are lighted in function of the luminosity
if (val == 0) {
printf("None Luminosity \r\n"); LED_Off(LED_INBUILT_YELLOW); LED_Off(LED_INBUILT_ORANGE); LED_Off(LED_INBUILT_RED);
\r\n");
AppCmdProcessor into CmdProcessorHandle parameter in the structure LumSetup
}
if ((0
< val) && (val <= 100)) { printf("Low Luminosity \r\n"); LED_On(LED_INBUILT_YELLOW); LED_Off(LED_INBUILT_ORANGE); LED_Off(LED_INBUILT_RED);
LumSetup.CmdProcessorHandle = AppCmdProcessor; // Send the value Button_Setup(&LumSetup); // Setupping the buttons with the structure
}
if ((100 < val) && (val <= 200)) {

printf("Medium Luminosity \r\n"); LED_On(LED_INBUILT_YELLOW); LED_On(LED_INBUILT_ORANGE); LED_Off(LED_INBUILT_RED);
}
if (200 < val) {
printf("HIGH Luminosity \r\n"); LED_On(LED_INBUILT_YELLOW); LED_On(LED_INBUILT_ORANGE); LED_On(LED_INBUILT_RED);
}
if (val < 0) {
printf("PROBLEME AU NIVEAU DE LA VALEUR DE SORTIE \r \n");
} }
/* ******************** Luminosity end *************************************************************** */
/* ******************** Game Begin ******************************************************************* */
static void game(ButtonEvent_T b1) { // function that setup the buttons into the game mode
if(b1 == BUTTON_EVENT_PRESSED) {
printf("C'est parti pour le jeu !!! \r\n");
printf("If you want to return, press both buttons at the same time
\r\n"); }
}
boutonSetup.CmdProcessorHandle = AppCmdProcessor; Button_Setup(&boutonSetup);
void status_LED(uint8_t* red, uint8_t* orange, uint8_t* yellow) { // function that get the status of LEDs, if they are lighted or not (game mode)
LED_Status(LED_INBUILT_RED, red); LED_Status(LED_INBUILT_ORANGE, orange); LED_Status(LED_INBUILT_YELLOW, yellow);
}
void allume_LED(uint8_t re, uint8_t or, uint8_t ye) { // function in game mode that
permits to go up in binary 000 -> 111
if (re == 1 && or == 1 && ye == 1) { printf("Maximum Luminosity \r\n");
}
if (re == 1 && or == 1 && ye == 0) {
LED_On(LED_INBUILT_YELLOW); printf("Go to the maximum ! \r\n");
}
if (re == 1 && or == 0 && ye == 1) {
LED_On(LED_INBUILT_ORANGE);

}
if (re
}
if (re
}
if (re
}
if (re
}
if (re
LED_Off(LED_INBUILT_YELLOW);
printf("Go to the very high luminosity \r\n");
== 1 && or == 0 && ye == 0) { LED_On(LED_INBUILT_YELLOW);
printf("Go to the High luminosity \r\n");
== 0 && or == 1 && ye == 1) { LED_On(LED_INBUILT_RED); LED_Off(LED_INBUILT_ORANGE); LED_Off(LED_INBUILT_YELLOW);
printf("Go to the Medium high luminosity \r\n");
== 0 && or == 1 && ye == 0) { LED_On(LED_INBUILT_YELLOW);
printf("Go to the Medium luminosity \r\n");
== 0 && or == 0 && ye == 1) { LED_Off(LED_INBUILT_YELLOW); LED_On(LED_INBUILT_ORANGE);
printf("Go to the Low Luminosity \r\n");
== 0 && or == 0 && ye == 0) { LED_On(LED_INBUILT_YELLOW);
printf("Go to the lowest luminosity \r\n");
}
if ((re != 0 && re != 1) || (or != 0 && or != 1) || (ye != 0 && ye != 1)) {
printf("Error Critical LED \r\n");
} }
void eteint_LED(uint8_t re, uint8_t or, uint8_t ye) { //function that permit to go down in binary 111 -> 000
if (re }
if (re
if (re }
if (re
}
if (re
== 1 && or == 1 && ye == 1) { LED_Off(LED_INBUILT_YELLOW);
printf("Go to Very high luminosity \r\n");
== 1 && or == 1 && ye == 0) { LED_On(LED_INBUILT_YELLOW); LED_Off(LED_INBUILT_ORANGE); printf("Go to high luminosity \r\n");
}
== 1 && or == 0 && ye == 1) {
LED_Off(LED_INBUILT_YELLOW);
printf("Go to Medium high luminosity \r\n");
== 1 && or == 0 && ye == 0) { LED_On(LED_INBUILT_YELLOW); LED_On(LED_INBUILT_ORANGE); LED_Off(LED_INBUILT_RED);
printf("Go to Medium luminosity \r\n");
== 0 && or == 1 && ye == 1) {

}
if (re
}
if (re
}
if (re
LED_Off(LED_INBUILT_YELLOW); printf("Go to Low luminosity \r\n");
== 0 && or == 1 && ye == 0) { LED_On(LED_INBUILT_YELLOW); LED_Off(LED_INBUILT_ORANGE); printf("Go to Lowest luminosity \r\n");
== 0 && or == 0 && ye == 1) { LED_Off(LED_INBUILT_YELLOW); printf("Go to the none ! \r\n");
== 0 && or == 0 && ye == 0) {
printf("You cannot go lower than this \r\n");
}
if ((re != 0 && re != 1) || (or != 0 && or != 1) || (ye != 0 && ye != 1)) {
printf("Error Critical LED \r\n");
} }
static void bouton1(ButtonEvent_T b1) { // function which permits go down in binary (game mode)
switch(b1) { case(BUTTON_EVENT_PRESSED):
retour_Begin.first_button = b1; status_LED(&statusRed, &statusOrange, &statusYellow); eteint_LED(statusRed, statusOrange, statusYellow);
break; case(BUTTON_EVENT_RELEASED):
retour_Begin.first_button = b1; break;
default:
printf("Problem on button 1 \r\n");
break; }
}
static void bouton2(ButtonEvent_T b2) { // function which permits go up in binary
(game mode)
switch(b2) { case(BUTTON_EVENT_PRESSED):
retour_Begin.second_button = b2; status_LED(&statusRed, &statusOrange, &statusYellow); allume_LED(statusRed, statusOrange, statusYellow);
break; case(BUTTON_EVENT_RELEASED):
retour_Begin.second_button = b2; break;
default:
printf("Problem on button 2 \r\n");
break;

} }
/* ******************** Game End ******************************************************************* */
static void turnOff_LEDs(void) { // function that turn off all the LEDs (except the green one)
LED_Off(LED_INBUILT_YELLOW); LED_Off(LED_INBUILT_ORANGE); LED_Off(LED_INBUILT_RED);
}
/* Reset Setup ****************************************************************************** */
static void reset(void) { // function used to return to the choose mode (main mode) when we press both buttons
vTaskDelay(XDK_APP_DELAY); // Need a delay that the printf can work
printf("Welcome Back ! \nPress button 1 to play \nPress button 2 to levelate the luminosity \r \n");
       turnOff_LEDs();
stop = 1;
retour_Begin.first_button = BUTTON_EVENT_RELEASED; retour_Begin.first_button = BUTTON_EVENT_RELEASED;
firstSetup.CmdProcessorHandle = AppCmdProcessor; Button_Setup(&firstSetup);
}
/* End Button Setup ******************************************************************************** */
/**
* @brief Responsible for controlling application control flow.
* Any application logic which is blocking in nature or fixed time dependent
* can be placed here.
*
* @param[in] pvParameters
* FreeRTOS task handle. Could be used if more than one thread is using this function
block. */
static void AppControllerFire(void* pvParameters) {
    BCDS_UNUSED(pvParameters);
while (1) {
        vTaskDelay(XDK_APP_DELAY);
if(retour_Begin.second_button == BUTTON_EVENT_PRESSED && retour_Begin.first_button == BUTTON_EVENT_PRESSED)
{

             reset(); // Reset to return into the choice of mode
        }
if(stop == 0) { // Condition to prevent the light sensor to work before entering in the light measurement mode
LightSensor_readLuxData(xdkLightSensor_MAX44009_Handle,&lightValuemilli); // Readed value in milliLux
to Lux
measurement
lightTrueValue = lightValuemilli / 1000; // Conversion milliLux
modifie_LED(lightTrueValue); // modify LEDs in function of light
(unsigned }
} }
printf("The value of the light sensor is : %d Lux \r\n",
int) lightTrueValue); // We print the result on the workbench's console.
/**
 * @brief To enable the necessary modules for the application
 *
 * @param [in] param1
 * A generic pointer to any context data structure which will be passed to the
function when it is invoked by the command processor. *
 * @param [in] param2
* A generic 32 bit value which will be passed to the function when it is invoked by the command processor..
*/
static void AppControllerEnable(void * param1, uint32_t param2) {
BCDS_UNUSED(param1); BCDS_UNUSED(param2);
Retcode_T retcode = RETCODE_OK;
/* MY CODE ************************************************************************************* ************************ */
    LED_Enable(); // enabling Leds
    Button_Enable(); // enabling buttons
/* ************************************************************************************* ********************************* */
/* @todo - Enable necessary modules for the application and check their return values */
if (RETCODE_OK == retcode) {

if (pdPASS != xTaskCreate(AppControllerFire, (const char * const ) "AppController", TASK_STACK_SIZE_APP_CONTROLLER, NULL, TASK_PRIO_APP_CONTROLLER, &AppControllerHandle))
{
retcode = RETCODE(RETCODE_SEVERITY_ERROR, RETCODE_OUT_OF_RESOURCES);
} }
if (RETCODE_OK != retcode) {
printf("AppControllerEnable : Failed \r\n"); Retcode_RaiseError(retcode);
assert(0); /* To provide LED indication for the user */
}
    Utils_PrintResetCause();
}
/**
 * @brief To setup the necessary modules for the application
 *
 * @param [in] param1
 * A generic pointer to any context data structure which will be passed to the
function when it is invoked by the command processor. *
 * @param [in] param2
* A generic 32 bit value which will be passed to the function when it is invoked by the command processor..
*/
static void AppControllerSetup(void * param1, uint32_t param2) {
BCDS_UNUSED(param1); BCDS_UNUSED(param2);
Retcode_T retcode = RETCODE_OK;
/* @todo - Setup the necessary modules required for the application */
/* MY CODE ************************************************************************************* ************************ */
    LED_Setup(); // Setup Leds
    initLightSensor(); // Setup light sensor
    reset(); // setup at the beginning of the execution the choice mode
/* ************************************************************************************* ********************************* */
retcode = CmdProcessor_Enqueue(AppCmdProcessor, AppControllerEnable, NULL, UINT32_C(0));
if (RETCODE_OK != retcode) {
printf("AppControllerSetup : Failed \r\n"); Retcode_RaiseError(retcode);

        assert(0); /* To provide LED indication for the user */
    }
}
/* global functions ********************************************************* */
/** Refer interface header for description */
void AppController_Init(void * cmdProcessorHandle, uint32_t param2) {
BCDS_UNUSED(param2);
Retcode_T retcode = RETCODE_OK;
if (cmdProcessorHandle == NULL) {
printf("AppController_Init : Command processor handle is NULL \r\n");
retcode = RETCODE(RETCODE_SEVERITY_ERROR, RETCODE_NULL_POINTER); }
else
{
AppCmdProcessor = (CmdProcessor_T *) cmdProcessorHandle;
retcode = CmdProcessor_Enqueue(AppCmdProcessor, AppControllerSetup, NULL,
UINT32_C(0));
    }
if (RETCODE_OK != retcode) {
        Retcode_RaiseError(retcode);
        assert(0); /* To provide LED indication for the user */
    }
}
/**@} */
/** ************************************************************************* */
