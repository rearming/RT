unsigned long	rt_hash(const char *str)
{
	unsigned long	hash;
	int				c;

	if (!str)
		return (0);
	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}
