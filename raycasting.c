/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/29 18:27:44 by rlucas        ########   odam.nl         */
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

void		create_image(t_display xsrv, t_game info)
{
	xsrv.img = mlx_new_image(xsrv.dpy, info.map.res[0], info.map.res[1]);
	if (!xsrv.img)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.imga = mlx_get_data_addr(xsrv.img, &xsrv.imginf->bpp,
			&xsrv.imginf->size_line, &xsrv.imginf->endian);
	if (!xsrv.imga)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	ray(info, xsrv);
	mlx_put_image_to_window(xsrv.dpy, xsrv.w, xsrv.img, 0, 0);
	mlx_destroy_image(xsrv.dpy, xsrv.img);
}

void		draw_image(t_ray *ray, t_game info, t_display *xsrv)
{
	ray->y = 0;
	while (ray->y < ray->drawStart)
	{
		img_put_pixel(*xsrv, ray->x, ray->y, BLUE);
		ray->y++;
	}
	while (ray->y < ray->drawEnd)
	{
		ray->tx.texY = (int)ray->tx.texPos;
		ray->tx.texPos += ray->tx.step;
		ft_memcpy(&ray->color, info.texstrs[ray->dda.side] + 4 * ray->tx.texX +
				info.texinf->size_line * ray->tx.texY, 4);
		img_put_pixel(*xsrv, ray->x, ray->y, ray->color);
		ray->y++;
	}
	while (ray->y < info.map.res[1])
	{
		img_put_pixel(*xsrv, ray->x, ray->y, PURPLE);
		ray->y++;
	}
}

void		ray(t_game info, t_display xsrv)
{
	t_ray		ray;

	ray.x = 0;
	init_plane(&ray, info);
	while (ray.x < info.map.res[0])
	{
		new_ray(&ray, info);
		dda_setup(&ray.dda, info);
		dda(&ray.dda, info);
		image_setup(&ray, info);
		texture_setup(&ray, info);
		draw_image(&ray, info, &xsrv);
		ray.x++;
	}
}
