/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floorcast.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:15:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 21:01:34 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

void		wallcast(t_cub *cub, t_ray *ray, int x)
{
	int		y;
	int		color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tx.y = (int)ray->tex_pos;
		ray->tex_pos += ray->txstep;
		color = cub->info.texstrs[ray->side][ray->tx.x + TEXHEIGHT * ray->tx.y];
		img_put_pixel(cub->xsrv, x, y, color);
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

void		floorcast(t_cub *cub, t_ray *ray, int x)
{
	int			y;
	int			color;
	t_floor		fc;

	y = ray->draw_end + 1;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		fc.pos.x = fc.weight * fc.wall.x + (1.0 - fc.weight) * cub->info.pos.x;
		fc.pos.y = fc.weight * fc.wall.y + (1.0 - fc.weight) * cub->info.pos.y;
		fc.tx.x = (int)(fc.pos.x * TEXWIDTH) % TEXWIDTH;
		fc.tx.y = (int)(fc.pos.y * TEXHEIGHT) % TEXHEIGHT;
		color = cub->info.texstrs[SPRITE][TEXWIDTH * fc.tx.y + fc.tx.x];
		img_put_pixel(cub->xsrv, x, y, color);
		color = cub->info.texstrs[SPRITE][TEXWIDTH * fc.tx.y + fc.tx.x];
		img_put_pixel(cub->xsrv, x, cub->info.res.y - y, color);
		y++;
	}
}
