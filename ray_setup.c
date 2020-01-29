/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_setup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 16:56:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/29 16:56:45 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

void		init_plane(t_ray *ray, t_game info)
{
	ray->planeX = 0.66 * cos(to_radians(info.player.dir)); // camera plane calcs
	ray->planeY = 0.66 * sin(to_radians(info.player.dir));
}

void		new_ray(t_ray *ray, t_game info)
{
		ray->cameraX = 2 * (double)ray->x / (double)(info.map.res[0]) - 1;
		ray->dda.rayDirX = sin(to_radians(info.player.dir)) +
			ray->planeX * ray->cameraX;
		ray->dda.rayDirY = -cos(to_radians(info.player.dir)) +
			ray->planeY * ray->cameraX;
		ray->dda.mapX = (int)info.player.location[X];
		ray->dda.mapY = (int)info.player.location[Y];
		ray->dda.deltaDistX = ft_abs_d(1 / ray->dda.rayDirX);
		ray->dda.deltaDistY = ft_abs_d(1 / ray->dda.rayDirY);
		ray->dda.hit = 0;
}

void		image_setup(t_ray *ray, t_game info)
{
	ray->lineheight = (int)(info.map.res[1] / ray->dda.perpWallDist);
	ray->drawStart = -ray->lineheight / 2 + info.map.res[1] / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineheight / 2 + info.map.res[1] / 2;
	if (ray->drawEnd >= info.map.res[1])
		ray->drawEnd = info.map.res[1] - 1;
}

void		texture_setup(t_ray *ray, t_game info)
{
	if (ray->dda.side == EAST || ray->dda.side == WEST)
		ray->tx.wallX = info.player.location[Y] + ray->dda.perpWallDist *
			ray->dda.rayDirY;
	else
		ray->tx.wallX = info.player.location[X] + ray->dda.perpWallDist *
			ray->dda.rayDirX;
	ray->tx.wallX -= floor((ray->tx.wallX));
	ray->tx.texX = (int)(ray->tx.wallX * (double)128);
	if ((ray->dda.side == EAST || ray->dda.side == WEST) && ray->dda.rayDirX > 0)
		ray->tx.texX = 128 - ray->tx.texX - 1;
	if ((ray->dda.side == NORTH || ray->dda.side == SOUTH) && ray->dda.rayDirY < 0)
		ray->tx.texX = 128 - ray->tx.texX - 1;
	ray->tx.texX = 128 / 2 - (ray->tx.texX - 128 / 2) - 1;
	ray->tx.step = 1.0 * 128 / ray->lineheight;
	ray->tx.texPos = (ray->drawStart - info.map.res[1] / 2 +
			ray->lineheight / 2) * ray->tx.step;
}

