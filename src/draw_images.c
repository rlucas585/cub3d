/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_images.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:17:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 10:35:10 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
** Put the correct sprite pixel in place. Used in sprite_cast().
*/

void		put_sprite_pixel(t_cub *cub, int y, int stripe, t_sray *sray)
{
	int		d;

	d = (y) * 256 - cub->info.res.y * 128 + sray->sprt.height * 128;
	sray->tx.y = ((d * cub->info.texinf[SPRITE]->size.y) /
			sray->sprt.height) / 256;
	if (sray->tx.y >= cub->info.texinf[SPRITE]->size.y ||
			sray->tx.x >= cub->info.texinf[SPRITE]->size.x ||
			sray->tx.y < 0 || sray->tx.x < 0)
		return ;
	sray->color = *(unsigned int *)(cub->info.texstrs[SPRITE] + 4 *
			sray->tx.x + cub->info.texinf[SPRITE]->size_line * sray->tx.y);
	if ((sray->color & 0x00FFFFFF) != 0)
		img_put_pixel(*cub, stripe, y, sray->color);
}

/*
** Function to place a single pixel in an image at an x & y coordinate.
*/

void		img_put_pixel(t_cub cub, int x, int y, unsigned int color)
{
	if (x >= cub.info.res.x || y >= cub.info.res.y)
		return ;
	if (x < 0 || y < 0)
		return ;
	if (cub.imgswap == 0)
		*(unsigned int *)&cub.xsrv.imga[4 * x +
			cub.xsrv.imginf->size_line * y] = color;
	else if (cub.imgswap == 1)
		*(unsigned int *)&cub.xsrv.imga2[4 * x +
			cub.xsrv.imginf->size_line * y] = color;
}
