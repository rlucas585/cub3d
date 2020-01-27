/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:39:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/27 17:27:20 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

/*
** Jumptable for direction to face in, measured in degrees.
*/

static double		dir_table(int c)
{
	static int	dir_array[128] = {
		['N'] = 0,
		['E'] = 90,
		['S'] = 180,
		['W'] = 270,
	};

	return (dir_array[c]);
}

/*
** Make a structure for player once found, containing location and direction 
** faced (in degrees).
*/

static t_player		make_player(int x, int y, int c)
{
	t_player	player;

	player.location[X] = (double)x + 0.5;
	player.location[Y] = (double)y + 0.5;
	player.dir = dir_table(c);
	return (player);
}

/*
** Find a player from a 2D-array. If two players are found, then an error is
** returned. make_player() will create the t_player.
*/

t_player			find_player(t_game game)
{
	int			x;
	int			y;
	t_player	player;

	x = 1;
	y = 1;
	player.location[X] = 0;
	while (x < (int)ft_strlen(game.map.coords[0]) - 1)
	{
		while (y < (int)ft_arrlen(game.map.coords) - 1)
		{
			if (ft_strchr("NESW", game.map.coords[y][x]))
			{
				if (player.location[Y] != 0)
					exit(ft_error(delete_info(DUP_PLAYERS, game.map), 0));
				player = make_player(x, y, game.map.coords[y][x]);
				game.map.coords[y][x] = '0';
			}
			y++;
		}
		x++;
		y = 1;
	}
	return (player);
}
