/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/30 18:45:23 by rlucas        ########   odam.nl         */
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
		/* img_put_pixel(*xsrv, ray->x, ray->y, info.map.ceilingcolor); */
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
		/* img_put_pixel(*xsrv, ray->x, ray->y, info.map.floorcolor); */
		ray->y++;
	}
}

void		ray(t_game info, t_display xsrv)
{
	t_ray		ray;

	ray.x = 0;
	init_plane(&ray, info);
	/* for (int y = 0; y < info.map.res[1]; y++) */
	/* { */
	/* 	float rayDirX0 = sin(to_radians(info.player.dir)) - ray.planeX; */
	/* 	float rayDirY0 = -cos(to_radians(info.player.dir)) - ray.planeY; */
	/* 	float rayDirX1 = sin(to_radians(info.player.dir)) + ray.planeX; */
	/* 	float rayDirY1 = -cos(to_radians(info.player.dir)) + ray.planeY; */
    /*  */
	/* 	int	p = y - info.map.res[1] / 2; */
	/* 	float posZ = 0.5 * info.map.res[1]; */
    /*  */
	/* 	float rowDistance = posZ / p; */
	/* 	float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / info.map.res[1]; */
	/* 	float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / info.map.res[1]; */
    /*  */
	/* 	float floorX = info.player.location[X] + rowDistance * rayDirX0; */
	/* 	float floorY = info.player.location[Y] + rowDistance * rayDirY0; */
    /*  */
	/* 	for (int x = 0; x < info.map.res[0]; ++x) */
	/* 	{ */
	/* 		int	cellX = (int)(floorX); */
	/* 		int	cellY = (int)(floorY); */
    /*  */
	/* 		int	tx = (int)(TEXWIDTH * (floorX - cellX)) & (128 - 1); */
	/* 		int	ty = (int)(TEXHEIGHT * (floorY - cellY)) & (128 - 1); */
    /*  */
	/* 		floorX += floorStepX; */
	/* 		floorY += floorStepY; */
    /*  */
	/* 		unsigned int	color; */
    /*  */
	/* 		ft_memcpy(&color, info.texstrs[NORTH] + 4 * tx + */
	/* 				info.texinf->size_line * ty, 4); */
	/* 		img_put_pixel(xsrv, x, y, color); */
	/* 	} */
	/* } */
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
