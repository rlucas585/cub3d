/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 18:16:42 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <stdio.h>

static void		ray_setup1(t_info info, t_ray *ray, int x)
{
	ray->camx = 2 * (double)x / (double)info.res.x - 1;
	ray->beam.x = sin(to_radians(info.dir)) + ray->plane.x * ray->camx;
	ray->beam.y = -cos(to_radians(info.dir)) + ray->plane.y * ray->camx;
	ray->map.x = (int)info.pos.x;
	ray->map.y = (int)info.pos.y;
	ray->delt.x = ft_abs_d(1 / ray->beam.x);
	ray->delt.y = ft_abs_d(1 / ray->beam.y);
}

static void		ray_setup2(t_info info, t_ray *ray)
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

static void		dda(t_info info, t_ray *ray)
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
		ray->pdist = (ray->map.x - info.pos.x + (1 - ray->step.x) / 2) /
			ray->beam.x;
	else
		ray->pdist = (ray->map.y - info.pos.y + (1 - ray->step.y) / 2) /
			ray->beam.y;
}

static void		draw_setup(t_info info, t_ray *ray)
{
	ray->height = (int)(info.res.y / ray->pdist);
	ray->draw_start = -ray->height / 2 + info.res.y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->height / 2 + info.res.y / 2;
	if (ray->draw_end >= info.res.y)
		ray->draw_end = info.res.y - 1;
	if (ray->side == EAST || ray->side == WEST)
		ray->wallx = info.pos.y + ray->pdist * ray->beam.y;
	else
		ray->wallx = info.pos.x + ray->pdist * ray->beam.x;
	ray->wallx -= floor(ray->wallx);
	ray->tx.x = (int)(ray->wallx * (double)info.texinf[ray->side]->size.x);
	if ((ray->side == EAST || ray->side == WEST) && ray->beam.x > 0)
		ray->tx.x = info.texinf[ray->side]->size.x - ray->tx.x - 1;
	if ((ray->side == NORTH || ray->side == SOUTH) && ray->beam.y < 0)
		ray->tx.x = info.texinf[ray->side]->size.x - ray->tx.x - 1;
	ray->tx.x = info.texinf[ray->side]->size.x / 2 - (ray->tx.x - info.texinf[ray->side]->size.x / 2) - 1;
	ray->txstep = 1.0 * info.texinf[ray->side]->size.y / ray->height;
	ray->tex_pos = (ray->draw_start - info.res.y / 2 + ray->height / 2) *
		ray->txstep;
}

void			ray(t_cub *cub)
{
	t_ray		ray;
	int			x;

	if (!cub->info.z_buffer)
		cub->info.z_buffer = (double *)malloc(sizeof(double) * cub->info.res.x);
	if (!cub->info.z_buffer)
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	x = 0;
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	while (x < cub->info.res.x)
	{
		ray_setup1(cub->info, &ray, x);
		ray_setup2(cub->info, &ray);
		dda(cub->info, &ray);
		draw_setup(cub->info, &ray);
		wallcast(cub, &ray, x);
		floorcast(cub, &ray, x);
		cub->info.z_buffer[x] = ray.pdist;
		x++;
	}
	draw_sprites(cub, cub->info.z_buffer, ray.plane);
	ft_bzero(cub->info.z_buffer, (size_t)cub->info.res.x);
}
