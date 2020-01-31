/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:39:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

#include <stdio.h>

/*
** Function to place a single pixel in an image at an x & y coordinate.
*/

void		img_put_pixel(t_display xsrv, int x, int y, unsigned int color)
{
	if (x < 0 && y < 0)
		return ;
	*(unsigned int *)&xsrv.imga[4 * x + xsrv.imginf->size_line * y] = color;
}

/*
** Create a raycasted image, put it to the window, then destroy it.
*/

void		create_image(t_cub *cub)
{
	cub->xsrv.img = mlx_new_image(cub->xsrv.dpy, cub->info.res.x,
			cub->info.res.y);
	if (!cub->xsrv.img)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	cub->xsrv.imga = mlx_get_data_addr(cub->xsrv.img, &cub->xsrv.imginf->bpp,
			&cub->xsrv.imginf->size_line, &cub->xsrv.imginf->endian);
	if (!cub->xsrv.imga)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	ray(cub);
	mlx_put_image_to_window(cub->xsrv.dpy, cub->xsrv.w, cub->xsrv.img, 0, 0);
	mlx_destroy_image(cub->xsrv.dpy, cub->xsrv.img);
}

void		ray_setup1(t_info info, t_ray *ray, int x)
{
		ray->camX = 2 * (double)x / (double)info.res.x - 1;
		ray->beam.x = sin(to_radians(info.dir)) + ray->plane.x * ray->camX;
		ray->beam.y = -cos(to_radians(info.dir)) + ray->plane.y * ray->camX;
		ray->map.x = (int)info.pos.x;
		ray->map.y = (int)info.pos.y;
		ray->delt.x = ft_abs_d(1 / ray->beam.x);
		ray->delt.y = ft_abs_d(1 / ray->beam.y);
}

void		ray_setup2(t_info info, t_ray *ray)
{
		if (ray->beam.x < 0)
		{
			ray->step.x = -1;
			ray->sidedist.x = (info.pos.x - ray->map.x) * ray->delt.x;
		}
		else
		{
			ray->step.x = 1;
			ray->sidedist.x = (ray->map.x + 1.0 - info.pos.x) * ray->delt.x;
		}
		if (ray->beam.y < 0)
		{
			ray->step.y = -1;
			ray->sidedist.y = (info.pos.y - ray->map.y) * ray->delt.y;
		}
		else
		{
			ray->step.y = 1;
			ray->sidedist.y = (ray->map.y + 1.0 - info.pos.y) * ray->delt.y;
		}
}

void		dda(t_info info, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->delt.x;
			ray->map.x += ray->step.x;
			ray->side = (ray->beam.x > 0) ? EAST : WEST;
		}
		else
		{
			ray->sidedist.y += ray->delt.y;
			ray->map.y += ray->step.y;
			ray->side = (ray->beam.y > 0) ? SOUTH : NORTH;
		}
		if (info.map[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
	}
	if (ray->side == EAST || ray->side == WEST)
		ray->pdist = (ray->map.x - info.pos.x + (1 - ray->step.y) / 2) /
			ray->beam.y;
	else
		ray->pdist = (ray->map.y - info.pos.y + (1 - ray->step.y) / 2) /
			ray->beam.y;
}


void		draw_setup(t_info info, t_ray *ray)
{
	ray->height = (int)(info.res.y / ray->pdist);
	ray->drawStart = -ray->height / 2 + info.res.y / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->height / 2 + info.res.y / 2;
	if (ray->drawEnd >= info.res.y)
		ray->drawEnd = info.res.y - 1;
	if (ray->side == EAST || ray->side == WEST)
		ray->wallX = info.pos.y + ray->pdist * ray->beam.y;
	else
		ray->wallX = info.pos.x + ray->pdist * ray->beam.x;
	ray->wallX -= floor(ray->wallX);
	ray->tx.x = (int)(ray->wallX * (double)TEXWIDTH);
	if ((ray->side == EAST || ray->side == WEST) && ray->beam.x > 0)
		ray->tx.x = TEXWIDTH - ray->tx.x - 1;
	if ((ray->side == NORTH || ray->side == SOUTH) && ray->beam.y < 0)
		ray->tx.x = TEXWIDTH - ray->tx.x - 1;
	ray->tx.x = TEXWIDTH / 2 - (ray->tx.x - TEXWIDTH / 2) - 1;
	ray->txstep = 1.0 * TEXHEIGHT / ray->height;
	ray->texPos = (ray->drawStart - info.res.y / 2 + ray->height / 2) *
		ray->txstep;
}

