#include "rt.h"
#include "rt_gui.h"
#include "time.h"


char*		get_time(void)
{
	char			*time_;
	const time_t	cur = time(NULL);

	time_ = ctime(&cur);
	return (time_);
}

char		*name_generator(char *ext)//todo : remove \n from filename
{
	char *filename;
	char *tmp;

	tmp = ft_strjoin("Screenshot ", get_time());
	filename = ft_strjoin(tmp, ext);
	free(tmp);
	return (filename);
}
