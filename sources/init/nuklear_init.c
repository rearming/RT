/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nuklear_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:01:07 by dgreat            #+#    #+#             */
/*   Updated: 2020/02/07 19:23:04 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "nuklear_cross.h"

#define WIN_BORD_MINIM NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE


//void create_widget_test(void* loopArg)//todo: need debug this
//{
//	struct my_nkc_app		*myapp;
//	struct nk_context		*ctx;
//
//	myapp = (struct my_nkc_app*)loopArg;
//	ctx = nkc_get_ctx(myapp->nkcHandle);
//	if (nk_begin(ctx, "test",nk_rect(0, 0,
//			220,220),WIN_BORD_MINIM))
//	{
//			nk_layout_row_static(ctx, 30, 80, 1);
//		if (nk_button_label(ctx, "button"))
//		{
//			/* Button pressed case */
//		}
//		nk_layout_row_dynamic(ctx, 30, 2);
//		if (nk_option_label(ctx, "easy", myapp->op == EASY))
//			myapp->op = EASY;
//		if (nk_option_label(ctx, "hard", myapp->op == HARD))
//			myapp->op = HARD;
//		nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
//		nk_layout_row_push(ctx, 50);
//		nk_label(ctx, "Volume:", NK_TEXT_LEFT);
//		nk_layout_row_push(ctx, 110);
//		nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
//	}
//	nk_layout_row_end(ctx);
//}

void main_loop(void* loop_arg){
	struct my_nkc_app		*myapp;
	struct nk_context		*ctx;
	union nkc_event			event;

	myapp = (struct my_nkc_app*)loop_arg;
	ctx = nkc_get_ctx(myapp->nkcHandle);
	event = nkc_poll_events(myapp->nkcHandle);

	if((event.type == NKC_EWINDOW) && (event.window.param == NKC_EQUIT))
		nkc_stop_main_loop(myapp->nkcHandle);

	create_widget_test(loop_arg);

	nk_end(ctx);
	nkc_render(myapp->nkcHandle, nk_rgb(40,40,40) );
}



t_nk_main				nuklear_cross_init()
{
	struct my_nkc_app myapp;//widget
	struct nkc nkcx; /* Allocate memory for Nuklear+ handle */

	t_nk_main nk;

//	myapp.nkcHandle = &nkcx;

//	/* init some user data */
//	myapp.value = 0.4;
//	myapp.op = HARD;
	myapp = (struct my_nkc_app){.nkcHandle = &nkcx, .value = 0.4, .op = EASY};
	nk = (t_nk_main){.myapp = myapp, .loop_func = main_loop};

	if( nkc_init( nk.myapp.nkcHandle, RT_GUI_NAME, RT_NK_WIDTH,
			RT_NK_HEIGHT,NKC_WIN_NORMAL ) )
		return (nk);
//		nkc_set_main_loop(myapp.nkcHandle, main_loop, (void*)&myapp );
//	else
//	{
//		rt_raise_error();TODO:add error code
//	}

	printf("Value after exit = %f\n", myapp.value);
	nkc_shutdown( myapp.nkcHandle );
}