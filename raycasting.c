/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 16:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/20 20:00:13 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <cub3d.h>

#include <stdio.h>

void		verLine(int x, int start, int end, int color, t_display xsrv)
{
	int			y;
	int			ceiling;
	int			floor;

	ceiling = ft_hex("282828");
	floor = ft_hex("928374");
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
	while (y <= 1080)
	{
		mlx_pixel_put(xsrv.dpy, xsrv.w, x, y, floor);
		y++;
	}
}

void		ray(t_game info, t_display link)
{
	double	planeX;
	double	planeY;
	int		x;

	planeX = 0; // 2d raycaster version of camera plane
	planeY = 0.66;
	x = 0;

	while (x < info.map.res[0])
	{
		// Calculating ray position and direction
		double	cameraX = 2 * (double)x / (double)(info.map.res[0]) - 1; // x-coord in camera space
		double	rayDirX = info.player.dir[X] + planeX * cameraX;
		double	rayDirY = info.player.dir[Y] + planeY * cameraX;

		printf("cameraX = %f\n", cameraX);
		ft_printf("info.map.res[0] - 1 = %d\n", info.map.res[0] - 1);
		// The box of the map we're in
		int		mapX = (int)info.player.location[X];
		int		mapY = (int)info.player.location[Y];

		// Length of ray from current position to next x or y-side
		double	sideDistX;
		double	sideDistY;

		// Length of ray from one x or y-side to next x or y-side
		double	deltaDistX = ft_abs_d(1 / rayDirX);
		double	deltaDistY = ft_abs_d(1 / rayDirY);
		double	perpWallDist;

		ft_printf("RayDirX = %d\n", rayDirX);
		// What direction to step in x or y-direction (either +1 or -1)
		int		stepX;
		int		stepY;

		int		hit = 0; // was a wall hit?
		int		side; // was a NS or a EW wall hit?

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
			if (info.map.coords[mapY][mapX] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info.player.location[X] + (1 - stepX) / 2) /
				rayDirX;
		else
			perpWallDist = (mapY - info.player.location[Y] + (1 - stepY) / 2) /
				rayDirY;

		// Calculate height of line to draw on screen
		int		lineHeight = (int)(info.map.res[1] / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		int		drawStart = -lineHeight / 2 + info.map.res[1] / 2;
		if (drawStart < 0)
			drawStart = 0;
		int		drawEnd = lineHeight / 2 + info.map.res[1] / 2;
		if (drawEnd >= info.map.res[1])
			drawEnd = info.map.res[1] - 1;

		// Choose wall color
		int		color;
		switch(info.map.coords[mapY][mapX])
		{
			case 1:	color = ft_hex("fb4934"); // red
					break ;
			case 2:	color = ft_hex("b8bb26"); // green
					break ;
			case 3:	color = ft_hex("83a598"); // blue
					break ;
			case 4:	color = ft_hex("fbf1c7"); // white
					break ;
			case 5:	color = ft_hex("fabd2f"); // yellow
					break ;
		}

		// give x and y sides different brightness
		if (side == 1)
			color = color / 2;

		ft_printf("x = %d, drawStart = %d, drawEnd = %d\n", x, drawStart, drawEnd);
		// draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color, link);
		x++;
	}
}
