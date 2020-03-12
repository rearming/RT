#include "test_header.h"
#include "rt_fsm.h"

t_fsm_translation	*fsm_init_translations(int translations_num, va_list ap)
{
	t_fsm_translation	*translations;
	int					i;

	translations = rt_safe_malloc(sizeof(t_fsm_translation) * translations_num);
	i = 0;
	while (i < translations_num)
	{
		translations[i] = va_arg(ap, t_fsm_translation);
		i++;
	}
	return (translations);
}

t_fsm_state		fsm_create_state(t_fsm_state new_state, ...)
{
	t_fsm_state		state;
	va_list			ap;

	state.data = NULL;
	state.func = new_state.func;
	state.translations_num = new_state.translations_num;
	state.name = new_state.name;
	state.processed = false;
	if (state.translations_num > 0)
	{
		va_start(ap, new_state);
		state.translations = fsm_init_translations(new_state.translations_num, ap);
		va_end(ap);
	}
	return (state);
}

bool		fsm_get_next_state(t_fsm_state *current_state, t_fsm_state **out_state, void *condition_check)
{
	int		i;

	i = 0;
	while (i < current_state->translations_num)
	{
		if (current_state->translations[i].condition(condition_check))
		{
			*out_state = current_state->translations[i].next_state;
			(*out_state)->processed = false;
			return (true);
		}
		i++;
	}
	return (false);
}

void			fsm_run(t_fsm_state *fsm)
{
	t_fsm_state		*current_state;

	current_state = &fsm[0];
	while (21)
	{
		if (!current_state->processed)
			current_state->func(current_state->data);
		current_state->processed = true;
		if (!fsm_get_next_state(current_state, &current_state, NULL) || current_state->translations_num <= 0)
			return ;
	}
}
