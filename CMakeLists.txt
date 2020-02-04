cmake_minimum_required(VERSION 3.14)
project(RT C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-Werror -O2)
endif()

# <----RTv1 compile---->

set(sources
        sources/init/rt_init.c
        sources/utils/rt_safe_malloc.c
        sources/utils/rt_raise_error.c
        sources/OpenCL_utils/rt_opencl_init.c
        sources/OpenCL_utils/rt_opencl_files_parser.c
        sources/debug/opencl_debug.c
        sources/utils/rt_exit_clean.c
        sources/SDL_utils/sdl_init.c
        sources/render/render.c
        sources/OpenCL_utils/rt_opencl_render.c
        sources/OpenCL_utils/rt_opencl_memory_management.c
        sources/rt_parsing/rt_parse_scene.c
        sources/rt_parsing/hardcoded_scene.c
        sources/OpenCL_utils/rt_opencl_utils.c
        sources/utils/rt_loop.c
        sources/rt_event_handling/rt_camera_moves.c
        sources/rt_event_handling/rt_event_handling.c
        sources/math_utils/rt_rotation_utils.c
        sources/math_utils/rt_cl_float3_utils.c
        sources/debug/rt_debug_info.c
        includes/rt_debug.h
        sources/debug/rt_debug_print_utils.c
        sources/rt_parsing/rt_correct_scene.c
        sources/utils/rt_color_utils.c
        sources/debug/rt_profiling.c
        sources/rt_parsing/rt_load_obj_files.c
        sources/debug/rt_print_obj_file.c
        sources/debug/rt_debug_print_parsed_meshes.c
        sources/rt_parsing/rt_load_obj_utils.c
        sources/rt_parsing/rt_load_obj_meshes.c
        sources/rt_parsing/rt_load_obj_materials.c
        sources/rt_parsing/rt_correct_materials.c
        sources/math_utils/rt_math_utils.c
        sources/rt_event_handling/rt_event_utils.c
        sources/OpenCL_utils/rt_init_renderer.c
        sources/rt_event_handling/rt_settings_change.c
        sources/rt_event_handling/rt_settings_info.c
        sources/rt_event_handling/rt_key_event_handing.c
        sources/rt_event_handling/rt_mouse_event_handling.c
        sources/init/rt_init_render_params.c
        sources/OpenCL_utils/rt_opencl_prepare_memory.c
        sources/render/rt_update_params.c
        sources/init/rt_load_textures.c
        sources/init/rt_load_textures_utils.c
        )

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(OPENCL REQUIRED OpenCL)

    set(graphic_libs_include_dirs
            ${SDL2_INCLUDE_DIRS})
    set(graphic_libs_dirs
            ${SDL2_LIBRARY_DIRS})
    set(graphic_libs_link_names
            ${SDL2_LIBRARIES}
            ${OPENCL_LIBRARIES})
else()
    set(graphic_libs_include_dirs
            SDL2_libs/SDL2.framework/Headers)
    set(graphic_libs_dirs
            SDL2_libs/)
    set(graphic_libs_link_names
            "-F ${PROJECT_SOURCE_DIR}/SDL2_libs -framework SDL2"
            "-framework OpenCL")
endif()

message("graphic_libs_include_dirs: " ${graphic_libs_include_dirs})
message("graphic_libs_dirs: " ${graphic_libs_dirs})
message("graphic_libs_link_names: " ${graphic_libs_link_names})

include_directories(
        libft/includes
        includes
        ${graphic_libs_include_dirs}
        )

link_directories(
        libft
        libft/ft_printf
        ${graphic_libs_dirs}
)

add_executable(RT
        sources/main.c
        ${sources}
)

target_link_libraries(RT
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        )

# <----TESTING----> #

add_executable(test
        ${sources}
        sources/test/test_main.c
        sources/test/test_utils.c
        sources/test/test_opencl.c
        sources/test/test_lerp.c)

target_link_libraries(test
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        )
