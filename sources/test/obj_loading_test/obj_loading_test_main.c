#include "test_header.h"
#include "rt_load_obj_files.h"

t_opencl	g_opencl;
t_sdl		g_sdl;

int		main(int argc, char **argv)
{
	if (argc != 2)
		rt_raise_error("model loading test: path to obj not specified!");

	t_meshes	meshes;

	clock_t		start = clock();
	rt_load_obj_file(argv[1], &meshes);
	clock_t		end = clock();
	printf("mesh [%s] loaded in [%f] sec.\n", argv[1], (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}