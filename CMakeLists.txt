cmake_minimum_required(VERSION 3.14)
project(RT C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O2)
endif()

# <----RTv1 compile---->

set(debug_sources
        sources/debug/rt_debug_print_utils.c
        sources/debug/rt_print_obj_file.c
        sources/debug/rt_debug_print_parsed_meshes.c
        sources/debug/rt_print_object.c
        sources/debug/rt_kd_tree_print.c
        )

set(runtime_debug_sources
        sources/debug/runtime_debug/opencl_debug.c
        sources/debug/runtime_debug/rt_debug_info.c
        )

set(profiling_sources
        sources/debug/profiling/rt_profiling.c
        )

set(math_utils_sources
        sources/math_utils/rt_math_utils.c
        sources/math_utils/rt_rotation_utils.c
        sources/math_utils/rt_cl_float3_utils.c sources/math_utils/rt_vector_math.c)

set(OpenCL_utils_sources
        sources/OpenCL_utils/rt_opencl_init.c
        sources/OpenCL_utils/rt_opencl_files_parser.c
        sources/OpenCL_utils/rt_opencl_render.c
        sources/OpenCL_utils/rt_opencl_memory_management.c
        sources/OpenCL_utils/rt_opencl_utils.c
        sources/OpenCL_utils/rt_opencl_prepare_memory.c
        sources/OpenCL_utils/rt_init_renderer.c
        )

set(parsing_sources
        sources/rt_parsing/rt_parse_scene.c
        sources/rt_parsing/json_parser/rt_parse_textures.c
        sources/rt_parsing/json_parser/rt_parse_variable.c
        sources/rt_parsing/json_parser/rt_parse_object.c
        sources/rt_parsing/json_parser/rt_parse_string.c
        sources/rt_parsing/json_parser/rt_json_utils.c
        sources/rt_parsing/json_parser/rt_type_of_parametr.c
        sources/rt_parsing/json_parser/rt_add_to_scene.c
        sources/rt_parsing/json_parser/rt_parse_array.c
        sources/rt_parsing/rt_correct_scene.c
        sources/rt_parsing/print_scene_params_delete_if_everything_works.c
        )

set(event_handling_sources
        sources/rt_event_handling/rt_event_utils.c
        sources/rt_event_handling/rt_settings_change.c
        sources/rt_event_handling/rt_settings_info.c
        sources/rt_event_handling/rt_key_event_handing.c
        sources/rt_event_handling/rt_mouse_event_handling.c
        sources/rt_event_handling/rt_camera_moves.c
        sources/rt_event_handling/rt_event_handling.c
        )

set(utils_sources
        sources/utils/rt_safe_malloc.c
        sources/utils/rt_raise_error.c
        sources/utils/rt_exit_clean.c
        sources/utils/rt_color_utils.c
        )

set(SDL_utils_sources
        sources/SDL_utils/sdl_init.c
        )

set(obj_loading_sources
        sources/obj_loading/rt_correct_materials.c
        sources/obj_loading/rt_load_obj_files.c
        sources/obj_loading/rt_load_obj_utils.c
        sources/obj_loading/rt_load_obj_meshes.c
        sources/obj_loading/rt_load_obj_materials.c
        )

set(init_sources
        sources/init/rt_init.c
        sources/init/rt_init_render_params.c
        sources/init/rt_load_textures.c
        sources/init/rt_load_textures_utils.c
        )

set(render_sources
        sources/render/rt_loop.c
        sources/render/render.c
        sources/render/rt_update_params.c
        )

set(kd_tree_sources
        sources/kd_tree/rt_kd_get_aabb.c
        sources/kd_tree/rt_kd_tree_build.c
        sources/test/kd_3d_test/rt_kd_tree_traversal.c
        sources/kd_tree/rt_kd_tree_to_array.c
        sources/kd_tree/rt_kd_tree_utils.c
        sources/kd_tree/rt_kd_tree_get.c
        sources/kd_tree/rt_kd_pack_object_indices.c)

set(gui_sources
        sources/gui/gui_init.c
        sources/gui/buttons.c
        sources/gui/gui_utils/color_utils.c
        sources/gui/button_callback.c)

set(sources
        ${debug_sources}
        ${runtime_debug_sources}
        ${math_utils_sources}
        ${OpenCL_utils_sources}
        ${parsing_sources}
        ${event_handling_sources}
        ${utils_sources}
        ${SDL_utils_sources}
        ${obj_loading_sources}
        ${init_sources}
        ${render_sources}
        ${kd_tree_sources}
        ${profiling_sources}
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
            lib/SDL2_libs/SDL2.framework/Headers
            lib/SDL2_libs/SDL2_ttf.framework/Headers)
    set(graphic_libs_dirs
            lib/SDL2_libs/)
    set(graphic_libs_link_names
            "-F ${PROJECT_SOURCE_DIR}/lib/SDL2_libs -framework SDL2 -framework SDL2_ttf"
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
        lib/jansson/build/lib/
)

add_executable(RT
        sources/main.c
        ${sources})

target_link_libraries(RT
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        "jansson"
        )

# <----TESTING----> #

# <---- kd_tree_test ----> #

add_executable(kd_tree_test
        ${SDL_utils_sources}
        ${math_utils_sources}
        ${utils_sources}
        ${kd_tree_sources}
        ${obj_loading_sources}
        sources/debug/rt_debug_print_parsed_meshes.c
        sources/debug/rt_debug_print_utils.c
        sources/debug/rt_kd_tree_print.c
        sources/test/kd_3d_test/kd_tree_main.c
        sources/test/kd_3d_test/kd_tree_export.c
        sources/test/kd_3d_test/test_kd_traversal.c)

target_include_directories(kd_tree_test PRIVATE
        sources/test)

target_link_libraries(kd_tree_test
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        )

# <---- generic_test ----> #

add_executable(generic_test
        ${sources}
        sources/test/test_asserts.c
        sources/test/generic_test/generic_test_main.c
        )

target_include_directories(generic_test PRIVATE
        sources/test)

target_link_libraries(generic_test
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        "jansson"
        )

# <---- obj_loading_test ----> #

add_executable(obj_loading_test
        ${debug_sources}
        ${OpenCL_sources}
        ${SDL_utils_sources}
        ${math_utils_sources}
        ${utils_sources}
        ${obj_loading_sources}
        sources/test/test_asserts.c
        sources/test/obj_loading_test/obj_loading_test_main.c)

target_include_directories(obj_loading_test PRIVATE
        sources/test)

target_link_libraries(obj_loading_test
        "ftprintf"
        "ft"
        ${graphic_libs_link_names}
        "m"
        "jansson"
        )