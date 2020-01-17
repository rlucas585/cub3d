/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 18:15:14 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <fcntl.h>

int			dir_table(int c)
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
	ft_printf("c = %d\n", c);
	return (player);
}

t_player	find_player(char **map)
{
	int			x;
	int			y;
	t_player	player;

	x = 1;
	y = 1;
	player.location[X] = 0;
	while (y < (int)ft_arrlen(map) - 1)
	{
		while (x < (int)ft_strlen(map[0]) - 1)
		{
			if (ft_strchr("NESW", map[y][x]))
			{
				if (player.location[Y] != 0)
					exit(ft_error(DUP_PLAYERS, 0));
			/* change to this: exit(ft_error(delete_all(MEM_FAIL,
			 * map))); */
				player = make_player(x, y, map[y][x]);
			}
			x++;
		}
		y++;
		x = 1;
	}
	return (player);
}

int			main(int argc, char **argv)
{
	t_game		game;

	game.map = cub_parser(open_file(argc, argv));
	validate_n_s_walls(game.map);
	game.player = find_player(game.map.coords);
	print_gameinfo(game);
	return (0);
}
