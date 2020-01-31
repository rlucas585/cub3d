/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:47:31 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 20:50:02 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <cub3d.h>

void		count_sprites(t_info *info)
{
	size_t		y;

	y = 0;
	info->spritenum = 0;
	while (info->map[y])
	{
		info->spritenum += numstrchr(info->map[y], '2');
		y++;
	}
}

void		bump(double *x, double *y, char **map)
{
	if (ceil(*y) == *y)
	{
		if (ceil(*x) == *x)
		{
			if (map[(int)*y - 1][(int)floor(*x - 1)] == '1'
					|| map[(int)*y - 1][(int)floor(*x)] == '1')
				*y -= 0.05;
		}
		else if (map[(int)*y - 1][(int)(floor(*x))] == '1')
			*y -= 0.05;
	}
	if (ceil(*x) == *x)
	{
		if (ceil(*y) == *y)
		{
			if (map[(int)floor(*y - 1)][(int)*x - 1] == '1'
					|| map[(int)floor(*y)][(int)*x - 1] == '1')
				*x += 0.05;
		}
		else if (map[(int)floor(*y)][(int)*x - 1] == '1')
			*x += 0.05;
	}
}
