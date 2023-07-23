/**
 * \file header.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to design the board header
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "header.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" void m5_esp32_screen_header() {
    SCREEN.fillRect(0, 0, 320, 20, TFT_BLACK);

    SCREEN.setCursor(22, 5);
    SCREEN.setTextSize(1.9);
    SCREEN.setTextColor(TFT_WHITE, TFT_BLACK);
    SCREEN.drawPngFile(SD, "/cal.png", 5, 0);
    SCREEN.println("25/05/2023");

    /*SCREEN.setCursor(110, 5);
    SCREEN.setTextSize(1.9);
    SCREEN.setTextColor(TFT_WHITE, TFT_BLACK);
    SCREEN.drawPngFile(SD, "/clk.png", 93, 0);
    SCREEN.println("12:00pm");*/

    SCREEN.drawPngFile(SD, "/woff.png", 300, 0);
    SCREEN.drawPngFile(SD, "/loff.png", 280, 0);
}

extern "C" void m5_esp32_screen_pre_header() {
    SCREEN.fillScreen(0xffffff);

    SCREEN.fillRect(0, 135, 320, 20, TFT_RED); // rec air quality
    SCREEN.fillRect(60, 185, 65, 20, TFT_GREEN); // rec temp
    SCREEN.fillRect(205, 166, 65, 20, TFT_YELLOW); // rec hum
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/