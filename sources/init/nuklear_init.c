///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   nuklear_init.c                                     :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2020/02/07 16:01:07 by dgreat            #+#    #+#             */
///*   Updated: 2020/02/10 21:25:35 by dgreat           ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
#include "rt.h"
#include "nuklear_cross.h"
//
#define WIN_BORD_MINIM NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE
//
//
struct my_nkc_app* create_widget_test(void* loopArg)//todo: need debug this
{
	struct my_nkc_app		*myapp;
	struct nk_context		*ctx;

	myapp = (struct my_nkc_app*)loopArg;
	ctx = nkc_get_ctx(myapp->nkcHandle);

	if (nk_begin(ctx, "Type", nk_rect(50, 50, 220, 220),
				 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
		/* fixed widget pixel width */
		nk_layout_row_static(ctx, 30, 80, 1);
		if (nk_button_label(ctx, "button")) {
			/* event handling */
			printf("Button pressed\n");
		}

		/* fixed widget window ratio width */
		nk_layout_row_dynamic(ctx, 30, 2);
		if (nk_option_label(ctx, "easy", myapp->op == EASY)) myapp->op = EASY;
		if (nk_option_label(ctx, "hard", myapp->op == HARD)) myapp->op = HARD;

		/* custom widget pixel width */
		nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
		{
			nk_layout_row_push(ctx, 50);
			nk_label(ctx, "Volume:", NK_TEXT_LEFT);
			nk_layout_row_push(ctx, 110);
			nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
		}
		nk_layout_row_end(ctx);
	}
	nk_end(ctx);

	if (nk_begin(ctx, "test",nk_rect(0, 0,
			300,220),NK_WINDOW_BORDER|NK_WINDOW_MINIMIZABLE))
	{
		nk_layout_row_static(ctx, 30, 80, 3);
		if (nk_button_label(ctx, "button"))
		{
			/* Button pressed case */
		}
		nk_layout_row_dynamic(ctx, 40, 3);
		if (nk_option_label(ctx, "Simple", myapp->op == SIMPLE))
			myapp->op = SIMPLE;
		if (nk_option_label(ctx, "Metallic", myapp->op == METALLIC))
			myapp->op = METALLIC;
		if (nk_option_label(ctx, "Matte", myapp->op == MATTE))
				myapp->op = MATTE;

		nk_layout_row_begin(ctx, NK_STATIC, 30, 3);
		nk_layout_row_push(ctx, 50);
		nk_label(ctx, "Volume:", NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 110);
		nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
	}
	nk_layout_row_end(ctx);

	return (myapp);
}


void mainLoop(void* loopArg){
	struct my_nkc_app* myapp = (struct my_nkc_app*)loopArg;
	struct nk_context *ctx = nkc_get_ctx(myapp->nkcHandle);
	struct nk_image img;

	union nkc_event e = nkc_poll_events(myapp->nkcHandle);
	if( (e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) )
	{
		nkc_stop_main_loop(myapp->nkcHandle);
	}
	create_widget_test(loopArg);
	/* End Nuklear GUI */
	img = nkc_load_image_memory(myapp->nkcHandle, g_img_data, sizeof(g_img_data));
	nk_layout_space_push(ctx, nk_rect(0, 0, WIN_WIDTH, WIN_HEIGHT));
	nk_image(ctx, img);

//	nk_layout_row_static(ctx, 40, 40, 4);
//	if (nk_menu_begin_image(ctx, "Music", media->play, nk_vec2(110,120)))
//	{
//		/* settings */
//		nk_layout_row_dynamic(ctx, 25, 1);
//		nk_menu_item_image_label(ctx, media->play, "Play", NK_TEXT_RIGHT);
//		nk_menu_item_image_label(ctx, media->stop, "Stop", NK_TEXT_RIGHT);
//		nk_menu_item_image_label(ctx, media->pause, "Pause", NK_TEXT_RIGHT);
//		nk_menu_item_image_label(ctx, media->next, "Next", NK_TEXT_RIGHT);
//		nk_menu_item_image_label(ctx, media->prev, "Prev", NK_TEXT_RIGHT);
//		nk_menu_end(ctx);
//	}

	nk_end(ctx);
	nkc_render(myapp->nkcHandle, nk_rgb(40,40,40) );
}

t_nk_main nuklear_cross_init()
{
	struct my_nkc_app myapp;//widget
	struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
		t_nk_main nk;

	myapp = (struct my_nkc_app){.nkcHandle = &nkcx, .value = 0.4, .op = MATTE};
		nk = (t_nk_main){.myapp = myapp, .loop_func = mainLoop};
	if( nkc_init( myapp.nkcHandle, RT_GUI_NAME, WIN_WIDTH, WIN_HEIGHT,
			NKC_WIN_NORMAL ) )
	{
		printf("Successfull init. Starting 'infinite' main loop...\n");
		nkc_set_main_loop(myapp.nkcHandle, mainLoop, (void*)&myapp );
	}
	else
	{
		printf("something wrong with init of nkc");
//		rt_raise_error();TODO:add error code
	}
	printf("Value after exit = %f\n", myapp.value);
	nkc_shutdown( myapp.nkcHandle );
	return nk;
}