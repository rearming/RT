#include "rt.h"

void		*rt_safe_malloc(size_t size)
{
	void		*allocated_ptr;

	allocated_ptr = malloc(size);
	if (!allocated_ptr)
		rt_raise_error(ERR_MALLOC);
	return (allocated_ptr);
}
