/**
 * \file body.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to design the board body
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "body.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" void m5_esp32_screen_body_cfTask() {
    SCREEN.drawPngFile(SD, "/dust.png", 16, 41);
    SCREEN.drawPngFile(SD, "/temp.png", 2, 165);
    SCREEN.drawPngFile(SD, "/clligth.png", 128, 41);
    SCREEN.drawPngFile(SD, "/co2cloud.png", 240, 41);
    SCREEN.drawPngFile(SD, "/hum.png", 250, 165);

    write_text_to_screen_font9((String)"...", TFT_BLUE, TFT_WHITE, 60, 200);
    write_text_to_screen_font9((String)"...", TFT_BLUE, TFT_WHITE, 205, 180);

    write_text_to_screen_font9("PM1.0", TFT_DARKCYAN, TFT_WHITE, 25, 120);
    write_text_to_screen_font9((String)"...", TFT_BLUE, TFT_WHITE, 25, 149);
    //write_text_to_screen_font9("(", TFT_BLUE, TFT_WHITE, 47, 149);
    //write_text_to_screen_font9(")", TFT_BLUE, TFT_WHITE, 69, 149);

    write_text_to_screen_font9("PM2.5", TFT_DARKCYAN, TFT_WHITE, 140, 120);
    write_text_to_screen_font9((String)"...", TFT_BLUE, TFT_WHITE, 140, 149);
    //write_text_to_screen_font9("(", TFT_RED, TFT_WHITE, 162, 149);
    //write_text_to_screen_font9(")", TFT_RED, TFT_WHITE, 184, 149);

    write_text_to_screen_font9("PM10", TFT_DARKCYAN, TFT_WHITE, 251, 120);
    write_text_to_screen_font9((String)"...", TFT_BLUE, TFT_WHITE, 251, 149);
    //write_text_to_screen_font9("(", TFT_DARKGREEN, TFT_WHITE, 271, 149);
    //write_text_to_screen_font9(")", TFT_DARKGREEN, TFT_WHITE, 294, 149);
}


extern "C" void m5_esp32_screen_body_lpTask(String p_1, String p_25, String p_10, String temp, String hum) {
    SCREEN.fillRect(0, 135, 320, 20, TFT_RED); // rec air quality
        SCREEN.fillRect(60, 185, 65, 20, TFT_GREEN); // rec temp
        SCREEN.fillRect(205, 166, 65, 20, TFT_YELLOW); // rec hum

        write_text_to_screen_font9(p_1, TFT_BLUE, TFT_WHITE, 25, 149);
        //SCREEN.drawPngFile(SD, "/info.png", 57, 137);

        write_text_to_screen_font9(p_25, TFT_BLUE, TFT_WHITE, 140, 149);
        //SCREEN.drawPngFile(SD, "/frown.png", 172, 137);

        write_text_to_screen_font9(p_10, TFT_BLUE, TFT_WHITE, 251, 149);
        //SCREEN.drawPngFile(SD, "/smile.png", 281, 137);

        //write_text_to_screen_font9((String)sprintf(env_data[0], "%2.2fC", atof(env_data[0])), TFT_BLUE, TFT_WHITE, 60, 200);
        write_text_to_screen_font9(temp, TFT_BLUE, TFT_WHITE, 60, 200);
        write_text_to_screen_font9(hum, TFT_BLUE, TFT_WHITE, 205, 180);
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/