/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 18:37:32 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/15 16:59:47 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

static int	rgb(int red, int green, int blue)
{
	int		result;

	result = 0;
	if (red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 ||
			blue < 0)
		return (-1);
	red = red << 16;
	green = green << 8;
	result = red | green | blue;
	return (result);
}

int			main(void)
{
	void		*connection;
	void		*window;
	int			x;
	int			y;

	x = 100;
	y = 100;
	connection = mlx_init();
	if (connection == NULL)
		ft_printf("no connection established\n");
	else
		ft_printf("address of connection: %p\n", connection);
	window = mlx_new_window(connection, 400, 400, "A window by Ryan");
	if (!window)
		return (1);
	mlx_clear_window(connection, window);
	while (x < 300)
	{
		while (y < 300)
		{
			mlx_pixel_put(connection, window, x, y,
					rgb(255, 255, 255));
			y++;
		}
		y = 100;
		x++;
	}
	mlx_loop(connection);
	mlx_destroy_window(connection, window);
	return (0);
}
