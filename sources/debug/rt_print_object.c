#include "rt.h"
#include "rt_debug.h"

void		rt_print_sphere(t_object *sphere)
{
	ft_printf("sphere:\n");
	ft_printf("center: x: [%.2f], y: [%.2f], z: [%.2f]\n",
			sphere->center.x, sphere->center.y, sphere->center.z);
	ft_printf("radius: [%.2f]\n", sphere->radius);
	rt_print_material(&sphere->material);
	ft_printf("\n");
}
