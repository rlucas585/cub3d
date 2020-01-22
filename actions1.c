/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 16:07:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 17:39:00 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <mlx.h>

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
	create_image(*xsrv, *info);
}

void		move_forward(t_game *info, t_display *xsrv)
{
	double		x;
	double		y;

	x = 0.5 * sin(to_radians(info->player.dir));
	y = 0.5 * -cos(to_radians(info->player.dir));
	if (info->map.coords[(int)(info->player.location[Y] + y)]
			[(int)(info->player.location[X] + x)] != '1')
	{
		info->player.location[X] += x;
		info->player.location[Y] += y;
	}
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
	(void)xsrv;
}
