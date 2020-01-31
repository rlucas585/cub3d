/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_images.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:17:42 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 20:18:01 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

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
