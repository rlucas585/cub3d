/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/21 15:43:36 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>
#include <math.h>

#include <stdio.h>

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
		mlx_pixel_put(xsrv.dpy, xsrv.w, x, y, ceiling);
		y++;
	}
	while (y <= end)
	{
		mlx_pixel_put(xsrv.dpy, xsrv.w, x, y, color);
		y++;
	}
	while (y <= info.map.res[1])
	{
		mlx_pixel_put(xsrv.dpy, xsrv.w, x, y, floor);
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


	info.player.dir = 150;
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
		/* rayDirX = tan(to_radians(33)) * rayDirY; */
		/* rayDirY = tan(to_radians(33)) * rayDirX; */

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
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall or not
			if (info.map.coords[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
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

		// give x and y sides different brightness
		if (side == 1)
			color = color / 2;

		// draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color, xsrv, info);
		x++;
	}
}
