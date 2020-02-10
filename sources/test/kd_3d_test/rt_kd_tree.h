#ifndef RT_KD_TREE_H
# define RT_KD_TREE_H

typedef struct		s_bounds
{
	cl_float3		min;
	cl_float3		max;
}					t_bounds;

typedef union		s_aabb
{
	cl_float3		arr[2];
	t_bounds		bounds;
}					t_aabb;

typedef struct		s_split_p
{
	cl_float3		p0;
	cl_float3		p1;
	cl_float3		p2;
}					t_split_p;

typedef struct		s_split
{
	cl_float3		arr[3];
	t_split_p		points;
}					t_split;

t_aabb		*rt_get_all_aabbs(t_meshes *meshes);

#endif
