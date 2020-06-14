# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/10 23:20:41 by sleonard          #+#    #+#              #
#    Updated: 2042/11/29 15:48:40 by sleonard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
# SOURCES
# ============================================================================ #

SOURCES_FILES =					\
 debug/rt_debug_print_utils.c \
 debug/runtime_debug/rt_debug_info.c \
 \
 math_utils/rt_math_utils.c \
 math_utils/rt_rotation_utils.c \
 math_utils/rt_cl_float3_utils.c \
 math_utils/rt_vector_math.c \
 math_utils/rt_cl_float3_utils2.c \
 \
 OpenCL/rt_opencl_init.c \
 OpenCL/rt_opencl_files_parser.c \
 OpenCL/rt_opencl_render.c \
 OpenCL/rt_opencl_memory_management.c \
 OpenCL/rt_opencl_utils.c \
 OpenCL/rt_opencl_prepare_memory.c \
 OpenCL/rt_init_render_kernel.c \
 OpenCL/rt_opencl_kernels_compile.c \
 OpenCL/rt_opencl_kernels_exec.c \
 OpenCL/rt_opencl_kernels_exec_utils.c \
 OpenCL/rt_opencl_prepare_mem_array.c \
 OpenCL/rt_opencl_cache_program.c \
 \
 rt_parsing/rt_parse_scene.c \
 rt_parsing/json_parser/rt_add_to_scene.c \
 rt_parsing/json_parser/rt_json_utils.c \
 rt_parsing/json_parser/rt_json_utils2.c \
 rt_parsing/json_parser/rt_json_utils3.c \
 rt_parsing/json_parser/rt_parse_array.c \
 rt_parsing/json_parser/rt_parse_boolean.c \
 rt_parsing/json_parser/rt_parse_object.c \
 rt_parsing/json_parser/rt_parse_string.c \
 rt_parsing/json_parser/rt_parse_string2.c \
 rt_parsing/json_parser/rt_parse_textures.c \
 rt_parsing/json_parser/rt_parse_variable.c \
 rt_parsing/json_parser/rt_type_of_parametr.c \
 \
 rt_event_handling/rt_event_utils.c \
 rt_event_handling/rt_settings_change.c \
 rt_event_handling/rt_settings_info.c \
 rt_event_handling/rt_key_event_handing.c \
 rt_event_handling/rt_mouse_event_handling.c \
 rt_event_handling/rt_camera_moves.c \
 rt_event_handling/rt_event_handling.c \
 rt_event_handling/rt_key_event_handing2.c \
 \
 utils/rt_safe_malloc.c \
 utils/rt_raise_error.c \
 utils/rt_exit_clean.c \
 utils/rt_color_utils.c \
 utils/rt_hash.c \
 utils/rt_common_read_file.c \
 \
 SDL_utils/sdl_init.c \
 \
 obj_loading/rt_correct_materials.c \
 obj_loading/rt_load_obj_files.c \
 obj_loading/rt_load_obj_utils.c \
 obj_loading/rt_load_obj_meshes.c \
 obj_loading/rt_load_obj_materials.c \
 obj_loading/rt_load_vertices.c \
 \
 init/rt_init.c \
 init/rt_init_render_params.c \
 init/rt_load_textures.c \
 init/rt_load_textures_utils.c \
 init/rt_parse_options.c \
 \
 render/rt_loop.c \
 render/render.c \
 render/rt_update_params.c \
 \
 kd_tree/rt_kd_get_aabb.c \
 kd_tree/rt_kd_tree_build.c \
 kd_tree/rt_kd_tree_to_array.c \
 kd_tree/rt_kd_tree_utils.c \
 kd_tree/rt_kd_tree_get.c \
 kd_tree/rt_kd_pack_object_indices.c \
 kd_tree/rt_kd_tree_export.c \
 kd_tree/rt_kd_tree_import.c \
 kd_tree/rt_kd_tree_build_aabb_utils.c \
 kd_tree/rt_kd_build_recursive.c \
 kd_tree/rt_kd_split_buckets_sah.c \
 \
 gui/rt_gui_init.c \
 gui/rt_handle_event_gui.c \
 gui/gui_utils/rt_gui_color_utils.c \
 gui/buttons/rt_gui_buttons_render.c \
 gui/buttons/rt_gui_button_callback.c \
 gui/buttons/rt_buttons_border.c \
 gui/buttons/rt_button_label.c \
 gui/buttons/utils/rt_gui_change_algo.c \
 gui/buttons/rt_gui_init_buttons.c \
 gui/buttons/utils/rt_check_hover.c \
 gui/buttons/utils/rt_check_click.c \
 gui/buttons/utils/create_screenshot.c \
 gui/buttons/utils/name_generator.c \
 gui/buttons/utils/get_window_data.c \
 gui/text_box/render_text_box.c \
 gui/text_box/init_text_box.c \
 gui/text_box/rt_gui_text_box_init.c \
 gui/buttons/utils/check_positions.c \
 gui/buttons/rt_gui_buttons_render2.c \
 main.c \

