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
    ```
    int i;
   
    void parse(int i, int t, char *m, t_pf *f);
    ```
    **Правильно:**
    ```
    int scene_object_iter;
   
    void parse_scene_object(
        int object_number,
        t_obj_types object_type,
        char *parse_algo_modifier,
        t_parse_function_ptr *parse_func);
    ```
    **Тоже правильно** (сокращения, не вредящие читабельности):
    ```
    int scene_obj_i;
   
    void parse_scene_obj(
           int obj_num,
           t_obj_types obj_type,
           char *parse_modifier,
           t_parse_function_ptr *parse_func);
    ```

2. Названия функций общего назначение (напр., get_arguments/parse/get_object/ и т.п.) префиксуем rt_
    ```
    int     rt_parse_file(char *filename);
    ```                               
3. Название возвращаемых параметров функций префиксуется out_
    ```
   void     some_func(char **out_some_string);
    ```
   
## Code style
1. Длинные списки параметров переносим вот так:

    (по параметру на строку)
    ```
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
    ```
   if (some_condition)
   {
        if (another_condition)
        {
            do_some_work();
        }
   }
    ```
   **Неправильно:**
    ```
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
    ```
    int     get_param(char *filename, t_param **out_param)
    {
        ...
   
        if (some_condition)
            return (0);
        return (1);
    }
    ```
    **Правильно:**
    ```
    t_bool     get_param(char *filename, t_param **out_param)
    {
        ...
   
        if (some_contion)
            return (FALSE);
        return (TRUE);
    }
    ```
2. Обработка ошибок:
    ```
    if (some_error)
        rt_raise_error(ERR_SOME_ERROR);
    ```
   Если кода этой ошибки еще нет, дефайним ее в ```rt_errors.h```.

3. Вместо ```malloc()``` используем ```rt_safe_malloc()```:

   **Неправильно:**
   ```
   some_int_array = (int*)malloc(sizeof(int) * len));
   if (!some_int_array)
        rt_raise_error(ERR_MALLOC);
   ```
   **Правильно:**
   ```
   some_int_array = rt_safe_malloc(sizeof(int) * len));
   ```
   * **Ни к чему не приводим возвращаемое значение.**
   
   * **Память грантированно выделится, либо rt_safe_malloc сам кинет ERR_MALLOC и выйдет из программы, то есть проверять возврат на NULL не нужно**
   
4. Используемые типы:

    Для **всего, что связанно с рендером** мы используем typedef'ы OpenCL, т.е.:
    ```
    cl_int      my_int;
    cl_float    my_float;
    cl_float3   my_vector;
    ```
    И так далее.
    
5. Структуры:

   Каждый ```struct```, который мы используем на видеокарте (в кернеле), мы определяем так:
   ```
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
   ```
   typedef struct	s_float_struct
  	{
  	# ifndef FT_OPENCL___
  		cl_float3	    my_float3;
  	# else
  		float3		    my_float3;
  	# endif
  
  	}
   ```
   
## Настройки для Clion
1. Включение скрипта для авто-генерации прототипов kernel-функций (из .cl-файлов):

    **CMake Application** -> **Before launch** -> **Run External tool**
    ![Img alt](https://trello-attachments.s3.amazonaws.com/5e09e87ddad9255a33242a41/1146x748/b8683434b3011a1810691c223425a5e6/clion_external_tool_1.png)
    
    **Cо следующими параметрами:**
    ![Img alt](https://trello-attachments.s3.amazonaws.com/5dcd48f098640f8ffcb3f1fd/5e09e87ddad9255a33242a41/e26978c8751a6e268d07fb48fedf056f/clion_external_tool_2.png)