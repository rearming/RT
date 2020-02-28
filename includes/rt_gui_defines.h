//
// Created by Dyan Great on 15/02/2020.
//

#ifndef RT_GUI_DEFINES_H
# define RT_GUI_DEFINES_H



/*
** Sdl gui
*/
# define RT_GUI_NAME "Dota 5 Tools"

# ifdef __APPLE__
#  define WIN_GUI_WIDTH 640
# else
#  define WIN_GUI_WIDTH 320
# endif

#define GUI_BG 0x3F3F3F
#define BTN_BORDER 5

#define CHANGE_ALGO (1 << 0)

# define ACTIVATE 1

# define FONT_SIZE 30
# define FONT_COL 0x0

#define NONE (0 << 0)
#define RENDER_BTN (1 << 0)
#define SCREENSHOT (1 << 1)

#define BTN_COLOR_NONACTIVE 0xA0CA92
#define BTN_COLOR_HOVER 0xD8F793
#define BTN_COLOR_CLICK 0xDDFC74

#endif //RT_GUI_DEFINES_H
