#include "rt.h"

bool		rt_bit_isset(uint32_t params, uint32_t target)
{
	if (params & target)
		return (true);
	return (false);
}
