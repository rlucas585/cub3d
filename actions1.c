/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:07:10 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <mlx.h>

#include <stdio.h>

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
		else
			if (map[(int)*y - 1][(int)(floor(*x))] == '1')
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
		else
			if (map[(int)floor(*y)][(int)*x - 1] == '1')
				*x += 0.05;
	}
}

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
	move(&cub->info, 0.2, left);
	bump(&cub->info.pos.x, &cub->info.pos.y, cub->info.map);
}

void		move_right(t_cub *cub)
{
	int			right;

	right = cub->info.dir + 90;
	right = (right > 360) ? right - 360 : right;
	move(&cub->info, 0.2, right);
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

void		turn_left(t_cub *cub)
{
	cub->info.dir -= TURNANGLE;
	if (cub->info.dir < 0)
		cub->info.dir += 360;
}

void		turn_right(t_cub *cub)
{
	cub->info.dir += TURNANGLE;
	if (cub->info.dir >= 360)
		cub->info.dir -= 360;
}

void		escape(t_cub *cub)
{
	delete_info(0, cub->info);
	mlx_destroy_window(cub->xsrv.dpy, cub->xsrv.w);
}

void		player_actions(t_cub *cub)
{
	if (cub->key.left)
		turn_left(cub);
	if (cub->key.right)
		turn_right(cub);
	if (cub->key.w)
		move_forward(cub);
	if (cub->key.s)
		move_back(cub);
	if (cub->key.a)
		move_left(cub);
	if (cub->key.d)
		move_right(cub);
}
