#include "rt.h"

void	print_tmp(t_tmp *tmp)
{
	int i;

	i = 0;
	while (tmp)
	{
		printf(" i = %i structure_type = %i type = %i, ", i, tmp->structure_type, tmp->type);
		if (tmp->checker[ROTATION] == true)
			printf("rotation = [%.3f][%.3f][%.3f], ", tmp->rotation.x, tmp->rotation.y, tmp->rotation.z);
		if (tmp->checker[POS] == true)
			printf ("pos = [%.3f][%.3f][%.3f], ", tmp->pos.x, tmp->pos.y, tmp->pos.z);
		if (tmp->checker[INTENSITY] == true)
			printf("intensity = %.3f, ", tmp->intensity);
		if (tmp->checker[DIRECTION] == true)
			printf("dir = [%.3f][%.3f][%.3f], ", tmp->dir.x, tmp->dir.y, tmp->dir.z);
		if (tmp->checker[COLOR] == true)
			printf("color = [%.3f][%.3f][%.3f], ", tmp->color.x, tmp->color.y, tmp->color.z);
		if (tmp->checker[NORMAL] == true)
			printf("normal = [%.3f][%.3f][%.3f], ",tmp->normal.x, tmp->normal.y, tmp->normal.z);
		if (tmp->checker[AXIS] == true)
			printf("axis = [%.3f][%.3f][%.3f], ", tmp->axis.x, tmp->axis.y, tmp->axis.z);
		if (tmp->checker[CENTER] == true)
			printf("center = [%.3f][%.3f][%.3f], ", tmp->center.x, tmp->center.y, tmp->center.z);
		if (tmp->checker[VMIN] == true)
			printf("vmin = [%.3f][%.3f][%.3f], ", tmp->vmin.x, tmp->vmin.y, tmp->vmin.z);
		if (tmp->checker[VMAX] == true)
			printf("vmax = [%.3f][%.3f][%.3f], ", tmp->vmax.x, tmp->vmax.y, tmp->vmax.z);
		if (tmp->checker[DISTANCE] == true)
			printf("distance = %.3f, ", tmp->distance);
		if (tmp->checker[RADIUS] == true)
			printf("radius = %.3f, ", tmp->radius);
		if (tmp->checker[ANGLE] == true)
			printf("angle = %.3f, ", tmp->angle);
		if (tmp->checker[LEN] == true)
			printf("len = %.3f, ", tmp->len);
		if (tmp->checker[AMBIENCE] == true)
			printf("ambience = [%.3f][%.3f][%.3f], ", tmp->ambience.x, tmp->ambience.y, tmp->ambience.z);
		if (tmp->checker[DIFFUSE] == true)
			printf("diffuse = [%.3f][%.3f][%.3f], ", tmp->diffuse.x, tmp->diffuse.y, tmp->diffuse.z);
		if (tmp->checker[SPECULAR] == true)
			printf("specular = [%.3f][%.3f][%.3f], ", tmp->specular.x, tmp->specular.y, tmp->specular.z);
		if (tmp->checker[PHONG_EXP] == true)
			printf("phong_exp = %.3f, ", tmp->phong_exp);
		if (tmp->checker[SMOOTHNESS] == true)
			printf("smoothness = %.3f, ", tmp->smoothness);
		if (tmp->checker[TRANSMITTANCE] == true)
			printf("transmittance = %.3f, ", tmp->transmittance);
		if (tmp->checker[REFRACTION] == true)
			printf("refraction = %.3f, ", tmp->refraction);
		if (tmp->checker[EMISSION_COLOR] == true)
			printf("emission_color = [%.3f][%.3f][%.3f], ", tmp->emission_color.x,tmp->emission_color.y, tmp->emission_color.z);
		if (tmp->checker[EMISSION_POWER] == true)
			printf("emission_power = %.3f, ", tmp->emission_power);
		if (tmp->checker[SPECULAR_TEXTURE] == true)
			printf("specular_texture = %.3f, ",tmp->specular_texture);
		if (tmp->checker[TEXTURE] == true)
			printf("texture_number = %i, ", tmp->texture_number);
		if (tmp->checker[TEXTURE_POS] == true)
			printf("texture_pos = [%.3f][%.3f][%.3f]", tmp->texture_position.x, tmp->texture_position.y, tmp->texture_position.z);
		printf("\n");
		i++;
		tmp = tmp->next;
	}
}

void			print_textures(void)
{
	t_texture_name *tmp;
	tmp = g_textures.textures_names;
	while (tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}