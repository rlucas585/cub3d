/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_player.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:39:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 08:54:54 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

/*
** Jumptable for direction to face in, measured in degrees.
*/

static double	dir_table(int c)
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

static void		make_player(int x, int y, int c, t_info *info)
{
	info->pos.x = (double)x + 0.5;
	info->pos.y = (double)y + 0.5;
	info->dir = dir_table(c);
}

/*
** Find a player from a 2D-array. If two players are found, then an error is
** returned. make_player() will create the t_player.
*/

void			find_player(t_info *info)
{
	int			x;
	int			y;

	x = 1;
	y = 1;
	info->pos.x = 0;
	if (!info->map)
		exit(ft_error(delete_info(NO_MAP, *info), 0));
	while (y < (int)ft_arrlen(info->map) - 1)
	{
		while (x < (int)ft_strlen(info->map[y]) - 1)
		{
			if (ft_strchr("NESW", info->map[y][x]))
			{
				if (info->pos.x != 0)
					exit(ft_error(delete_info(DUP_PLAYERS, *info), 0));
				make_player(x, y, info->map[y][x], info);
				info->map[y][x] = '0';
			}
			x++;
		}
		y++;
		x = 1;
	}
}
