#include "rt.h"

static int	hex_num(char a)
{
	int		i;
	char	*hex_char;

	i = 0;
	hex_char = "aAbBcCdDeEfF";
	if (a > 47 && a < 58)
		return (a - '0');
	while (i < 12)
	{
		if (a == hex_char[i])
			return (10 + i / 2);
		i++;
	}
	rt_raise_error(ERR_PARSING_WRONG_COLOR);
	return (0);
}

int			hex_to_int(const char *temp)
{
	int i;
	int result;
	int len;

	result = 0;
	len = ft_strlen(temp);
	i = 0;
	if (len != 8 && len != 6)
		rt_raise_error(ERR_PARSING_WRONG_COLOR);
	if (len == 8)
	{
		if (temp[0] == '0' && (temp[1] == 'x' || temp[1] == 'X'))
			i = 2;
		else
			rt_raise_error(ERR_PARSING_WRONG_COLOR);
	}
	while (i < len)
	{
		result *= 16;
		result = result + hex_num(temp[i]);
		i++;
	}
	return (result);
}
