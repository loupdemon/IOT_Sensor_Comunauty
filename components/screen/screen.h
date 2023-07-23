/**
 * \file screen.h
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief Main header of the Screen component
 * \date 25 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* MACROS                                                                                                   */
/**********************************************************************************************************************/

#ifndef SCREEN_H
#define SCREEN_H

/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include <base.h>

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

/**********************************************************************************************************************/
/* PRIVATE ENUM AND VARIABLE                                                                                          */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PRIVATE METHODS PROTOTYPES                                                                                         */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* PUBLIC METHODS PROTOTYPES                                                                                          */
/**********************************************************************************************************************/

void write_text_to_screen_font9(String text, uint16_t text_color, uint16_t text_bg_color, int16_t x_pos, int16_t y_pos);

#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif


/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/