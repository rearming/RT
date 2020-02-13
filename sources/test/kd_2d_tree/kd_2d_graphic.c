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
	aabb_rect.y = screen_aabb.bounds.max.y;
	aabb_rect.w = (int)screen_aabb.bounds.max.x - (int)screen_aabb.bounds.min.x;
	aabb_rect.h = (int)screen_aabb.bounds.min.y - (int)screen_aabb.bounds.max.y;

//	if (tree->left == NULL || tree->right == NULL)
//		SDL_SetRenderDrawColor(g_sdl.rend, 200, 0, 0, 255);
//	else
//		SDL_SetRenderDrawColor(g_sdl.rend, 0, 200, 0, 255);

	SDL_RenderDrawRect(g_sdl.rend, &aabb_rect);

//	print_2d_aabb(tree->aabb);
//	print_2d_aabb(screen_aabb);
//	ft_printf("x: [%i], y: [%i], w: [%i], h: [%i]\n",
//			aabb_rect.x, aabb_rect.y, aabb_rect.w, aabb_rect.h);

	kd_render_bounds(tree->left);
	kd_render_bounds(tree->right);
}

void			kd_render_obj_bounds(t_aabb *obj_aabbs, int num_aabbs)
{
	for (int i = 0; i < num_aabbs; ++i)
	{
		SDL_Rect		aabb_rect;
		t_aabb			screen_aabb;

		screen_aabb.bounds.min.x = SCALE * obj_aabbs[i].bounds.min.x + WIN_WIDTH / 2;
		screen_aabb.bounds.min.y = WIN_HEIGHT / 2 - SCALE * obj_aabbs[i].bounds.min.y;

		screen_aabb.bounds.max.x = SCALE * obj_aabbs[i].bounds.max.x + WIN_WIDTH / 2;
		screen_aabb.bounds.max.y = WIN_HEIGHT / 2 - SCALE * obj_aabbs[i].bounds.max.y;

		aabb_rect.x = screen_aabb.bounds.min.x;
		aabb_rect.y = screen_aabb.bounds.max.y;
		aabb_rect.w = (int)screen_aabb.bounds.max.x - (int)screen_aabb.bounds.min.x;
		aabb_rect.h = (int)screen_aabb.bounds.min.y - (int)screen_aabb.bounds.max.y;

//		print_2d_aabb(obj_aabbs[i]);
//		print_2d_aabb(screen_aabb);
//		ft_printf("x: [%i], y: [%i], w: [%i], h: [%i]\n",
//				aabb_rect.x, aabb_rect.y, aabb_rect.w, aabb_rect.h);

		SDL_SetRenderDrawColor(g_sdl.rend, 57, 207, 205, 255);
		SDL_RenderFillRect(g_sdl.rend, &aabb_rect);
		SDL_SetRenderDrawColor(g_sdl.rend, 255, 0, 0, 255);
		SDL_RenderDrawRect(g_sdl.rend, &aabb_rect);
	}
}

void		kd_2d_draw_loop(t_aabb *obj_aabbs, int num_aabbs)
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
					g_empty_cost += 0.1f;
					start_build_kd_2d_tree(obj_aabbs, num_aabbs);
				}
				else if (event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
				{
					if (g_empty_cost - 0.2f > 0)
						g_empty_cost -= 0.1f;
					g_max_height--;
					start_build_kd_2d_tree(obj_aabbs, num_aabbs);
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

	kd_render_obj_bounds(obj_aabbs, num_aabbs);
	SDL_SetRenderDrawColor(g_sdl.rend, 0, 255, 0, 255);
	kd_render_bounds(tree);

	SDL_RenderPresent(g_sdl.rend);
}