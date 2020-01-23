/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/23 12:10:54 by rlucas        ########   odam.nl         */
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
	ray(info, xsrv);
	mlx_put_image_to_window(xsrv.dpy, xsrv.w, xsrv.img, 0, 0);
	mlx_destroy_image(xsrv.dpy, xsrv.img);
}

/*
** Write a vertical line into an image, used in ray().
*/

void		verLine(int x, int start, int end, int color, t_display xsrv,
		t_game info)
{
	int			y;
	int			ceiling;
	int			floor;

	ceiling = 2631720;
	floor = 9601908;
	y = 0;
	while (y < start)
	{
		img_put_pixel(xsrv, x, y, ceiling);
		y++;
	}
	while (y <= end)
	{
		img_put_pixel(xsrv, x, y, color);
		y++;
	}
	while (y < info.map.res[1])
	{
		img_put_pixel(xsrv, x, y, floor);
		y++;
	}
}

void		ray(t_game info, t_display xsrv)
{
	double	planeX;
	double	planeY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		x;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	// What direction to step in x or y-direction (either +1 or -1)
	int		stepX;
	int		stepY;
	int		hit; // was a wall hit?
	int		side; // was a NS or a EW wall hit?
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		colorchosen;
	int		color;


	planeX = 0.66 * cos(to_radians(info.player.dir)); // camera plane calcs
	planeY = 0.66 * sin(to_radians(info.player.dir));
	x = 0;
	colorchosen = ft_hex("abcdef");

	while (x < info.map.res[0])
	{
		color = colorchosen;
		hit = 0;

		// Calculating ray position and direction
		cameraX = 2 * (double)x / (double)(info.map.res[0]) - 1; // x-coord in camera space
		rayDirX = sin(to_radians(info.player.dir)) + planeX * cameraX;
		rayDirY = -cos(to_radians(info.player.dir)) + planeY * cameraX;

		/* ft_printf("info.map.res[0] - 1 = %d\n", info.map.res[0] - 1); */
		// The box of the map we're in
		mapX = (int)info.player.location[X];
		mapY = (int)info.player.location[Y];

		// Length of ray from one x or y-side to next x or y-side
		deltaDistX = ft_abs_d(1 / rayDirX);
		deltaDistY = ft_abs_d(1 / rayDirY);

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info.player.location[X] - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info.player.location[X]) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info.player.location[Y] - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info.player.location[Y]) * deltaDistY;
		}

		// Performing DDA
		while (hit == 0)
		{
			// jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = (rayDirX > 0) ? EAST : WEST;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = (rayDirY > 0) ? SOUTH : NORTH;
			}
			// Check if ray has hit a wall or not
			if (info.map.coords[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == EAST || side == WEST)
			perpWallDist = (mapX - info.player.location[X] + (1 - stepX) / 2) /
				rayDirX;
		else
			perpWallDist = (mapY - info.player.location[Y] + (1 - stepY) / 2) /
				rayDirY;

		// Calculate height of line to draw on screen
		lineHeight = (int)(info.map.res[1] / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + info.map.res[1] / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + info.map.res[1] / 2;
		if (drawEnd >= info.map.res[1])
			drawEnd = info.map.res[1] - 1;

		// Choose wall color
		if (side == EAST)
			color = GREEN;
		if (side == NORTH)
			color = RED;
		if (side == SOUTH)
			color = PURPLE;
		if (side == WEST)
			color = BLUE;

		// give x and y sides different brightness
		/* if (side == 1) */
		/* 	color = color / 2; */

		// draw the pixels of the stripe as a vertical line into an image.
		verLine(x, drawStart, drawEnd, color, xsrv, info);
		x++;
	}
}
