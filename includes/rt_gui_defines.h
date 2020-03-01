//
// Created by Dyan Great on 15/02/2020.
//

#ifndef RT_GUI_DEFINES_H
# define RT_GUI_DEFINES_H



/*
** Sdl gui
*/

#define RT_WIN_ID 1
#define GUI_WIN_ID 2

# define RT_GUI_NAME "Dota 5 Tools"

# ifdef __APPLE__
#  define WIN_GUI_WIDTH 600
# else
#  define WIN_GUI_WIDTH 300
# endif

#define GRAY_GUI 0x3F3F3F

# define GUI_BG GRAY_GUI
# define BTN_BORDER 5

# define CHANGE_ALGO (1 << 0)

# define ACTIVATE 1

# define ARIZONIA_REGULAR_FONT              "Fonts/Arizonia-Regular.ttf"
# define BEYOND_FONT                        "Fonts/Beyond.ttf"
# define BLADRMF_FONT                       "Fonts/BLADRMF_.TTF"
# define COALITION_V2_FONT                  "Fonts/Coalition_v2..ttf"
# define CYBERPUNK_FONT                     "Fonts/Cyberpunk.ttf"
# define DEMONIZED_FONT                     "Fonts/Demonized.ttf"
# define EALOGOREGULAR_PDGR_FONT            "Fonts/EaLogoRegular-PdGr.ttf"
# define HELVETICA_FONT                     "Fonts/Helvetica.ttf"
# define MAGMAWAVE_CAPS_FONT                "Fonts/MagmaWave Caps.otf"
# define NEED_FOR_FONT_FONT                 "Fonts/Need for Font.ttf"
# define NFS_BY_JLTV_FONT                   "Fonts/NFS_by_JLTV.ttf"
# define OASIS_FONT                         "Fonts/OASIS___.TTF"
# define ROBOTO_BLACK_FONT                  "Fonts/Roboto-Black.ttf"
# define ROBOTO_BLACKITALIC_FONT            "Fonts/Roboto-BlackItalic.ttf"
# define ROBOTO_BOLD_FONT                   "Fonts/Roboto-Bold.ttf"
# define ROBOTO_BOLDITALIC_FONT             "Fonts/Roboto-BoldItalic.ttf"
# define ROBOTO_ITALIC_FONT                 "Fonts/Roboto-Italic.ttf"
# define ROBOTO_LIGHT_FONT                  "Fonts/Roboto-Light.ttf"
# define ROBOTO_LIGHTITALIC_FONT            "Fonts/Roboto-LightItalic.ttf"
# define ROBOTO_MEDIUM_FONT                 "Fonts/Roboto-Medium.ttf"
# define ROBOTO_MEDIUMITALIC_FONT           "Fonts/Roboto-MediumItalic.ttf"
# define ROBOTO_REGULAR_FONT                "Fonts/Roboto-Regular.ttf"
# define ROBOTO_THIN_FONT                   "Fonts/Roboto-Thin.ttf"
# define ROBOTO_THINITALIC_FONT             "Fonts/Roboto-ThinItalic.ttf"
# define ROBOTOCONDENSED_BOLD_FONT          "Fonts/RobotoCondensed-Bold.ttf"
# define ROBOTOCONDENSED_BOLDITALIC_FONT    "Fonts/RobotoCondensed-BoldItalic.ttf"
# define ROBOTOCONDENSED_ITALIC_FONT        "Fonts/RobotoCondensed-Italic.ttf"
# define ROBOTOCONDENSED_LIGHT_FONT         "Fonts/RobotoCondensed-Light.ttf"
# define ROBOTOCONDENSED_LIGHTITALIC_FONT   "Fonts/RobotoCondensed-LightItalic.ttf"
# define ROBOTOCONDENSED_REGULAR_FONT       "Fonts/RobotoCondensed-Regular.ttf"
# define STREET_GATHERING_FONT              "Fonts/Street Gathering.ttf"
# define TECHNO_FONT                        "Fonts/Techno.ttf"
# define TESLA_FONT                         "Fonts/TESLA.ttf"
# define THEWITCHER_FONT                    "Fonts/Thewitcher.ttf"
# define TRUE_LIES_FONT                     "Fonts/True Lies.ttf"



# define FONT_PATH THEWITCHER_FONT

# define FONT_SIZE 30
# define FONT_COL 0x0

//# define PATH_TRACE_LABEL "[PATH TRACE]"
# define PATH_TRACE_LABEL "[Path Trace]"
//# define RAY_TRACE_LABEL "[RAY TRACE]"
# define RAY_TRACE_LABEL "[Ray Trace]"
# define RAY_MARCH_LABEL "[RAY MARCH]"

# define SCREENSHOT_LABEL "{Take Screenshot}"

# define NONE       (0 << 0)
# define RENDER_BTN (1 << 0)
# define SCREENSHOT (1 << 1)

# define LIGHT_GREEN_BTN 0xA0CA92
# define GREEN_BTN 0xD8F793
# define DARK_GREEN_BTN 0xDDFC74

# define BTN_COLOR_NONACTIVE LIGHT_GREEN_BTN
# define BTN_COLOR_HOVER GREEN_BTN
# define BTN_COLOR_CLICK DARK_GREEN_BTN

#endif //RT_GUI_DEFINES_H
