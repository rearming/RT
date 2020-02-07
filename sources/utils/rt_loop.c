#include "rt.h"
#include "../debug/rt_debug_utils.h"
#include "nuklear_cross.h"

#define WIN_BORD_MINIM NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE

void create_widget_test(void* loopArg)//todo: need debug this
{
	struct my_nkc_app		*myapp;
	struct nk_context		*ctx;

	myapp = (struct my_nkc_app*)loopArg;
	ctx = nkc_get_ctx(myapp->nkcHandle);
	if (nk_begin(ctx, "test",nk_rect(0, 0,
									 220,220),WIN_BORD_MINIM))
	{
		nk_layout_row_static(ctx, 30, 80, 1);
		if (nk_button_label(ctx, "button"))
		{
			/* Button pressed case */
		}
		nk_layout_row_dynamic(ctx, 30, 2);
		if (nk_option_label(ctx, "easy", myapp->op == EASY))
			myapp->op = EASY;
		if (nk_option_label(ctx, "hard", myapp->op == HARD))
			myapp->op = HARD;
		nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
		nk_layout_row_push(ctx, 50);
		nk_label(ctx, "Volume:", NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 110);
		nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
	}
	nk_layout_row_end(ctx);
}

//void main_loop(void* loop_arg){
//	struct my_nkc_app		*myapp;
//	struct nk_context		*ctx;
//	union nkc_event			event;
//
//	myapp = (struct my_nkc_app*)loop_arg;
//	ctx = nkc_get_ctx(myapp->nkcHandle);
//	event = nkc_poll_events(myapp->nkcHandle);
//
//	if((event.type == NKC_EWINDOW) && (event.window.param == NKC_EQUIT))
//		nkc_stop_main_loop(myapp->nkcHandle);
//
//	create_widget_test(loop_arg);
//
//	nk_end(ctx);
//	nkc_render(myapp->nkcHandle, nk_rgb(40,40,40) );
//}

t_nk_main		nk_render()
{
	t_nk_main		nk;

	nk = nuklear_cross_init();

	create_widget_test(&(nk.myapp));
	nk_end(nkc_get_ctx(&(nk.myapp.nkcHandle)));
	nkc_render(&(nk.myapp.nkcHandle), nk_rgb(40,40,40) );
	return (nk);
}

void		rt_loop(t_rt *rt)
{
	union nkc_event			nk_event;
	SDL_Event		event;
	t_nk_main		nk;


	SDL_SetRelativeMouseMode(SDL_TRUE);
	bool flag = false;

	while (21)
	{
		while (SDL_PollEvent(&event))
//		)
		{
			handle_event(&event, rt);
//			nk_event = nkc_poll_events(nk.myapp.nkcHandle);
		}
		rt_render(rt, rt_opencl_render);
//		nk_render();
		if (flag == true)
		{
			rt_pathtrace_profile(rt, 1000);
			flag = false;
		}
		if (event.type == SDL_QUIT)
//		|| (nk_event.type == NKC_EWINDOW) && (nk_event.window.param == NKC_EQUIT))
			break ;
	}
}

