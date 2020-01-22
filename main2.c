/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 14:35:22 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>
#include <string.h>

double		dir_table(int c)
{
	static int	dir_array[128] = {
		['N'] = 0,
		['E'] = 90,
		['S'] = 180,
		['W'] = 270,
	};

	return (dir_array[c]);
}

t_player	make_player(int x, int y, int c)
{
	t_player	player;

	player.location[X] = x;
	player.location[Y] = y;
	player.dir = dir_table(c);
	return (player);
}

t_player	find_player(t_game game)
{
	int			x;
	int			y;
	t_player	player;
	char		**map;

	x = 1;
	y = 1;
	map = game.map.coords;
	player.location[X] = 0;
	while (x < (int)ft_strlen(map[0]) - 1)
	{
		while (y < (int)ft_arrlen(map) - 1)
		{
			if (ft_strchr("NESW", map[y][x]))
			{
				if (player.location[Y] != 0)
					exit(ft_error(delete_info(DUP_PLAYERS, game.map), 0));
				player = make_player(x, y, map[y][x]);
			}
			y++;
		}
		x++;
		y = 1;
	}
	return (player);
}

t_display	establish_connection(t_game info)
{
	t_display	xsrv;

	xsrv.dpy = mlx_init();
	if (xsrv.dpy == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.w = mlx_new_window(xsrv.dpy, info.map.res[0], info.map.res[1], "cub3d");
	if (xsrv.w == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.imginf = (t_imginf *)malloc(sizeof(t_imginf));
	if (xsrv.imginf == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	mlx_clear_window(xsrv.dpy, xsrv.w);
	xsrv.img = mlx_new_image(xsrv.dpy, info.map.res[0], info.map.res[1]);
	if (!xsrv.img)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.imga = mlx_get_data_addr(xsrv.img, &xsrv.imginf->bpp,
			&xsrv.imginf->size_line, &xsrv.imginf->endian);
	return (xsrv);
}

int			main(int argc, char **argv)
{
	t_game		game;
	t_display	xsrv;

	game.map = cub_parser(open_file(argc, argv));
	validate_n_s_walls(game.map);
	game.player = find_player(game);
	/* print_gameinfo(game); */
	xsrv = establish_connection(game);
	create_image(xsrv, game);
	mlx_loop(xsrv.dpy);
	mlx_destroy_window(xsrv.dpy, xsrv.w);
	return (0);
}
