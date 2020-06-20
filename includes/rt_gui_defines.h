/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_gui_defines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:23:43 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 13:23:43 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GUI_DEFINES_H
# define RT_GUI_DEFINES_H

# define RT_GUI_NAME "Dota 5 Tools"

# ifdef __APPLE__
#  define WIN_GUI_WIDTH 600
#  define GUI_FOOTER 150
#  define GUI_TITLE 70
#  define BTN_DEFAULT_SIZE 50
#  define BTN_BIG_SIZE 100
#  define PANEL_HEIGHT 600
#  define PANEL_WIDTH 600
#  define PANEL_Y 175
# else
#  define WIN_GUI_WIDTH 300
#  define GUI_FOOTER 75
#  define GUI_TITLE 35
#  define BTN_DEFAULT_SIZE 25
#  define BTN_BIG_SIZE 50
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

# define DEFAULT_BORDER 5

# define RT_GUI_TITLE "RT by Sleonard and team"
# define PATH_TRACE_LABEL "{PATH TRACE}"
# define RAY_TRACE_LABEL "(RAY TRACE)"
# define CAMERA_LABEL "Camera"
# define POSITION_LABEL "Position"
# define PARAMETERS_LABEL "Params"

# define MESHES_LABEL "Meshes"
# define OBJECTS_LABEL "Objects"
# define TEXTURE_LABEL "Textures"
# define ANTI_AL_LABEL "Anti Aliasing"
# define SKYBOX_LABEL "Skybox"
# define BLUR_LABEL "DOF"
# define SEPIA_LABEL "Sepia"
# define IMPRESSIVE_LABEL "Impressive"
# define CARTOON_LABEL "Cartoon"
# define BACKFACE_LABEL "Backface Culling"
# define SMOOTH_LABEL "Smooth"
# define SCREENSHOT_LABEL "XTake ScreenshotX"

# define NONE       (0 << 0)
# define RENDER_BTN (1 << 0)
# define SCREENSHOT (1 << 1)
# define PANEL      (1 << 2)
# define TEXT_BOX	(1 << 10)
# define CAM_TEXT_BOX   (1 << 3) | TEXT_BOX
# define POS_TEXT_BOX   (1 << 4) | TEXT_BOX
# define PARAM_TEXT_BOX   (1 << 5) | TEXT_BOX
# define STATE_BTN			(1 << 4)
# define OPTION_BTN			(1 << 6)
# define MESHES_BTN			(1 << 7) | OPTION_BTN
# define OBJECTS_BTN		(1 << 8) | OPTION_BTN
# define TEXTURES_BTN		(1 << 9) | OPTION_BTN
# define ANTI_AL_BTN		(1 << 11) | OPTION_BTN
# define SKYBOX_BTN			(1 << 12) | OPTION_BTN
# define IMP_BTN			(1 << 13) | OPTION_BTN
# define BFC_BTN			(1 << 14) | OPTION_BTN
# define SMOOTH_BTN			(1 << 15) | OPTION_BTN
# define BLUR_BTN			(1 << 14) | STATE_BTN
# define SEPIA_BTN			(1 << 15) | STATE_BTN
# define CARTOON_BTN		(1 << 13) | STATE_BTN

# define PANEL_BORDER DEFAULT_BORDER * 10

# define PANEL_BUTTON_WIDTH (PANEL_WIDTH - PANEL_BORDER * 2) / 3
# define TEXT_WIDTH (PANEL_WIDTH - PANEL_BORDER * 2)
# define OPTIONS_BLOCK PANEL_Y + 60 + 6 * BTN_DEFAULT_SIZE
# define FIRST_COL_X 0
# define SECOND_COL_X WIN_GUI_WIDTH / 2
# define HALF_GUI WIN_GUI_WIDTH / 2
# define MSH_Y OPTIONS_BLOCK
# define OBJ_Y MSH_Y  + BTN_BIG_SIZE
# define TEXTURE_Y OBJ_Y + BTN_BIG_SIZE
# define ANTI_AL_Y TEXTURE_Y + BTN_BIG_SIZE
# define SKYBOX_Y ANTI_AL_Y + BTN_BIG_SIZE
# define BACKFACE_C_Y SKYBOX_Y + BTN_BIG_SIZE
# define IMP_Y MSH_Y
# define DOF_Y OBJ_Y
# define SEPIA_Y TEXTURE_Y
# define TUNES_Y ANTI_AL_Y
# define SMOOTH_Y SKYBOX_Y

# define LIGHT_LEMON 0xF1E8B8

# define BTN_COLOR_NONACTIVE	0xe76f51
# define BTN_COLOR_HOVER 		0xe9c46a
# define BTN_COLOR_CLICK		0x2a9d8f
# define TEXT_BOX_UNFOCUSED		0xEFB366
# define TEXT_BOX_FOCUSED		0xF4A261
# define LAYER_COLOR			LIGHT_LEMON
# define GUI_BG					0x193038

#endif
