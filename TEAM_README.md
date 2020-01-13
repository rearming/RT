# RT

## Начало работы
1. Запускаем ```./compile.sh```
2. Читаем этот README.

## Работа с Git
1. Каждая задача разрабатывается в отдельной ветке (назавание ветки == название задачи)
2. Для работы с задачей делаем git checkout -b "some_task" с мастера
3. Сделав задачу, сливаем master в свою ветку, тестим, что все работает и сливаем все это **с коммитом** обратно в мастер.
4. Для работы с гитом использовать Clion или SmartGit (удобен при разрешении конфликтов слияния)
5. Одна задача - одна карточка в Trello. Если задача большая, от своей ветки с этой задачей создаем столько, сколько нужно дополнительных веток. **Не создаем ветки с подзадачами от мастера!**
6. Если в процессе разработки появилась новая задача, которой нет в Trello, добавляем ее туда, а потом создаем бранч.

## Нейминг (названия функций и переменных)

1. Все названия должны быть **читабельными**. Ничего страшного, если они получатся длинными, особенно в .cl файлах

    **Неправильно:**
    ```c
    int i;
   
    void parse(int i, int t, char *m, t_pf *f);
    ```
    **Правильно:**
    ```c
    int scene_object_iter;
   
    void parse_scene_object(
        int object_number,
        t_obj_types object_type,
        char *parse_algo_modifier,
        t_parse_function_ptr *parse_func);
    ```
    **Тоже правильно** (сокращения, не вредящие читабельности):
    ```c
    int scene_obj_i;
   
    void parse_scene_obj(
           int obj_num,
           t_obj_types obj_type,
           char *parse_modifier,
           t_parse_function_ptr *parse_func);
    ```

2. Названия функций общего назначение (напр., get_arguments/parse/get_object/ и т.п.) префиксуем rt_
    ```c
    int     rt_parse_file(char *filename);
    ```                               
3. Название возвращаемых параметров функций префиксуется out_
    ```c
   void     some_func(char **out_some_string);
    ```
   
