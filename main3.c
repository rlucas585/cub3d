/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 12:34:30 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>
#include <string.h>

int			main(void)
{
	t_display	xsrv;
	int			x;
	int			y;

	x = 501;
	y = 501;
	xsrv.dpy = mlx_init();
	xsrv.w = mlx_new_window(xsrv.dpy, 500, 500, "hello");
	xsrv.img = mlx_png_file_to_image(xsrv.dpy, "textures/test.png", &x, &y);
	mlx_put_image_to_window(xsrv.dpy, xsrv.w, xsrv.img, 0, 0);
	mlx_loop(xsrv.dpy);
	mlx_destroy_window(xsrv.dpy, xsrv.w);
	return (0);
}
