#include <printf.h>
#include <stdint.h>

void	print_bits(uint64_t bits, int len, const char *definition)
{
	char		bits_str[64];
	uint64_t	mask = (1 << 0);

	printf("bits of [%s]: \n", definition);
	for (int i = 0; i < len; ++i)
	{
		bits_str[(len - 1) - i] = ((bits & mask) != 0L) + '0';
		mask <<= 1;
	}
	bits_str[len] = 0;
	printf("%s\n", bits_str);
}