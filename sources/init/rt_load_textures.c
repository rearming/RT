# define STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "rt.h"
#include "stb_image.h"
#include "stb_image_resize.h"

static float	*rt_memcpy(float *help, int size_dst, int type)
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

static void		rt_add(const float *scr, int size_src, int texture_num)
{
	float	*help;
	int		i;
	int		j;
	int		size_dst;

	size_dst = g_textures.texture_info[texture_num].start;
	if (size_dst != 0)
	{
		help = (float *)rt_safe_malloc(sizeof(float) * size_dst);
		help = rt_memcpy(help, size_dst, 1);
		free(g_textures.texture_list);
		g_textures.texture_list = (float *)rt_safe_malloc(sizeof(float)
				* (size_dst + size_src));
		help = rt_memcpy(help, size_dst, 0);
		free(help);
	}
	else
		g_textures.texture_list = (float *)rt_safe_malloc(sizeof(float)
				* (size_dst + size_src));
	j = 0;
	i = size_dst;
	while (j < size_src)
		g_textures.texture_list[i++] = scr[j++];
}

static void		rt_change_format_and_add(const unsigned char *tmp_texture,
		int texture_num)
{
	int		i;
	int		j;
	float	*tmp_texture_list;
	int		texture_list_size;

	i = 0;
	j = 0;
	texture_list_size = g_textures.texture_info[texture_num].width
			* g_textures.texture_info[texture_num].height;
	tmp_texture_list = (float *)rt_safe_malloc(sizeof(float)
			* texture_list_size);
	while (i < texture_list_size * 3)
	{
		tmp_texture_list[j] = (float)(tmp_texture[i] << 16 |
				tmp_texture[i + 1] << 8 | tmp_texture[i + 2]);
		i += 3;
		j++;
	}
	free(tmp_texture_list);
	rt_add(tmp_texture_list, j, texture_num);
	if (texture_num + 1 == TEXTURE_NUM)
		init_final_texture_parameters(
				g_textures.texture_info[texture_num].start + j);
}

static unsigned char	*resize_image(unsigned char *tmp_texture,
									  int texture_num, int new_height)
{
	unsigned char	*resized_texture;
	int				new_width;

	new_width = new_height * g_textures.texture_info[texture_num].width
				/ g_textures.texture_info[texture_num].height;
	resized_texture = (unsigned char *)rt_safe_malloc(sizeof(unsigned char)
													  * new_width * new_height * 3);
	stbir_resize_uint8(tmp_texture, g_textures.texture_info[texture_num].width,
					   g_textures.texture_info[texture_num].height, 0,
					   resized_texture, new_width, new_height, 0, STBI_rgb);
	g_textures.texture_info[texture_num].width = new_width;
	g_textures.texture_info[texture_num].height = new_height;
	free(tmp_texture);
	return (resized_texture);
}

void			rt_textures_init(void)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp_filename;
	unsigned char	*tmp_texture;

	if (!(dir = opendir("textures/2sphere/")))
		return (rt_raise_error(ERR_INVALID_TEXRTURE_DIR));
	i = init_basic_textures_parameters();
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[i] == '.')
			continue;
		if (!(tmp_filename = ft_strjoin("textures/2sphere/", entry->d_name)))
			return (rt_raise_error(ERR_INVALID_TEXRTURE));
		tmp_texture = stbi_load(tmp_filename, &g_textures.texture_info[i].width,
								&g_textures.texture_info[i].height, &g_textures.texture_info[i].bpp,
								STBI_rgb);
		if (g_textures.texture_info[i].height > WIN_HEIGHT * SCALE_HEIGHT * 3) //есть какой-то размер при котором картинка плохо растягивается и плохо сжимается
			tmp_texture = resize_image(tmp_texture, i, 3 * WIN_HEIGHT);
		rt_add_start_position(i);
		rt_change_format_and_add(tmp_texture, i);
		free(tmp_filename);
		stbi_image_free(tmp_texture);
		if (g_textures.texture_list == NULL)
			return (rt_raise_error(ERR_INVALID_TEXRTURE));
		i++;
	}
	closedir(dir);
}