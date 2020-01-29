/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/29 17:40:38 by rlucas        ########   odam.nl         */
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

void		move(t_dda dda, t_game *info)
{
	if (dda.hit)
	{
		if (dda.perpWallDist > 0.5)
		{
			info->player.location[X] += 0.5 * sin(to_radians(info->player.dir));
			info->player.location[Y] += 0.5 *
				-cos(to_radians(info->player.dir));
		}
		else
		{
			info->player.location[X] += (dda.perpWallDist - 0.1) *
				sin(to_radians(info->player.dir));
			info->player.location[Y] += (dda.perpWallDist - 0.1) *
				-cos(to_radians(info->player.dir));
		}
	}
	else
	{
		info->player.location[X] += 0.5 * sin(to_radians(info->player.dir));
		info->player.location[Y] += 0.5 * -cos(to_radians(info->player.dir));
	}
}

void		move_left(t_game *info, t_display *xsrv)
{
	double		x;
	double		y;
	int			ldir;

	ldir = info->player.dir - 90;
	ldir = (ldir < 0) ? ldir + 360 : ldir;
	x = 0.4 * sin(to_radians(ldir));
	y = 0.4 * -cos(to_radians(ldir));
	if (info->map.coords[(int)(info->player.location[Y] + y)]
			[(int)(info->player.location[X] + x)] != '1')
	{
		info->player.location[X] += x;
		info->player.location[Y] += y;
	}
	bump(&info->player.location[X],
			&info->player.location[Y], info->map.coords);
	create_image(*xsrv, *info);
}

void		move_right(t_game *info, t_display *xsrv)
{
	double		x;
	double		y;
	int			rdir;

	rdir = info->player.dir + 90;
	rdir = (rdir >= 0) ? rdir - 360 : rdir;
	x = 0.4 * sin(to_radians(rdir));
	y = 0.4 * -cos(to_radians(rdir));
	if (info->map.coords[(int)(info->player.location[Y] + y)]
			[(int)(info->player.location[X] + x)] != '1')
	{
		info->player.location[X] += x;
		info->player.location[Y] += y;
	}
	bump(&info->player.location[X],
			&info->player.location[Y], info->map.coords);
	create_image(*xsrv, *info);
}

void		move_forward(t_game *info, t_display *xsrv)
{
	t_dda		dda;

	noray_dda(&dda, *info);
	dda_setup(&dda, *info);
	dda_movement(&dda, *info);
	move(dda, info);
	create_image(*xsrv, *info);
}

void		move_back(t_game *info, t_display *xsrv)
{
	double		x;
	double		y;

	x = 0.5 * -sin(to_radians(info->player.dir));
	y = 0.5 * cos(to_radians(info->player.dir));
	if (info->map.coords[(int)(info->player.location[Y] + y)]
			[(int)(info->player.location[X] + x)] != '1')
	{
		info->player.location[X] += x;
		info->player.location[Y] += y;
	}
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
