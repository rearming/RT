#ifndef RT_FSM_H
# define RT_FSM_H

#include <stdbool.h>
#include <stdarg.h>

typedef void	(*t_state_func)(void*);
typedef bool	(*t_condition_func)(void*);

typedef struct		s_fsm_state t_fsm_state;

typedef struct		s_fsm_translation
{
	t_fsm_state			*next_state;
	t_condition_func	condition;
}					t_fsm_translation;

typedef struct		s_fsm_state
{
	const char			*name;
	t_state_func		func;
	void				*data;
	t_fsm_translation	*translations;
	int					translations_num;
	bool				processed;
}					t_fsm_state;

t_fsm_state		fsm_create_state(t_fsm_state new_state, ...);
bool			fsm_get_next_state(t_fsm_state *current_state, t_fsm_state **out_state, void *condition_check);
void			fsm_run(t_fsm_state *fsm);

#endif
