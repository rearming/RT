
#ifndef RT_GUI_DEFINES_H
# define RT_GUI_DEFINES_H

# define RT_GUI_NAME "Dota 5 Tools"

# ifdef __APPLE__
#  define WIN_GUI_WIDTH 600
#  define GUI_FOOTER 150
#  define GUI_TITLE 70
#  define BTN_DEFAULT_SIZE 50
#  define PANEL_HEIGHT 940
#  define PANEL_WIDTH 600
#  define PANEL_Y 200
# else
#  define WIN_GUI_WIDTH 300
#  define GUI_FOOTER 75
#  define GUI_TITLE 35
#  define BTN_DEFAULT_SIZE 25
#  define PANEL_HEIGHT 470
#  define PANEL_WIDTH 300
#  define PANEL_Y 100
# endif

# define DARK_GRAY 0x3F3F3F
# define BLACK 0X0
# define WHITE 0xFFFFFF
# define LIGHT_GREEN 0xA0CA92
# define GREEN 0xD8F793
# define DARK_GREEN 0xDDFC74

/*
** Sdl gui
*/

# define RT_WIN_ID 1
# define GUI_WIN_ID 2

# define BMP 1
# define JPG 2
# define PNG 3
# define SCREENSHOT_FORMAT PNG

# define ACTIVATE 1

# define ARIZONIA_REGULAR_FONT              "assets/Fonts/Arizonia-Regular.ttf"
# define CYBERPUNK_FONT                     "assets/Fonts/Cyberpunk.ttf"
# define DEMONIZED_FONT                     "assets/Fonts/Demonized.ttf"
# define HELVETICA_FONT                     "assets/Fonts/Helvetica.ttf"
# define MAGMAWAV_CAPS_FONT                "assets/Fonts/MagmaWave Caps.otf"
# define OASIS_FONT                         "assets/Fonts/OASIS___.TTF"
# define ROBOTO_BLACK_FONT                  "assets/Fonts/Roboto-Black.ttf"
# define ROBOTO_BOLD_FONT                   "assets/Fonts/Roboto-Bold.ttf"
# define ROBOTO_BOLDITALIC_FONT             "assets/Fonts/Roboto-BoldItalic.ttf"
# define ROBOTO_ITALIC_FONT                 "assets/Fonts/Roboto-Italic.ttf"
# define ROBOTO_LIGHT_FONT                  "assets/Fonts/Roboto-Light.ttf"
# define ROBOTO_MEDIUM_FONT                 "assets/Fonts/Roboto-Medium.ttf"
# define ROBOTO_REGULAR_FONT                "assets/Fonts/Roboto-Regular.ttf"
# define ROBOTO_THIN_FONT                   "assets/Fonts/Roboto-Thin.ttf"
# define ROBOTO_THINITALIC_FONT             "assets/Fonts/Roboto-ThinItalic.ttf"
# define STREET_GATHERING_FONT              "assets/Fonts/Street Gathering.ttf"
# define TECHNO_FONT                        "assets/Fonts/Techno.ttf"
# define TESLA_FONT                         "assets/Fonts/TESLA.ttf"
# define THEWITCHER_FONT                    "assets/Fonts/Thewitcher.ttf"

# define FONT_PATH THEWITCHER_FONT

# define TITLE_FONT_SIZE 40
# define SUBTITLE_FONT_SIZE 30
# define BODY_FONT_SIZE 25

# define FONT_COL BLACK

# define DEFAULT_BORDER 6

# define RT_GUI_TITLE "RT by Sleonard and team"
# define PATH_TRACE_LABEL "{PATH TRACE}"
# define RAY_TRACE_LABEL "(RAY TRACE)"
# define CAMERA_LABEL "Camera"
# define POSITION_LABEL "Position"
# define PARAMETERS_LABEL "Params"

# define SCREENSHOT_LABEL "XTake ScreenshotX"

# define NONE       (0 << 0)
# define RENDER_BTN (1 << 0)
# define SCREENSHOT (1 << 1)
# define PANEL      (1 << 2)
# define TEXT_BOX	(1 << 10)
# define CAM_TEXT_BOX   (1 << 3) | TEXT_BOX
# define POS_TEXT_BOX   (1 << 4) | TEXT_BOX
# define PARAM_TEXT_BOX   (1 << 5) | TEXT_BOX

# define PANEL_BORDER DEFAULT_BORDER * 3

# define PANEL_BUTTON_WIDTH (PANEL_WIDTH - PANEL_BORDER * 2) / 3
# define TEXT_WIDTH (PANEL_WIDTH - PANEL_BORDER * 2) / 2

# define BTN_COLOR_NONACTIVE LIGHT_GREEN
# define BTN_COLOR_HOVER GREEN
# define BTN_COLOR_CLICK DARK_GREEN

# define GUI_BG DARK_GRAY
# define PANEL_BG BTN_COLOR_CLICK

#endif
