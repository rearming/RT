#include "test_header.h"
#include "rt_fsm.h"

void	f_print_n(void *data)
{
	RT_UNUSED(data);
	printf("{fsm} N in pressed!\n");
}

void	f_print_a(void *data)
{
	RT_UNUSED(data);
	printf("{fsm} Adfee in pressed!\n");
}

void	f_init(void *data)
{
	const char 		*str = data;
	printf("{fsm} init str: [%s]\n", str);
}

void	f_exit(void *data)
{
	RT_UNUSED(data);
	printf("{fsm} exit!\n");
}

bool	f_translate_press_n(void *data)
{
	SDL_Event		*event = data;

	if (event->key.keysym.scancode == SDL_SCANCODE_N)
		return (true);
	return (false);
}

bool	f_translate_press_a(void *data)
{
	SDL_Event		*event = data;

	if (event->key.keysym.scancode == SDL_SCANCODE_A)
		return (true);
	return (false);
}

bool	f_translate_press_r(void *data)
{
	SDL_Event		*event = data;

	if (event->key.keysym.scancode == SDL_SCANCODE_R)
		return (true);
	return (false);
}

bool	f_translate_press_e(void *data)
{
	SDL_Event		*event = data;

	if (event->key.keysym.scancode == SDL_SCANCODE_E)
		return (true);
	return (false);
}

bool	f_translate_press_n_poll(void *data)
{
	SDL_Event		event;
	SDL_PollEvent(&event);
	if (event.key.keysym.scancode == SDL_SCANCODE_N)
		return (true);
	return (false);
}

bool	f_translate_press_a_poll(void *data)
{
	SDL_Event		event;
	SDL_PollEvent(&event);
	if (event.key.keysym.scancode == SDL_SCANCODE_A)
		return (true);
	return (false);
}

bool	f_translate_press_r_poll(void *data)
{
	SDL_Event		event;
	SDL_PollEvent(&event);
	if (event.key.keysym.scancode == SDL_SCANCODE_R)
		return (true);
	return (false);
}

bool	f_translate_press_e_poll(void *data)
{
	SDL_Event		event;
	SDL_PollEvent(&event);
	if (event.key.keysym.scancode == SDL_SCANCODE_E)
		return (true);
	return (false);
}

t_sdl		g_sdl;

int		main(int argc, char **argv)
{
	RT_UNUSED(argc);
	RT_UNUSED(argv);

	rt_sdl_init();

	int				num_states = 4;
	t_fsm_state		*fsm = rt_safe_malloc(sizeof(t_fsm_state) * num_states);

	fsm[0] = fsm_create_state((t_fsm_state){"init", f_init, "yey fsm init!", NULL, 2, false},
			(t_fsm_translation) {&fsm[1], f_translate_press_n},
			(t_fsm_translation) {&fsm[2], f_translate_press_a});

	fsm[1] = fsm_create_state((t_fsm_state){"print N", f_print_n, NULL, NULL, 2, false},
			(t_fsm_translation) {&fsm[0], f_translate_press_r},
			(t_fsm_translation) {&fsm[3], f_translate_press_e});

	fsm[2] = fsm_create_state((t_fsm_state) {"print A", f_print_a, NULL, NULL, 2, false},
			(t_fsm_translation) {&fsm[1], f_translate_press_n},
			(t_fsm_translation) {&fsm[3], f_translate_press_e});

	fsm[3] = fsm_create_state((t_fsm_state){"exit", f_exit, NULL, NULL, 0, false});

	SDL_Event	event;
	t_fsm_state		*current_state = &fsm[0];
	while (21)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				exit(EXIT_SUCCESS);

			if (!current_state->processed)
				current_state->func(current_state->data);
			current_state->processed = true;
			if (!fsm_get_next_state(current_state, &current_state, &event) || current_state->translations_num <= 0)
				break ;
		}
		if (event.type == SDL_QUIT)
			break ;
	}

	return EXIT_SUCCESS;
}
