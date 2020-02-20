#include "rt.h"
#include "rt_parsing.h"

void		parse_object(t_tmp *tmp, const char *key, json_t *value,
		uint32_t *renderer_flags)
{
	int type_of_structure;

	type_of_structure = ft_type_of_structure(key);
	if (type_of_structure != -1)
	{
		if (type_of_structure == MATERIAL)
			check_duplicated(tmp->checker, type_of_structure);
		else
		{
			if (tmp->structure_type == NOT_SET)
				tmp->structure_type = type_of_structure;
			else
			{
				tmp->next = (t_tmp *)rt_safe_malloc(sizeof(t_tmp));
				init_tmp(tmp->next);
				tmp = tmp->next;
				tmp->structure_type = type_of_structure;
			}
		}
		parse_json_file(value, tmp, renderer_flags);
	}
	else
		rt_raise_error(ERR_PARSING_WRONG_TYPE);
}
