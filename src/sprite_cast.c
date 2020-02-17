/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_cast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 10:25:30 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 17:50:05 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

void		sprite_cast(t_cub *cub, double *z_buffer, t_sray *sray)
{
	int			stripe;
	int			y;

	stripe = sray->draw_start.x;
	while (stripe <= sray->draw_end.x && stripe < cub->info.res.x)
	{
		y = init_scast(cub, sray, stripe);
		if (sray->transform.y > 0 && stripe >= 0 && stripe < cub->info.res.x &&
				sray->transform.y < z_buffer[stripe])
		{
			while (y < sray->draw_end.y)
			{
				put_sprite_pixel(cub, y, stripe, sray);
				y++;
			}
		}
		stripe++;
	}
}

void		draw_sprites(t_cub *cub, double *z_buffer, t_2d plane)
{
	t_sray		sray;
	int			i;

	i = 0;
	sprite_setup1(*cub, &sray);
	while (i < cub->info.spritenum)
	{
		sprite_setup2(cub->info, &sray, i, plane);
		if (sray.sprt.width < 1)
			sray.sprt.width = 1;
		if (sray.sprt.height < 1)
			sray.sprt.height = 1;
		sprite_cast(cub, z_buffer, &sray);
		i++;
	}
	free(sray.sprite_order);
	free(sray.sprite_dist);
}
