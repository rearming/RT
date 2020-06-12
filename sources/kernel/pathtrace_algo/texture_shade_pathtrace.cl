/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_shade_pathtrace.cl                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 12:07:40 by ahorker           #+#    #+#             */
/*   Updated: 2020/06/12 12:07:46 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float3		texture_shade_pathtrace(
		__global const t_texture_info *texture_info,
		__global const int *texture_list,
		__global const t_object *object,
		t_ray *ray,
		t_rayhit *hit,
		t_material material,
		float *seed,
		float2 pixel)
{
	if (material.texture_pbr) //change rayhit
		change_coordinates(hit, texture_info, texture_list, object);
	const float		specular_chance = material.specular_texture;
	const float3	color = texture(hit, texture_info, texture_list, object); //change material.emission_color to color

	const float		surface_chance = rt_randf(seed, pixel);
	const float		transmit_chance = rt_randf(seed, pixel);

	if (material.emission_power > 0)
	{
		ray->energy = 0;
		return color * material.emission_power;
	}
	if (surface_chance < specular_chance)
	{
		if (transmit_chance < material.transmittance) // if transparent
		{
			calc_refraction_pathtrace(ray, hit, &material, color, seed, pixel, specular_chance);
		}
		else
		{
			calc_reflection_pathtrace(ray, hit, &material, color, seed, pixel, specular_chance);
		}
	}
	else //diffuse surface
	{
		if (transmit_chance < material.transmittance) // if transparent
		{
			calc_refraction_pathtrace(ray, hit, &material, material.diffuse, seed, pixel, (1 - specular_chance));
		}
		else
		{
			ray->origin = hit->pos + hit->normal * RT_EPSILON;
			ray->dir = rand_dir_on_hemisphere(hit->normal, seed, pixel, LAMBERT_ALPHA);
			ray->energy *= (1.f / (1 - specular_chance)) * color;
		}
	}
	return 0;
}
