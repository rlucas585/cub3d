/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floorcast.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:15:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 18:39:04 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <stdio.h>

void		wallcast(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tx.y = (int)ray->tex_pos;
		ray->tex_pos += ray->txstep;
		color = cub->info.texstrs[ray->side][ray->tx.x +
			cub->info.texinf[ray->side]->size.y * ray->tx.y];
		img_put_pixel(*cub, x, y, color);
		y++;
	}
}

void		floorcast_setup(t_info info, t_ray *ray, t_2d *wall_pos)
{
	if (ray->side == EAST)
	{
		wall_pos->x = ray->map.x;
		wall_pos->y = ray->map.y + ray->wallx;
	}
	if (ray->side == WEST)
	{
		wall_pos->x = ray->map.x + 1.0;
		wall_pos->y = ray->map.y + ray->wallx;
	}
	if (ray->side == SOUTH)
	{
		wall_pos->x = ray->map.x + ray->wallx;
		wall_pos->y = ray->map.y;
	}
	if (ray->side == NORTH)
	{
		wall_pos->x = ray->map.x + ray->wallx;
		wall_pos->y = ray->map.y + 1.0;
	}
	if (ray->draw_end < 0)
		ray->draw_end = info.res.y;
}

void		tex_c_and_f(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;
	t_floor			fc;

	y = ray->draw_end + 1;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		fc.pos.x = fc.weight * fc.wall.x + (1.0 - fc.weight) * cub->info.pos.x;
		fc.pos.y = fc.weight * fc.wall.y + (1.0 - fc.weight) * cub->info.pos.y;
		fc.tx.x = (int)(fc.pos.x * cub->info.texinf[ray->side]->size.x) %
			cub->info.texinf[ray->side]->size.x;
		fc.tx.y = (int)(fc.pos.y * cub->info.texinf[ray->side]->size.y) %
			cub->info.texinf[ray->side]->size.y;
		color = cub->info.texstrs[FLOOR][cub->info.texinf[ray->side]->size.x *
			fc.tx.y + fc.tx.x];
		img_put_pixel(*cub, x, y, color);
		color = cub->info.texstrs[CEILING][cub->info.texinf[ray->side]->size.x *
			fc.tx.y + fc.tx.x];
		img_put_pixel(*cub, x, cub->info.res.y - y, color);
		y++;
	}
}

void		tex_c(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;
	t_floor			fc;

	y = ray->draw_end + 1;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		fc.pos.x = fc.weight * fc.wall.x + (1.0 - fc.weight) * cub->info.pos.x;
		fc.pos.y = fc.weight * fc.wall.y + (1.0 - fc.weight) * cub->info.pos.y;
		fc.tx.x = (int)(fc.pos.x * cub->info.texinf[CEILING]->size.x) %
			cub->info.texinf[ray->side]->size.x;
		fc.tx.y = (int)(fc.pos.y * cub->info.texinf[CEILING]->size.y) %
			cub->info.texinf[ray->side]->size.y;
		color = cub->info.texstrs[CEILING][cub->info.texinf[CEILING]->size.x *
			fc.tx.y + fc.tx.x];
		img_put_pixel(*cub, x, y, cub->info.floor.x);
		img_put_pixel(*cub, x, cub->info.res.y - y, color);
		y++;
	}
}

void		tex_f(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;
	t_floor			fc;

	y = ray->draw_end + 1;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		fc.pos.x = fc.weight * fc.wall.x + (1.0 - fc.weight) * cub->info.pos.x;
		fc.pos.y = fc.weight * fc.wall.y + (1.0 - fc.weight) * cub->info.pos.y;
		fc.tx.x = (int)(fc.pos.x * cub->info.texinf[FLOOR]->size.x) %
			cub->info.texinf[ray->side]->size.x;
		fc.tx.y = (int)(fc.pos.y * cub->info.texinf[FLOOR]->size.y) %
			cub->info.texinf[ray->side]->size.y;
		color = cub->info.texstrs[FLOOR][cub->info.texinf[FLOOR]->size.x *
			fc.tx.y + fc.tx.x];
		img_put_pixel(*cub, x, y, color);
		img_put_pixel(*cub, x, cub->info.res.y - y, cub->info.ceiling.x);
		y++;
	}
}

void		no_tex(t_cub *cub, t_ray *ray, int x)
{
	int		y;

	y = ray->draw_end + 1;
	while (y < cub->info.res.y)
	{
		img_put_pixel(*cub, x, y, cub->info.floor.x);
		img_put_pixel(*cub, x, cub->info.res.y - y, cub->info.ceiling.x);
		y++;
	}
}

void		floorcast(t_cub *cub, t_ray *ray, int x)
{
	if (cub->info.f_or_c.x == 2 && cub->info.f_or_c.y == 2)
		tex_c_and_f(cub, ray, x);
	else if (cub->info.f_or_c.x == 2 || cub->info.f_or_c.y == 2)
	{
		if (cub->info.f_or_c.x == 2)
			tex_f(cub, ray, x);
		if (cub->info.f_or_c.y == 2)
			tex_c(cub, ray, x);
	}
	else
		no_tex(cub, ray, x);
}