# ============================================================================ #
# BUILD FRACTOL
# ============================================================================ #

OS := $(shell uname)

NAME =							\
	RT

LIBFT =							\
	./libft/libft.a

FT_PRINTF = 					\
	./libft/ft_printf/

D_SRC = sources/
D_OBJ = temp/

SRC_RT = $(addprefix $(D_SRC), $(SOURCES_FILES))
OBJ_RT = $(addprefix $(D_OBJ), $(SOURCES_FILES:.c=.o))

SOURCES_OBJ = $(addprefix $(OBJ_DIR), $(SOURCES_FILES:.c=.o))

CC = clang

CFLAGS = -Wall -Wextra -Werror -O2

RT_INCLUDES =						\
	-I ./includes/				\
    -I ./includes/external		\

ifeq ($(OS), Linux)
SDL2_INCL = $(shell sdl2-config --cflags)
else
SDL2_INCL = -I ./lib/SDL2_libs/SDL2.framework/Headers
endif

ifeq ($(OS), Linux)
SDL2_TTF_INCL =
else
SDL2_TTF_INCL = -I ./lib/SDL2_libs/SDL2_ttf.framework/Headers
endif

INCLUDES = $(RT_INCLUDES) -I $(LIBFT_INCL) $(SDL2_INCL) $(SDL2_TTF_INCL)

ifeq ($(OS), Linux)
FRAMEWORKS = $(shell sdl2-config --libs) -lSDL2_ttf
else
FRW = lib/SDL2_libs
SDL2_FW = $(FRW)SDL2.framework/
TTF_FW = $(FRW)SDL2_ttf.framework/
FRAMEWORKS = -framework OpenCL -F $(FRW) -rpath $(FRW) -framework SDL2 -framework SDL2_ttf
endif

ifeq ($(OS), Linux)
OPENCL_LIB = -lOpenCL
else
OPENCL_LIB = ""
endif

JANSSON_LIB = -L ./lib/jansson/build/lib/ -ljansson

RT_LIBS = -L $(FT_PRINTF) -lftprintf -L $(LIBFT_DIR) -lft  $(FRAMEWORKS) -lm $(OPENCL_LIB) $(JANSSON_LIB)

all : update $(NAME)

update:
	@git submodule init
	@git submodule update
	{ \
        cd lib/jansson/ ;\
        mkdir build ;\
        cd build ;\
        cmake .. ;\
        make jansson/fast -j 4 ;\
    }

$(NAME) : $(LIBFT) $(D_OBJ) $(OBJ_RT)
	$(CC) $(CFLAGS) $(OBJ_RT) $(RT_LIBS) -o $(NAME)

$(D_OBJ):

$(D_OBJ)%.o: $(D_SRC)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(COMPILE) -c $(INCLUDES) $< -o $@

clean :
	@rm -rf $(D_OBJ)
	@make clean -C $(LIBFT_DIR)

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)

re : fclean $(NAME)

# ============================================================================ #
# 						LIBFT
# ============================================================================ #

LIBFT_DIR =				\
	./libft/			\

LIBFT_INCL = 			\
	./libft/includes/	\

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@make printf -C $(LIBFT_DIR)