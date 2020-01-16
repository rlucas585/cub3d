/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 18:37:32 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/16 17:46:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

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
			mlx_pixel_put(connection, window, x, y, ft_hex("9d0006"));
			y++;
		}
		y = 100;
		x++;
	}
	mlx_loop(connection);
	mlx_destroy_window(connection, window);
	return (0);
}
