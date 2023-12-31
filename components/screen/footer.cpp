/**
 * \file footer.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to design the board footer
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "footer.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" void m5_esp32_screen_footer() {
    SCREEN.drawPngFile(SD, "/waylay.png", 110, 210);
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/