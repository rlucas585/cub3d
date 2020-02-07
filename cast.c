/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floorcast.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:15:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/07 15:21:13 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

/*
** Put relevant pixels from textures onto the walls.
*/

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

/*
** Prepare ray parameters for floorcasting.
*/

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

/*
** Floorcast to fill in the floor and ceiling with colors.
*/

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
