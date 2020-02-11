#include "test_header.h"
#include "kd_2d_tree_header.h"

# define SCALE 100

void			kd_render_bounds(void *tree_ptr)
{
	if (!tree_ptr)
		return;

	t_kd_tree		*tree = tree_ptr;
	SDL_Rect		aabb_rect;

	t_aabb			screen_aabb;
	screen_aabb.bounds.min.x = SCALE * tree->aabb.bounds.min.x + WIN_WIDTH / 2;
	screen_aabb.bounds.min.y = WIN_HEIGHT / 2 - SCALE * tree->aabb.bounds.min.y;

	screen_aabb.bounds.max.x = SCALE * tree->aabb.bounds.max.x + WIN_WIDTH / 2;
	screen_aabb.bounds.max.y = WIN_HEIGHT / 2 - SCALE * tree->aabb.bounds.max.y;

	aabb_rect.x = screen_aabb.bounds.min.x;
	aabb_rect.y = screen_aabb.bounds.min.y;
	aabb_rect.w = (int)screen_aabb.bounds.max.x - (int)screen_aabb.bounds.min.x;
	aabb_rect.h = (int)screen_aabb.bounds.max.y - (int)screen_aabb.bounds.min.y;

//	if (tree->left == NULL || tree->right == NULL)
//		SDL_SetRenderDrawColor(g_sdl.rend, 200, 0, 0, 255);
//	else
//		SDL_SetRenderDrawColor(g_sdl.rend, 0, 200, 0, 255);

	SDL_RenderDrawRect(g_sdl.rend, &aabb_rect);

	ft_printf("x: [%i], y: [%i], w: [%i], h: [%i]\n",
			aabb_rect.x, aabb_rect.y, aabb_rect.w, aabb_rect.h);

	kd_render_bounds(tree->left);
	kd_render_bounds(tree->right);
}

void			kd_render_obj_bounds(t_aabb *obj_bounds, int num_aabbs)
{
	SDL_SetRenderDrawColor(g_sdl.rend, 57, 207, 205, 255);

	for (int i = 0; i < num_aabbs; ++i)
	{
		SDL_Rect	obj_rect;
		t_bounds	bounds;

//		bounds = objects[i].bounds;
//
//		obj_rect.x = (int)bounds.arr[0].x * SCALE;
//		obj_rect.y = (int)bounds.arr[0].y * SCALE;
//		obj_rect.w = (int)(fabsf(bounds.arr[0].x - bounds.arr[1].x) * SCALE);
//		obj_rect.h = (int)(fabsf(bounds.arr[0].y - bounds.arr[2].y) * SCALE);

		SDL_RenderFillRect(g_sdl.rend, &obj_rect);
	}
}

void		kd_draw_loop(t_aabb *obj_aabbs, int num_aabbs)
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
					start_build_kd_2d_tree(obj_aabbs, num_aabbs);
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
				{
					g_max_height--;
					start_build_kd_2d_tree(obj_aabbs, num_aabbs);
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_R)
				{
					g_max_height = 1;
					test_kd_2d_tree_main();
					return;
				}
			}
			SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

		}
		if (event.type == SDL_QUIT)
			break ;
	}
}

void		graphic_print_kd_tree(t_kd_tree *tree, t_aabb *obj_aabbs, int num_aabbs)
{
	SDL_SetRenderDrawColor(g_sdl.rend, 0, 0, 0, 255);
	SDL_RenderClear(g_sdl.rend);

	SDL_SetRenderDrawColor(g_sdl.rend, 0, 255, 0, 255);
	kd_render_bounds(tree);
	SDL_SetRenderDrawColor(g_sdl.rend, 150, 0, 0, 255);
//	kd_render_obj_bounds(obj_aabbs, num_aabbs);

	SDL_RenderPresent(g_sdl.rend);
}
