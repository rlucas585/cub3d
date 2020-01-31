/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 20:52:52 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <mlx.h>

#include <stdio.h>

void		move(t_info *info, double dist, int dir)
{
	if (info->map[(int)(info->pos.y)][(int)(info->pos.x + dist *
				sin(to_radians(dir)))] != '1')
		info->pos.x += dist * sin(to_radians(dir));
	if (info->map[(int)(info->pos.y + dist *
			-cos(to_radians(dir)))][(int)(info->pos.x)] != '1')
		info->pos.y += dist * -cos(to_radians(dir));
}

void		move_left(t_cub *cub)
{
	int			left;

	left = cub->info.dir - 90;
	left = (left < 0) ? left + 360 : left;
	move(&cub->info, STRAFESPEED, left);
	bump(&cub->info.pos.x, &cub->info.pos.y, cub->info.map);
}

void		move_right(t_cub *cub)
{
	int			right;

	right = cub->info.dir + 90;
	right = (right > 360) ? right - 360 : right;
	move(&cub->info, STRAFESPEED, right);
	bump(&cub->info.pos.x, &cub->info.pos.y, cub->info.map);
}

void		move_forward(t_cub *cub)
{
	move(&cub->info, FORWARDSPEED, cub->info.dir);
	bump(&cub->info.pos.x, &cub->info.pos.y, cub->info.map);
}

void		move_back(t_cub *cub)
{
	int			reverse;

	reverse = cub->info.dir - 180;
	reverse = (reverse < 0) ? reverse + 360 : reverse;
	move(&cub->info, BACKWARDSPEED, reverse);
	bump(&cub->info.pos.x, &cub->info.pos.y, cub->info.map);
}
