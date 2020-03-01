# define STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "rt.h"
#include "rt_math_utils.h"
#include "stb_image.h"
#include "stb_image_resize.h"

static int	*rt_memcpy(int *help, int size_dst, int type)
{
	int i;

	i = -1;
	if (type == 1)
	{
		while (++i < size_dst)
			help[i] = g_textures.texture_list[i];
	}
	else
	{
		while (++i < size_dst)
			g_textures.texture_list[i] = help[i];
	}
	return (help);
}
static void		rt_add_texture_and_info(const int *src,
		int size_src, int texture_num)
{
	int	*help;
	int		i;
	int		j;
	int		size_dst;

	size_dst = g_textures.texture_info[texture_num].start;
	if (size_dst != 0)
	{
		help = (int *)rt_safe_malloc(sizeof(int) * size_dst);
		help = rt_memcpy(help, size_dst, 1);
		free(g_textures.texture_list);
		g_textures.texture_list = (int *)rt_safe_malloc(sizeof(float)
				* (size_dst + size_src));
		help = rt_memcpy(help, size_dst, 0);
		free(help);
	}
	else
		g_textures.texture_list = (int *)rt_safe_malloc(sizeof(float)
				* (size_dst + size_src));
	j = 0;
	i = size_dst;
	while (j < size_src)
		g_textures.texture_list[i++] = src[j++];
}


static void			rt_change_format_and_add(const float *tmp_texture,
		int texture_num)
{
	int		i;
	int		j;
	int		*tmp_texture_list;
	int		texture_list_size;

	i = 0;
	j = 0;
	texture_list_size = g_textures.texture_info[texture_num].width
			* g_textures.texture_info[texture_num].height;
	tmp_texture_list = (int *)rt_safe_malloc(sizeof(int)
			* texture_list_size);
	while (j < texture_list_size)
	{
		tmp_texture_list[j] = get_int_color((cl_float3){.x = tmp_texture[i], .y = tmp_texture[i + 1], .z = tmp_texture[i + 2]}); // is it bad or not?
		i += 3;
		j++;
	}
	rt_add_texture_and_info(tmp_texture_list, j, texture_num);
	free(tmp_texture_list);
	if (texture_num + 1 == (int)g_textures.texture_info_size)
		g_textures.texture_list_size =
				g_textures.texture_info[texture_num].start + j;
}

void			rt_textures_init(void)
{
	int				i;
	char			*tmp_filename;
	float			*tmp_texture;

	i = init_basic_textures_parameters();
	while (++i < (int)g_textures.texture_info_size)
	{
		if (!(tmp_filename = (ft_strchr(g_textures.textures_names->name, 47)
			!= NULL) ? ft_strdup(g_textures.textures_names->name) :
			ft_strjoin(TEXTURES_FOLDER, g_textures.textures_names->name)))
			return (rt_raise_error(ERR_INVALID_TEXRTURE));
		tmp_texture = stbi_loadf(tmp_filename, &g_textures.texture_info[i].width,
		&g_textures.texture_info[i].height, &g_textures.texture_info[i].bpp, STBI_rgb);
		if (!tmp_texture)
			return (rt_raise_error(ERR_INVALID_TEXRTURE));
		rt_add_start_position(i);
		rt_change_format_and_add(tmp_texture, i);
		free(tmp_filename);
		free(tmp_texture);
		if (g_textures.texture_list == NULL)
			return (rt_raise_error(ERR_INVALID_TEXRTURE));
//		free(g_textures.textures_names->name);
//		free(g_textures.textures_names);
		g_textures.textures_names = g_textures.textures_names->next;
	}
}

void 		rt_skybox_init(void)
{
	char 	*tmp_filename;
	float	*tmp_texture;
	int 	i;
	int 	j;
	int		texture_list_size;

	i = 0;
	j = 0;
	if (!(tmp_filename = (ft_strchr(g_textures.skybox_info->skybox_name, 47) != NULL)
						 ? ft_strdup(g_textures.skybox_info->skybox_name) :
						 ft_strjoin(TEXTURES_FOLDER, g_textures.skybox_info->skybox_name)))
		return (rt_raise_error(ERR_INVALID_TEXRTURE));
	tmp_texture = stbi_loadf(tmp_filename, &g_textures.skybox_info->width,
							 &g_textures.skybox_info->height, &g_textures.skybox_info->bpp, STBI_rgb);
	texture_list_size = g_textures.skybox_info->width * g_textures.skybox_info->height;
	g_textures.skybox_list = rt_safe_malloc(sizeof(cl_float3) * texture_list_size);
	while (j < texture_list_size)
	{
		g_textures.skybox_list[j].x = tmp_texture[i];
		g_textures.skybox_list[j].y = tmp_texture[i + 1];
		g_textures.skybox_list[j].z = tmp_texture[i + 2];
		i += 3;
		j++;
	}
	g_textures.skybox_info->size = texture_list_size;
	free(tmp_filename);
	free(tmp_texture);
}