void		wallcast(t_cub *cub, t_ray *ray, int x)
{
	int		y;
	int		color;

	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		ray->tx.y = (int)ray->texPos;
		ray->texPos += ray->txstep;
		color = cub->info.texstrs[ray->side][ray->tx.x + TEXHEIGHT * ray->tx.y];
		img_put_pixel(cub->xsrv, x, y, color);
		y++;
	}
}

void		wallcast_notex(t_cub *cub, t_ray *ray, int x)
{
	int		y;
	int		color;

	y = 0;
	while (y < ray->drawStart)
	{
		img_put_pixel(cub->xsrv, x, y, cub->info.ceiling);
		y++;
	}
	while (y < ray->drawEnd)
	{
		ray->tx.y = (int)ray->texPos;
		ray->texPos += ray->txstep;
		color = cub->info.texstrs[ray->side][ray->tx.x + TEXHEIGHT * ray->tx.y];
		img_put_pixel(cub->xsrv, x, y, color);
		y++;
	}
	while (y < cub->info.res.y)
	{
		img_put_pixel(cub->xsrv, x, y, cub->info.floor);
		y++;
	}
}

void		floorcast_setup(t_info info, t_ray *ray, t_2d *wall_pos)
{
	if (ray->side == EAST)
	{
		wall_pos->x = ray->map.x;
		wall_pos->y = ray->map.y + ray->wallX;
	}
	if (ray->side == WEST)
	{
		wall_pos->x = ray->map.x + 1.0;
		wall_pos->y = ray->map.y + ray->wallX;
	}
	if (ray->side == SOUTH)
	{
		wall_pos->x = ray->map.x + ray->wallX;
		wall_pos->y = ray->map.y;
	}
	if (ray->side == NORTH)
	{
		wall_pos->x = ray->map.x + ray->wallX;
		wall_pos->y = ray->map.y + 1.0;
	}
	if (ray->drawEnd < 0)
		ray->drawEnd = info.res.y;
}

void		floorcast(t_cub *cub, t_ray *ray, int x)
{
	int			y;
	int			color;
	t_floor		fc;

	y = ray->drawEnd + 1;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		fc.pos.x = fc.weight * fc.wall.x + (1.0 - fc.weight) * cub->info.pos.x;
		fc.pos.y = fc.weight * fc.wall.y + (1.0 - fc.weight) * cub->info.pos.y;
		fc.tx.x = (int)(fc.pos.x * TEXWIDTH) % TEXWIDTH;
		fc.tx.y = (int)(fc.pos.y * TEXHEIGHT) % TEXHEIGHT;
		color = cub->info.texs[SPRITE][TEXWIDTH * fc.tx.y + fc.tx.x];
		img_put_pixel(cub->xsrv, x, y, color);
		color = cub->info.texs[SPRITE][TEXWIDTH * fc.tx.y + fc.tx.x];
		img_put_pixel(cub->xsrv, x, cub->info.res.y - y, color);
		y++;
	}
}

void		ray(t_cub *cub)
{
	t_ray		ray;
	int			x;

	x = 0;
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	while (x < cub->info.res.x)
	{
		ray_setup1(cub->info, &ray, x);
		ray_setup2(cub->info, &ray);
		dda(cub->info, &ray);
		draw_setup(cub->info, &ray);
		wallcast_notex(cub, &ray, x);
		/* floorcast(cub, &ray, x); */
		x++;
	}
}
