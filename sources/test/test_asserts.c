#include "test_header.h"

bool		assert_float_equals(float expected, float actual)
{
	bool	result = false;
#ifdef VERBOSE
	static int test_count = 0;
#endif
	if (expected == actual)
		result = true;
#ifdef VERBOSE
	else
	{
		ft_printf("test [%i] failed, [%f] != [%f]\n", expected, actual);
	}
	test_count++;
#endif
	return result;
}

bool		assert_int_equals(int expected, int actual)
{
	static int test_count = 0;
	bool	result = false;

	if (expected == actual)
	{
		result = true;
#ifdef VERBOSE
		ft_printf("test [%i] passed, [%i] == [%i]\n", test_count, expected, actual);
#endif
	}
	else
	{
		ft_printf("test [%i] failed, [%i] != [%i]\n", test_count, expected, actual);
	}
	test_count++;
	return result;
}
