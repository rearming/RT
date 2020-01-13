#include "test_header.h"

t_point		*test_get_point_arr(int arr_size)
{
	t_point		*test_arr = rt_safe_malloc(arr_size * sizeof(t_point));

	for (int i = 0; i < arr_size; ++i)
		test_arr[i] = (t_point){i, -i, i * i, {i % 2 ? COL_GREEN : COL_GREY}};
//	for (int j = 0; j < 10; ++j)
//	{
//		printf("%d: x: [%d] y: [%d] z: [%d] color: [%s]\n",
//				j, test_arr[j].x, test_arr[j].y, test_arr[j].z, test_arr[j].color.value == COL_GREEN ? "COL_GREEN" : "COL_GREY");
//	}
	return test_arr;
}

int			*test_get_int_arr(int arr_size)
{
	int		*test_arr = rt_safe_malloc(arr_size * sizeof(int));

	for (int i = 0; i < arr_size; ++i)
		test_arr[i] = i * i;
	return test_arr;
}

void		test_rt_loop(t_rt *rt)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				rt_render(NULL, &test_run_kernels);
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				exit(0);
		}
		if (event.type == SDL_QUIT)
			break ;
	}
}

void 	dummy_render_func(t_rt *rt)
{
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
	{
		g_img_data[i] = COL_GREEN;
	}
}
