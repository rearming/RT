#ifndef RT_INIT_H
# define RT_INIT_H

# define OPTION_REGENERATE_KD_TREE "--regenerate"

typedef enum		e_init_options
{
	INIT_NONE = 0x0,
	INIT_KD_REGENERATE = (1 << 0),
}					t_init_options;

#endif
