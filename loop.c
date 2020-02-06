/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 10:14:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/06 16:32:45 by rlucas        ########   odam.nl         */
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
	int				x;

	size = 54 + cub.info.res.x * cub.info.res.y * 3;
	x = 0;
	fd = open("output.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	write(fd, "\x00\x00\x00\x00", 4); // Image Size - set to 0 when no compression
	write(fd, "\x00\x00\x00\x00", 4); // xpixels res of target dev, 0 = no preference
	write(fd, "\x00\x00\x00\x00", 4); // ypixels, as above
	write(fd, "\x00\x00\x00\x00", 4); // Total colors in pallet, uses bpp if blank
	write(fd, "\x00\x00\x00\x00", 4); // Important colors, 0 = ignore
	while (x < cub.info.res.x)
	{
		write(fd, cub.xsrv.imga, 4 * cub.info.res.x);
		x++;
	}
}

/*
** Create a raycasted image, put it to the window, then destroy it.
*/

void			create_image(t_cub *cub)
{
	ray(cub);
	if (cub->imgswap == 0)
	{
		mlx_put_image_to_window(cub->xsrv.dpy, cub->xsrv.w, cub->xsrv.img, 0, 0);
		cub->imgswap = 1;
	}
	else
	{
		mlx_put_image_to_window(cub->xsrv.dpy, cub->xsrv.w, cub->xsrv.img2, 0, 0);
		cub->imgswap = 0;
	}
	if (cub->save == 1)
	{
		save_init_img(*cub);
		cub->save = 0;
	}
}

int				check_keys(t_keys key)
{
	if (key.w == 0 && key.s == 0 && key.a == 0 && key.d == 0 &&
			key.left == 0 && key.right == 0)
		return (1);
	return (0);
}

/*
** Remember to fix the error in map parsing, "NOO" is accepted instead of "NO";
*/

int				loop_func(t_cub *cub)
{
	if (check_keys(cub->key))
		return (1);
	player_actions(cub);
	create_image(cub);
	return (1);
}
