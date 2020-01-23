/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/23 19:28:24 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

int			action(int key, t_all *all)
{
	t_act					funct;
	static const t_act		actiontable[128] = {
		[KEY_A] = &move_left,
		[KEY_S] = &move_back,
		[KEY_D] = &move_right,
		[KEY_W] = &move_forward,
		[KEY_LEFT] = &turn_left,
		[KEY_RIGHT] = &turn_right,
		[KEY_ESC] = &escape,
	};

	funct = actiontable[key];
	if (funct)
		funct(all->info, all->xsrv);
	if (key == KEY_ESC)
		exit(0);
	return (1);
}

int			crosspress(t_all *all)
{
	escape(all->info, all->xsrv);
	exit(0);
}

void		one_tex(t_all *all, int dir, void **img)
{
	int			x;
	int			y;

	x = 128;
	y = 128;
	img[dir] = mlx_png_file_to_image(all->xsrv->dpy,
			all->info->map.textures[dir], &x, &y);
	all->info->tex[dir] = mlx_get_data_addr(img[dir],
			&all->info->texinf->bpp,
			&all->info->texinf->size_line,
			&all->info->texinf->endian);
}

void		init_tex(t_all *all)
{
	void		*img[5];
	/* int			x; */
	/* int			y; */
	/* unsigned int color; */

	all->info->tex = (char **)malloc(sizeof(char *) * 6);
	all->info->texinf = (t_imginf *)malloc(sizeof(t_imginf));
	one_tex(all, NORTH, img);
	one_tex(all, EAST, img);
	one_tex(all, WEST, img);
	one_tex(all, SOUTH, img);
	/* all->xsrv->img = mlx_new_image(all->xsrv->dpy, all->info->map.res[0], all->info->map.res[1]); */
	/* all->xsrv->imga = mlx_get_data_addr(all->xsrv->img, &all->xsrv->imginf->bpp, */
	/* 		&all->xsrv->imginf->size_line, &all->xsrv->imginf->endian); */
	/* x = 0; */
	/* y = 0; */
	/* color = RED; */
	/* while (x < 128) */
	/* { */
	/* 	ft_memcpy(&color, all->info->tex[NORTH] + 4 * x + all->info->texinf->size_line * y, 4); */
	/* 	img_put_pixel(*all->xsrv, x, y, color); */
	/* 	x++; */
	/* 	if (x == 128 && y < 127) */
	/* 	{ */
	/* 		x = 0; */
	/* 		y++; */
	/* 	} */
	/* } */
	/* mlx_put_image_to_window(all->xsrv->dpy, all->xsrv->w, all->xsrv->img, 0, 0); */
	/* mlx_loop(all->xsrv->dpy); */
	/* mlx_put_image_to_window(all->xsrv->dpy, all->xsrv->w, img[NORTH], 0, 0); */
	/* mlx_put_image_to_window(all->xsrv->dpy, all->xsrv->w, img[EAST], 128, 0); */
	/* mlx_put_image_to_window(all->xsrv->dpy, all->xsrv->w, img[WEST], 256, 0); */
	/* mlx_put_image_to_window(all->xsrv->dpy, all->xsrv->w, img[SOUTH], 384, 0); */
	/* mlx_loop(all->xsrv->dpy); */
}

int			main(int argc, char **argv)
{
	t_game		game;
	t_display	xsrv;
	t_all		all;

	game.map = cub_parser(open_file(argc, argv));
	validate_n_s_walls(game.map);
	game.player = find_player(game);
	/* print_gameinfo(game); */
	xsrv = establish_connection(game);
	all.xsrv = &xsrv;
	all.info = &game;
	init_tex(&all);
	mlx_hook(all.xsrv->w, 2, 0, &action, &all);
	mlx_hook(all.xsrv->w, 17, 0, &crosspress, &all);
	create_image(xsrv, game);
	mlx_loop(xsrv.dpy);
	return (0);
}
