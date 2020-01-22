/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 15:37:28 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

int			say_hi(int c, t_display *xsrv)
{
	ft_printf("Hi, you just pressed %d\n", c);
	ft_printf("xsrv.imginf->bpp = %d\n", (*xsrv).imginf->bpp);
	return (1);
}

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
	xsrv.imginf = (t_imginf *)malloc(sizeof(t_imginf));
	xsrv.imga = mlx_get_data_addr(xsrv.img, &xsrv.imginf->bpp,
			&xsrv.imginf->size_line, &xsrv.imginf->endian);
	mlx_put_image_to_window(xsrv.dpy, xsrv.w, xsrv.img, 0, 0);
	mlx_destroy_image(xsrv.dpy, xsrv.img);
	ft_printf("xsrv.imginf->bpp = %d\n", xsrv.imginf->bpp);
	mlx_key_hook(xsrv.w, &say_hi, &xsrv);
	mlx_loop(xsrv.dpy);
	mlx_destroy_window(xsrv.dpy, xsrv.w);
	return (0);
}
