/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_images.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:17:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/06 11:04:30 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

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
		*(unsigned int *)&cub.xsrv.imga[4 * x + cub.xsrv.imginf->size_line * y] =
			color;
	else if (cub.imgswap == 1)
		*(unsigned int *)&cub.xsrv.imga2[4 * x + cub.xsrv.imginf->size_line * y] =
			color;
}
