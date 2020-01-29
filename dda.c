/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 16:53:15 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/29 17:38:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

void		noray_dda(t_dda *dda, t_game info)
{
	dda->hit = 0;
	dda->perpWallDist = 0;
	dda->rayDirX = sin(to_radians(info.player.dir));
	dda->rayDirY = -cos(to_radians(info.player.dir));
	dda->mapX = (int)info.player.location[X];
	dda->mapY = (int)info.player.location[Y];
	dda->deltaDistX = ft_abs_d(1 / dda->rayDirX);
	dda->deltaDistY = ft_abs_d(1 / dda->rayDirY);
}

void		dda_setup(t_dda *dda, t_game info)
{
	if (dda->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (info.player.location[X] - dda->mapX) *
			dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (dda->mapX + 1.0 - info.player.location[X]) *
			dda->deltaDistX;
	}
	if (dda->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (info.player.location[Y] - dda->mapY) *
			dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (dda->mapY + 1.0 - info.player.location[Y]) *
			dda->deltaDistY;
	}
}

void		dda(t_dda *dda, t_game info)
{
	while (dda->hit == 0)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = (dda->rayDirX > 0) ? EAST : WEST;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = (dda->rayDirY > 0) ? SOUTH : NORTH;
		}
		if (info.map.coords[dda->mapY][dda->mapX] == '1')
			dda->hit = 1;
	}
	if (dda->side == EAST || dda->side == WEST)
		dda->perpWallDist = (dda->mapX - info.player.location[X] + 
				(1 - dda->stepX) / 2) / dda->rayDirX;
	else
		dda->perpWallDist = (dda->mapY - info.player.location[Y] +
				(1 - dda->stepY) / 2) / dda->rayDirY;
}

void		dda_movement(t_dda *dda, t_game info)
{
	while (dda->hit == 0 && dda->perpWallDist < 0.5)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = 1;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = 0;
		}
		if (dda->side)
			dda->perpWallDist = (dda->mapX - info.player.location[X] +
					(1 - dda->stepX) / 2) / dda->rayDirX;
		else
			dda->perpWallDist = (dda->mapY - info.player.location[Y] +
					(1 - dda->stepY) / 2) / dda->rayDirY;
		if (info.map.coords[dda->mapY][dda->mapX] == '1')
			dda->hit = 1;
	}
}
