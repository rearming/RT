
typedef struct		s_ray
{
	float3			origin;
	float3			dir;
	float3			energy;
}					t_ray;

typedef struct		s_rayhit
{
	float3			pos;
	float			distance;
	float3			normal;
}					t_rayhit;
