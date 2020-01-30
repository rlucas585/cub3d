/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/30 16:53:22 by rlucas        ########   odam.nl         */
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

void		move(t_game *info, double dist, int dir)
{
	if (info->map.coords[(int)(info->player.location[Y])]
			[(int)(info->player.location[X] + dist *
				sin(to_radians(dir)))] != '1')
		info->player.location[X] += dist * sin(to_radians(dir));
	if (info->map.coords[(int)(info->player.location[Y] + dist *
			-cos(to_radians(dir)))][(int)(info->player.location[X])] != '1')
		info->player.location[Y] += dist * -cos(to_radians(dir));
}

void		move_left(t_all *all)
{
	int			left;

	left = all->info->player.dir - 90;
	left = (left < 0) ? left + 360 : left;
	move(all->info, 0.2, left);
	bump(&all->info->player.location[X],
			&all->info->player.location[Y], all->info->map.coords);
}

void		move_right(t_all *all)
{
	int			right;

	right = all->info->player.dir + 90;
	right = (right > 360) ? right - 360 : right;
	move(all->info, 0.2, right);
	bump(&all->info->player.location[X],
			&all->info->player.location[Y], all->info->map.coords);
}

void		move_forward(t_all *all)
{
	move(all->info, FORWARDSPEED, all->info->player.dir);
	bump(&all->info->player.location[X],
			&all->info->player.location[Y], all->info->map.coords);
}

void		move_back(t_all *all)
{
	int			reverse;

	reverse = all->info->player.dir - 180;
	reverse = (reverse < 0) ? reverse + 360 : reverse;
	move(all->info, BACKWARDSPEED, reverse);
	bump(&all->info->player.location[X],
			&all->info->player.location[Y], all->info->map.coords);
}

void		turn_left(t_all *all)
{
	all->info->player.dir -= TURNANGLE;
	if (all->info->player.dir < 0)
		all->info->player.dir += 360;
}

void		turn_right(t_all *all)
{
	all->info->player.dir += TURNANGLE;
	if (all->info->player.dir >= 360)
		all->info->player.dir -= 360;
}

void		escape(t_all *all)
{
	delete_info(0, all->info->map);
	mlx_destroy_window(all->xsrv->dpy, all->xsrv->w);
}

void		player_actions(t_all *all)
{
	if (all->key.left)
		turn_left(all);
	if (all->key.right)
		turn_right(all);
	if (all->key.w)
		move_forward(all);
	if (all->key.s)
		move_back(all);
	if (all->key.a)
		move_left(all);
	if (all->key.d)
		move_right(all);
}
