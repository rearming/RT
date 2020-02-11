//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct		s_bounds
//{
//	cl_float3		min;
//	cl_float3		max;
//}					t_bounds;
//
//typedef union		s_aabb
//{
//	cl_float3		arr[2];
//	t_bounds		bounds;
//}					t_aabb;
//
//t_aabb	*parse_raw_aabbs(const char *filename, int *out_aabbs_num)
//{
//	FILE *fp = fopen(filename, "rb");
//
//	fread(out_aabbs_num, sizeof(int), 1, fp);
//
//	unsigned char	*raw_data = malloc(sizeof(t_aabb) * (*out_aabbs_num));
//
//	fread(raw_data, sizeof(t_aabb) * (*out_aabbs_num), 1, fp);
//
//	t_aabb	*parsed_aabbs = malloc(sizeof(t_aabb) * (*out_aabbs_num));
//
//	printf("parsed aabbs num: [%i]\n", *out_aabbs_num);
//
//	for (int i = 0; i < *out_aabbs_num; ++i)
//		parsed_aabbs[i] = ((t_aabb*)raw_data)[i];
//	return parsed_aabbs;
//}
