/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:47:31 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/04 19:33:12 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <cub3d.h>
#include <stdio.h>

static void		count_sprites(t_info *info)
{
	size_t		y;

	y = 0;
	info->spritenum = 0;
	while (info->map[y])
	{
		info->spritenum += numstrchr(info->map[y], '2');
		y++;
	}
	if (info->spritenum == 0)
		return ;
	info->sprts = (t_sprite *)malloc(sizeof(t_sprite) * info->spritenum);
	printf("info->spritenum = %d\n", info->spritenum);
	if (info->sprts == NULL)
		exit(ft_error(delete_info(MEM_FAIL, *info), 0));
}

void			init_sprites(t_info *info)
{
	size_t		y;
	size_t		x;
	size_t		i;

	y = 0;
	x = 0;
	i = 0;
	count_sprites(info);
	while (info->map[y] && info->spritenum != 0)
	{
		while (info->map[y][x])
		{
			if (info->map[y][x] == '2')
			{
				info->sprts[i].pos.x = x + 0.5;
				info->sprts[i].pos.y = y + 0.5;
				info->sprts[i].type = 2;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void			bump(double *x, double *y, char **map)
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
