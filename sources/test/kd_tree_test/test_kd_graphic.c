#include "test_header.h"
#include "test_kd_tree_header.h"

# define SCALE 100

void			kd_render_bounds(void *tree_ptr)
{
	if (!tree_ptr)
		return;

	t_kd_tree		*tree = tree_ptr;
	SDL_Rect		bounds_rect;

//	if (tree->left == NULL || tree->right == NULL)
//		SDL_SetRenderDrawColor(g_sdl.rend, 200, 0, 0, 255);
//	else
//		SDL_SetRenderDrawColor(g_sdl.rend, 0, 200, 0, 255);

	bounds_rect.x = (int)(tree->bounds.arr[0].x * SCALE);
	bounds_rect.y = (int)(tree->bounds.arr[0].y * SCALE);
	bounds_rect.w = (int)(fabsf(tree->bounds.arr[0].x - tree->bounds.arr[1].x) * SCALE);
	bounds_rect.h = (int)(fabsf(tree->bounds.arr[0].y - tree->bounds.arr[2].y) * SCALE);
	SDL_RenderDrawRect(g_sdl.rend, &bounds_rect);

//	ft_printf("x: [%i], y: [%i], w: [%i], h: [%i]\n",
//			bounds_rect.x, bounds_rect.y, bounds_rect.w, bounds_rect.h);

	kd_render_bounds(tree->left);
	kd_render_bounds(tree->right);
}

void			kd_render_obj_bounds(t_kd_obj *objects)
{
	SDL_SetRenderDrawColor(g_sdl.rend, 57, 207, 205, 255);

	for (int i = 0; i < KD_SCENE_HEIGHT * KD_SCENE_WIDTH; ++i)
	{
		SDL_Rect	obj_rect;
		t_bounds	bounds;

		if (objects[i].index != NOT_SET)
		{
			bounds = objects[i].bounds;

			obj_rect.x = (int)bounds.arr[0].x * SCALE;
			obj_rect.y = (int)bounds.arr[0].y * SCALE;
			obj_rect.w = (int)(fabsf(bounds.arr[0].x - bounds.arr[1].x) * SCALE);
			obj_rect.h = (int)(fabsf(bounds.arr[0].y - bounds.arr[2].y) * SCALE);

			SDL_RenderFillRect(g_sdl.rend, &obj_rect);
		}
	}
}

void kd_draw_loop(t_kd_obj *objects)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					SDL_DestroyRenderer(g_sdl.rend);
					SDL_DestroyWindow(g_sdl.win);
					SDL_Quit();
					exit(0);
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
				{
					g_max_height++;
					start_build_kd_tree(objects);
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
				{
					g_max_height--;
					start_build_kd_tree(objects);
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_R)
				{
					g_max_height = 1;
					test_kd_tree_main();
					return;
				}
			}
			SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

		}
		if (event.type == SDL_QUIT)
			break ;
	}
}

void		graphic_print_kd_tree(t_kd_tree *tree, t_kd_obj *objects)
{
	SDL_SetRenderDrawColor(g_sdl.rend, 0, 0, 0, 255);
	SDL_RenderClear(g_sdl.rend);

	SDL_SetRenderDrawColor(g_sdl.rend, 0, 255, 0, 255);
	kd_render_bounds(tree);
	SDL_SetRenderDrawColor(g_sdl.rend, 150, 0, 0, 255);
	kd_render_obj_bounds(objects);

	SDL_RenderPresent(g_sdl.rend);
}
