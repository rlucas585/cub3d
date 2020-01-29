/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/29 19:10:47 by rlucas        ########   odam.nl         */
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

void		move(t_dda dda, t_game *info, double dist, int dir)
{
	(void)dda;
	/* if (dda.hit && dda.perpWallDist <= dist) */
	/* { */
	/* 		info->player.location[X] += (dda.perpWallDist - 0.1) * */
	/* 			sin(to_radians(dir)); */
	/* 		info->player.location[Y] += (dda.perpWallDist - 0.1) * */
	/* 			-cos(to_radians(dir)); */
	/* } */
	/* else */
	/* { */
	/* 	info->player.location[X] += dist * sin(to_radians(dir)); */
	/* 	info->player.location[Y] += dist * -cos(to_radians(dir)); */
	/* } */
	if (info->map.coords[(int)(info->player.location[Y])][(int)(info->player.location[X] +
			dist * sin(to_radians(dir)))] != '1')
		info->player.location[X] += dist * sin(to_radians(dir));
	if (info->map.coords[(int)(info->player.location[Y] + dist *
			-cos(to_radians(dir)))][(int)(info->player.location[X])] != '1')
		info->player.location[Y] += dist * -cos(to_radians(dir));
}

void		move_left(t_game *info, t_display *xsrv)
{
	t_dda		dda;
	int			left;

	left = info->player.dir - 90;
	left = (left < 0) ? left + 360 : left;
	noray_dda(&dda, *info, left);
	dda_setup(&dda, *info);
	dda_movement(&dda, *info, 0.4);
	move(dda, info, 0.4, left);
	bump(&info->player.location[X],
			&info->player.location[Y], info->map.coords);
	create_image(*xsrv, *info);
}

void		move_right(t_game *info, t_display *xsrv)
{
	t_dda		dda;
	int			right;

	right = info->player.dir + 90;
	right = (right > 360) ? right - 360 : right;
	noray_dda(&dda, *info, right);
	dda_setup(&dda, *info);
	dda_movement(&dda, *info, 0.4);
	move(dda, info, 0.4, right);
	bump(&info->player.location[X],
			&info->player.location[Y], info->map.coords);
	create_image(*xsrv, *info);
}

void		move_forward(t_game *info, t_display *xsrv)
{
	t_dda		dda;

	noray_dda(&dda, *info, info->player.dir);
	dda_setup(&dda, *info);
	dda_movement(&dda, *info, 0.5);
	move(dda, info, 0.5, info->player.dir);
	bump(&info->player.location[X],
			&info->player.location[Y], info->map.coords);
	create_image(*xsrv, *info);
}

void		move_back(t_game *info, t_display *xsrv)
{
	t_dda		dda;
	int			reverse;

	reverse = info->player.dir - 180;
	reverse = (reverse < 0) ? reverse + 360 : reverse;
	noray_dda(&dda, *info, reverse);
	dda_setup(&dda, *info);
	dda_movement(&dda, *info, 0.4);
	move(dda, info, 0.4, reverse);
	bump(&info->player.location[X],
			&info->player.location[Y], info->map.coords);
	create_image(*xsrv, *info);
}

void		turn_left(t_game *info, t_display *xsrv)
{
	info->player.dir -= 10;
	if (info->player.dir < 0)
		info->player.dir += 360;
	create_image(*xsrv, *info);
}

void		turn_right(t_game *info, t_display *xsrv)
{
	info->player.dir += 10;
	if (info->player.dir >= 360)
		info->player.dir -= 360;
	create_image(*xsrv, *info);
}

void		escape(t_game *info, t_display *xsrv)
{
	delete_info(0, info->map);
	mlx_destroy_window(xsrv->dpy, xsrv->w);
	(void)xsrv;
}
