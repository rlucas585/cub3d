/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/07 16:12:52 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <mlx.h>

void		move(t_info *info, double dist, int dir)
{
	if (!ft_strchr("12", info->map[(int)(info->pos.y)][(int)(info->pos.x +
					dist * sin(to_radians(dir)))]))
		info->pos.x += dist * sin(to_radians(dir));
	if (!ft_strchr("12", info->map[(int)(info->pos.y + dist *
			-cos(to_radians(dir)))][(int)(info->pos.x)]))
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
