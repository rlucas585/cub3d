/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/29 19:49:59 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>

int			keypress(int key, t_all *all)
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
		funct(all);
	if (key == KEY_ESC)
		exit(0);
	return (1);
}

int			keyrelease(t_all *all)
{
	all->keytest = 1;
	return (1);
}

int			crosspress(t_all *all)
{
	escape(all);
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
	if (!img[dir])
		exit(ft_error(delete_all(MISSING_TEX, *all), 0));
	all->info->texstrs[dir] = mlx_get_data_addr(img[dir],
			&all->info->texinf->bpp,
			&all->info->texinf->size_line,
			&all->info->texinf->endian);
	if (!all->info->texstrs[dir])
		exit(ft_error(delete_all(MISSING_TEX, *all), 0));
}

void		init_tex(t_all *all)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		all->info->texstrs[i] = NULL;
		i++;
	}
	all->info->texinf = (t_imginf *)malloc(sizeof(t_imginf));
	if (!all->info->texinf)
		exit(ft_error(delete_all(MEM_FAIL, *all), 0));
	one_tex(all, NORTH, &all->info->imgs[NORTH]);
	one_tex(all, EAST, &all->info->imgs[EAST]);
	one_tex(all, SOUTH, &all->info->imgs[SOUTH]);
	one_tex(all, WEST, &all->info->imgs[WEST]);
}

int			main(int argc, char **argv)
{
	t_game		game;
	t_display	xsrv;
	t_all		all;

	game.map = cub_parser(open_file(argc, argv));
	validate_n_s_walls(game.map);
	game.player = find_player(game);
	if (game.player.location[X] == 0)
		exit(ft_error(delete_info(NO_PLAYER, game.map), 0));
	/* print_gameinfo(game); */
	xsrv = establish_connection(game);
	all.xsrv = &xsrv;
	all.info = &game;
	init_tex(&all);
	all.keytest = 0;
	mlx_hook(all.xsrv->w, 2, 0, &keypress, &all);
	mlx_hook(all.xsrv->w, 3, 0, &keyrelease, &all);
	mlx_hook(all.xsrv->w, 17, 0, &crosspress, &all);
	create_image(xsrv, game);
	mlx_loop(xsrv.dpy);
	return (0);
}
