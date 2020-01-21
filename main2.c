/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/21 16:45:02 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

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

void		test_img(t_display xsrv, t_game info)
{
	unsigned int	clr;
	unsigned int	test;
	int				x;
	int				y;

	test = 0;
	clr = mlx_get_color_value(xsrv.dpy, rgb(255, 30, 30));
	ft_printf("rgb(255, 30, 30) clr = %u\n", mlx_get_color_value(xsrv.dpy, rgb(255, 30, 30)));
	ft_printf("address = %p\n", xsrv.imga);
	ft_printf("value of clr: %u\n", clr);
	ft_printf("value of test: %u\n", test);
	ft_memcpy(&test, &clr, 4);
	ft_printf("value of test: %u\n", test);
	ft_printf("length of pixel in bits: %d\n", xsrv.img->bpp);

	x = 0;
	y = 0;
	ft_printf("values: %u\n", *xsrv.imga);
	while (x < info.map.res[0])
	{
		while (y < info.map.res[1])
		{
			/* ft_bzero(xsrv.imga + xsrv.img->size_line * x + xsrv.img->bpp * y, xsrv.img->bpp / 4); */
			ft_memcpy(xsrv.imga + xsrv.img->size_line * x +
					(xsrv.img->bpp / 8) * y, &clr, xsrv.img->bpp / 8);
			y++;
		}
		y = 0;
		x++;
	}
	ft_printf("values: %u\n", *xsrv.imga);

	/* ft_memcpy(xsrv.imga, &clr, xsrv.img->bpp); */
	/* ft_memcpy(xsrv.imga + xsrv.img->bpp, &clr, xsrv.img->bpp); */
	mlx_put_image_to_window(xsrv.dpy, xsrv.w, xsrv.img, 0, 0);
}

t_display	establish_connection(t_game info)
{
	t_display	xsrv;
	int			a;
	int			b;
	int			c;

	xsrv.dpy = mlx_init();
	if (xsrv.dpy == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.w = mlx_new_window(xsrv.dpy, info.map.res[0], info.map.res[1], "cub3");
	if (xsrv.w == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	mlx_clear_window(xsrv.dpy, xsrv.w);
	/* ray(info, xsrv); */
	xsrv.img = (t_img *)mlx_new_image(xsrv.dpy, info.map.res[0], info.map.res[1]);
	if (!xsrv.img)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	/* mlx_get_data_addr(xsrv.img, &xsrv.img->bpp, &xsrv.img->size_line, &xsrv.img->endian); */
	xsrv.imga = mlx_get_data_addr(xsrv.img, &a, &b, &c);
	xsrv.img->bpp = a;
	xsrv.img->size_line = b;
	xsrv.img->endian = c;
	xsrv.imga = (char *)malloc(info.map.res[0] * info.map.res[1] * xsrv.img->bpp);
	test_img(xsrv, info);
	return (xsrv);
}

int			main(int argc, char **argv)
{
	t_game		game;
	t_display	xsrv;

	game.map = cub_parser(open_file(argc, argv));
	validate_n_s_walls(game.map);
	game.player = find_player(game);
	print_gameinfo(game);
	xsrv = establish_connection(game);
	mlx_loop(xsrv.dpy);
	mlx_destroy_window(xsrv.dpy, xsrv.w);
	return (0);
}
