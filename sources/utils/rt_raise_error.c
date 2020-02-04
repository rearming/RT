#include "libft.h"
#include "rt_errors.h"

void			rt_raise_error(const char *err_str)
{
	if (err_str)
		ft_printf_fd(STDERR_FILENO, "%s\n", err_str);
	else
		ft_printf_fd(STDERR_FILENO, "UNKNOWN ERROR!\n");
	exit(1);
}
