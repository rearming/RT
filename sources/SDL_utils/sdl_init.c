#include "rt.h"

#define FONT_SIZE 30

void		gui_render_algo_buttons_init(int count, int height)
{
	g_sdl.buttons[pt_btn].button = (SDL_Rect){.x = 0, .y = 0,
			.w = RT_GUI_WIDTH / count, .h = height};
	g_sdl.buttons[pt_btn].color.value = 0xFF0000;
	g_sdl.buttons[rt_btn].button = (SDL_Rect){.x = RT_GUI_WIDTH / 3, .y = 0,
			.w = RT_GUI_WIDTH / count, .h = height};
	g_sdl.buttons[pt_btn].color.value = 0xFF00;
	g_sdl.buttons[rm_btn].button = (SDL_Rect){.x = 2 * RT_GUI_WIDTH / 3, .y = 0,
			.w = RT_GUI_WIDTH / count, .h = height};
	g_sdl.buttons[pt_btn].color.value = 0xFF;
}

void 		init_gui(void)
{
	SDL_Surface *text_box;
	TTF_Font *font;

	gui_render_algo_buttons_init(3, 100);
	TTF_Init();
	g_sdl.surface = SDL_GetWindowSurface(g_sdl.win_tool);
	SDL_FillRect(g_sdl.surface, NULL, SDL_MapRGB(g_sdl.surface->format, 255, 255, 255));
	font = TTF_OpenFont("Fonts/Techno.ttf", FONT_SIZE);
	SDL_FillRect(g_sdl.surface, &g_sdl.buttons[pt_btn], SDL_MapRGB(g_sdl.surface->format, 128, 0, 0));
	SDL_FillRect(g_sdl.surface, &g_sdl.buttons[rt_btn], SDL_MapRGB(g_sdl.surface->format, 0, 128, 0));
	SDL_FillRect(g_sdl.surface, &g_sdl.buttons[rm_btn], SDL_MapRGB(g_sdl.surface->format, 0, 0, 128));
//	char text[] = "hello world!";//todo добавить шрифт
//	SDL_Rect sign = (SDL_Rect){.x = 0, .y = 0, .h = 100, .w = 100};
//	text_box = TTF_RenderText_Blended(font, text,(SDL_Color){.r = 0, .g = 0, .b = 0});
//	SDL_BlitSurface(text_box, NULL, g_sdl.surface, &sign);
//	SDL_FreeSurface(text_box);
//	TTF_CloseFont(font);
	SDL_UpdateWindowSurface(g_sdl.win_tool);
}

void		rt_sdl_init(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		rt_raise_error(ERR_SDL_INIT);
	if (!(g_sdl.win = SDL_CreateWindow(WIN_TITLE,
			200, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		rt_raise_error(ERR_SDL_WIN);
	if (!(g_sdl.win_tool = SDL_CreateWindow(RT_GUI_NAME,
			200 + WIN_WIDTH, SDL_WINDOWPOS_CENTERED,
			RT_GUI_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		rt_raise_error(ERR_SDL_WIN);
	init_gui();
	if (!(g_sdl.rend = SDL_CreateRenderer(g_sdl.win, -1,
			SDL_RENDERER_ACCELERATED)))
		rt_raise_error(ERR_SDL_RENDER);
	if (!(g_sdl.texture = SDL_CreateTexture(g_sdl.rend,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		rt_raise_error(ERR_SDL_TEXTURE_CREATE);
}