## Code style
1. Длинные списки параметров переносим вот так:

    (по параметру на строку)
    ```c
    void   some_func_with_long_param_list(
            int param_1,
            int param_2,
            int param_3,
            int param_4);
    ```
   **Настройки для Clion:**
   ![Img alt](https://trello-attachments.s3.amazonaws.com/5e09e87ddad9255a33242a41/770x478/722d7104bb92b1b407eb9d3f7a582e3c/clion_wrapping_settings.png)
2. В .cl файлах **не используем** K&R стиль скобок:

    **Правильно:**
    ```c
   if (some_condition)
   {
        if (another_condition)
        {
            do_some_work();
        }
   }
    ```
   **Неправильно:**
    ```c
   if (some_condition) {
        if (another_condition) {
            do_some_work();
        }
   }
    ```         
   (На таких небольших примерах выглядит еще нормально, но когда функции становятся больше, это превращается в ад.)
   
   **Clion-> Preferences -> Editor -> Code Style -> C/C++ -> Wrapping and braces -> Braces placement -> Next line**

## Code agreement
1. Там, где под ```int``` мы имеем в виду булевы значения, используем ```t_bool``` и ```TRUE```/```FALSE``` дефайны. 

    Допустим, есть функция, которая возвращает 1 в случае ошибки и 0 в случае успешного получаение param:
    
    **Неправильно:**
    ```c
    int     get_param(char *filename, t_param **out_param)
    {
        ...
   
        if (some_condition)
            return (0);
        return (1);
    }
    ```
    **Правильно:**
    ```c
    t_bool     get_param(char *filename, t_param **out_param)
    {
        ...
   
        if (some_contion)
            return (FALSE);
        return (TRUE);
    }
    ```
2. Обработка ошибок:
   ```c
   if (some_error)
       rt_raise_error(ERR_SOME_ERROR);
   ```
   или
   ```c
   some_error ? rt_raise_error(ERR_SOME_ERROR) : 0;
   ```
   Если кода этой ошибки еще нет, дефайним ее в ```rt_errors.h```.\
   
   В случае ошибок связанных с OpenCL (теми, что вернули их функции), используем
   ```c
   rt_opencl_handle_error(ERR_OPENCL_SOME_ERROR, err);
   ```
   Где ```err``` это код ошибки, которую вернул OpenCL.

3. Вместо ```malloc()``` используем ```rt_safe_malloc()```:

   **Неправильно:**
   ```c
   some_int_array = (int*)malloc(sizeof(int) * len));
   if (!some_int_array)
        rt_raise_error(ERR_MALLOC);
   ```
   **Правильно:**
   ```c
   some_int_array = rt_safe_malloc(sizeof(int) * len));
   ```
   * **Ни к чему не приводим возвращаемое значение.**
   
   * **Память грантированно выделится, либо rt_safe_malloc сам кинет ERR_MALLOC и выйдет из программы, то есть проверять возврат на NULL не нужно**
   
4. Используемые типы:

    Для **всего, что связанно с рендером** мы используем typedef'ы OpenCL, т.е.:
    ```c
    cl_int      my_int;
    cl_float    my_float;
    cl_float3   my_vector;
    ```
    И так далее.
    
5. Структуры:

   Каждый ```struct```, который мы используем на видеокарте (в кернеле), мы определяем так:
   ```c
   typedef struct s_some_struct
   {
   # ifndef FT_OPENCL___
   	cl_some_type	    my_host_field_1;
   	cl_another_type     my_host_field_2;
   # else
   
   	builtin_cl_type     my_kernel_filed_1;
   	builtin_cl_type     my_kernel_filed_2;
   # endif
   
   }
   ```
   Где ```builtin_cl_type``` нужно посмотреть в документации
   (например, ```cl_float3``` на хосте (процессоре) становится ```float3``` на кернеле).
   
   Например:
   ```c
   typedef struct	s_float_struct
  	{
  	# ifndef FT_OPENCL___
  		cl_float3	    my_float3;
  	# else
  		float3		    my_float3;
  	# endif
  
  	}
   ```
6. Передача данных в kernel:\
   Пойнтеры в структурах не копируются на девайс. Именно поэтому мы передаем
   ```c
   typedef struct           s_scene
   {
        t_camera        camera;
        cl_int          obj_nbr;
        cl_int          lights_nbr;
        t_object        *objects;
        t_light         *lights;
   }                        t_scene;
   ```
   И отдельно массивы объектов и источников света:
   ```c
   t_object         *objects;
   t_light          *lights;
   ```
   Мы передаем данные на девайс с помощью
   ```c
   void		rt_opencl_prepare_memory(t_rt *rt);
   ```
   + Обновляем кол-во параметов ```g_opencl.opencl_memobj_number```
   + Формируем из нашей структуры ```t_opencl_mem_obj```, со следующими полями:
        + Структура
        + Размер структуры (если массив, то ```sizeof(my_struct) * arr_len```)
        + Необходимый флаг для OpenCL (скорее всего подойдет ```RT_DEFAULT_MEM_FLAG```)
        + Нужно ли каждый раз копировать память, или использовать старую.\
        (Например, в сцене такие параметры камеры как позиция и поворот каждый раз меняются,
        поэтому её мы копируем каждый раз,
        тогда как объекты пока что неизменяемы и каждый раз копировать их не имеет смысла)
   ```c
   void		rt_opencl_prepare_memory(t_rt *rt)
   {
   	g_opencl.opencl_memobj_number = 3;
   	rt_opencl_move_host_mem_to_kernel(g_opencl.opencl_memobj_number,
   		(t_opencl_mem_obj){&rt->scene,
   			sizeof(t_scene), RT_DEFAULT_MEM_FLAG, TRUE},
   		(t_opencl_mem_obj){rt->scene.objects,
   			sizeof(t_object) * rt->scene.obj_nbr, RT_DEFAULT_MEM_FLAG, FALSE},
   		(t_opencl_mem_obj){rt->scene.lights,
   			sizeof(t_light) * rt->scene.lights_nbr, RT_DEFAULT_MEM_FLAG, FALSE}
   			);
   }
   ```
   
7. Добавление новых объектов:\
    Каждый объект на сцене представляется в структуре ```t_object``` и хранятся в массиве ```t_object *objects;```.\
    Когда для нового объекта нужно добавить какое-либо поле, добавляем его в эту структуру.
   
## Настройки для Clion
1. Включение opencl_init.py скрипта:\
    **CMake Application** -> **Before launch** -> **Run External tool**
    ![Img alt](https://trello-attachments.s3.amazonaws.com/5e09e87ddad9255a33242a41/1146x748/b8683434b3011a1810691c223425a5e6/clion_external_tool_1.png)
    
    **Cо следующими параметрами:**
    ![Img alt](https://trello-attachments.s3.amazonaws.com/5dcd48f098640f8ffcb3f1fd/5e09e87ddad9255a33242a41/6e46cf2f77ed3046323c053beeb5b0f3/clion_external_tool_2.png)

     **Текущий функционал:**
     + генерация и отслеживание изменений прототипов kernel-функций (из .cl файлов):
     + дополнение opencl_files_parser.c при добавлении новых .cl файлов\
     (число файлов ```concat_opencl_kernel_code(6,``` тоже изменяется автоматически)
     
 2. Создание Clion'ом Header Guards по норме:
    ```c
    #ifndef HEADER_NAME_H
    # define HEADER_NAME_H
    ```
    **Preferences->Editor->Code Style->Naming Convention->Header Guard Style**\
    Установить:\
    **"${FILE_NAME}_${EXT}"**
   
