/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   f_c_tex.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 15:11:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/18 12:24:15 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
** Get the position of a texture coordinate for the ceiling/floor pixel
** required. Also returns the color of the relevant texture. Texture chosen
** is determined by the 'side' parameter.
*/

unsigned int	init_tex_pos(t_floor *fc, t_cub *cub, int side)
{
	char			*img;
	unsigned int	color;

	fc->pos.x = fc->weight * fc->wall.x + (1.0 - fc->weight) * cub->info.pos.x;
	fc->pos.y = fc->weight * fc->wall.y + (1.0 - fc->weight) * cub->info.pos.y;
	fc->tx.x = (int)(fc->pos.x * cub->info.texinf[side]->size.x) %
		cub->info.texinf[side]->size.x;
	fc->tx.y = (int)(fc->pos.y * cub->info.texinf[side]->size.y) %
		cub->info.texinf[side]->size.y;
	if (fc->tx.x < 0)
		fc->tx.x = 0;
	if (fc->tx.x > cub->info.texinf[side]->size.x)
		fc->tx.x = cub->info.texinf[side]->size.x - 1;
	if (fc->tx.y < 0)
		fc->tx.y = 0;
	if (fc->tx.y > cub->info.texinf[side]->size.y)
		fc->tx.y = cub->info.texinf[side]->size.y - 1;
	img = cub->info.texstrs[side] + 4 * fc->tx.x +
		cub->info.texinf[side]->size_line * fc->tx.y;
	color = *(unsigned int *)img;
	return (color);
}

/*
** Floor and ceiling casting when both the floor and the ceiling uses textures.
*/

void			tex_c_and_f(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;
	t_floor			fc;

	y = ray->draw_end;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		color = init_tex_pos(&fc, cub, FLOOR);
		img_put_pixel(*cub, x, y, color);
		color = init_tex_pos(&fc, cub, CEILING);
		img_put_pixel(*cub, x, cub->info.res.y - y - 1, color);
		y++;
	}
}

/*
** Floor and ceiling casting when the ceiling is a texture, and the floor
** is only a single color.
*/

void			tex_c(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;
	t_floor			fc;

	y = ray->draw_end;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		img_put_pixel(*cub, x, y, cub->info.floor.x);
		color = init_tex_pos(&fc, cub, CEILING);
		img_put_pixel(*cub, x, cub->info.res.y - y - 1, color);
		y++;
	}
}

/*
** Like tex_c, but vice-versa.
*/

void			tex_f(t_cub *cub, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;
	t_floor			fc;

	y = ray->draw_end;
	floorcast_setup(cub->info, ray, &fc.wall);
	while (y < cub->info.res.y)
	{
		fc.weight = (cub->info.res.y / (2.0 * y - cub->info.res.y)) /
			ray->pdist;
		color = init_tex_pos(&fc, cub, FLOOR);
		img_put_pixel(*cub, x, y, color);
		img_put_pixel(*cub, x, cub->info.res.y - y - 1, cub->info.ceiling.x);
		y++;
	}
}

/*
** Floor and ceiling casting when both are only a single color.
*/

void			no_tex(t_cub *cub, t_ray *ray, int x)
{
	int		y;

	y = ray->draw_end;
	while (y < cub->info.res.y)
	{
		img_put_pixel(*cub, x, y, cub->info.floor.x);
		img_put_pixel(*cub, x, cub->info.res.y - y - 1, cub->info.ceiling.x);
		y++;
	}
}
