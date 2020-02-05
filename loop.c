/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 10:14:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 18:49:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>
#include <libft.h>
#include <fcntl.h>

void		save_init_img(t_cub cub)
{
	int				fd;
	unsigned int	size;

	size = 54 + cub.info.res.x * cub.info.res.y * 4;
	fd = open("output.bmp", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		exit(ft_error(delete_all(BMP_FAIL, cub), 0));
	write(fd, "BM", 2); // the filetype (2 bytes)
	write(fd, &size, 4);
	write(fd, "\x00\x00\x00\x00", 4); // reserved bytes for image processing
	write(fd, "\x36\x00\x00\x00", 4); // Pixel Data offset
	write(fd, "\x28\x00\x00\x00", 4); // Size of bitmap header
	write(fd, &cub.info.res.x, 4); // Image width
	write(fd, &cub.info.res.y, 4); // Image height
	write(fd, "\x01\x00", 2); // Number of color planes
	write(fd, "\x20\x00\x00\x00", 2); // Bits per pixel
	write(fd, "\x00\x00\x00\x00", 4); // Compression (set to 0)
	write(fd, "\x00\x00\x00\x00", 4); // xpixels res of target dev, 0 = no preference
	write(fd, "\x00\x00\x00\x00", 4); // ypixels, as above
	write(fd, "\x00\x00\x00\x00", 4); // Total colors in pallet, uses bpp if blank
	write(fd, "\x00\x00\x00\x00", 4); // Important colors, 0 = ignore
}

/*
** Create a raycasted image, put it to the window, then destroy it.
*/

static void		create_image(t_cub *cub)
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
	if (cub->save == 1)
	{
		save_init_img(*cub);
		cub->save = 0;
	}
	mlx_destroy_image(cub->xsrv.dpy, cub->xsrv.img);
}

/*
** Remember to fix the error in map parsing, "NOO" is accepted instead of "NO";
*/

int				loop_func(t_cub *cub)
{
	player_actions(cub);
	create_image(cub);
	return (1);
}
