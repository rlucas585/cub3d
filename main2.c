/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 17:41:42 by rlucas        ########   odam.nl         */
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
	mlx_hook(all.xsrv->w, 2, 0, &action, &all);
	create_image(xsrv, game);
	mlx_loop(xsrv.dpy);
	mlx_destroy_window(xsrv.dpy, xsrv.w);
	return (0);
}
