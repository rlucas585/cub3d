/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmpsave.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:52:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/19 09:09:22 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>
#include <fcntl.h>

static unsigned int	count_padding(t_cub cub)
{
	unsigned int	count;
	int				x;
	int				y;

	x = 0;
	y = cub.info.res.y - 1;
	count = 0;
	while (y >= 0)
	{
		while (x < cub.info.res.x)
			x++;
		if ((x * 3) % 4 != 0)
			count += 4 - ((x * 3) % 4);
		x = 0;
		y--;
	}
	return (count);
}

static void			write_bmp_header(int fd, t_cub cub)
{
	unsigned int	size;

	size = cub.info.res.y * cub.info.res.x * 3 + count_padding(cub) + 54;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\x00\x00\x00\x00", 4);
	write(fd, "\x36\x00\x00\x00", 4);
	write(fd, "\x28\x00\x00\x00", 4);
	write(fd, &cub.info.res.x, 4);
	write(fd, &cub.info.res.y, 4);
	write(fd, "\x01\x00", 2);
	write(fd, "\x18\x00\x00\x00", 2);
	write(fd, "\x00\x00\x00\x00", 4);
	write(fd, "\x00\x00\x00\x00", 4);
	write(fd, "\x00\x00\x00\x00", 4);
	write(fd, "\x00\x00\x00\x00", 4);
	write(fd, "\x00\x00\x00\x00", 4);
	write(fd, "\x00\x00\x00\x00", 4);
}

void				save_init_img(t_cub cub)
{
	int		fd;
	int		x;
	int		y;

	x = 0;
	y = cub.info.res.y - 1;
	fd = open("output.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit(ft_error(delete_all(BMP_FAIL, cub), 0));
	write_bmp_header(fd, cub);
	while (y >= 0)
	{
		while (x < cub.info.res.x)
		{
			write(fd, cub.xsrv.imga + x * 4 + y *
					cub.xsrv.imginf->size_line, 3);
			x++;
		}
		if ((x * 3) % 4 != 0)
			write(fd, "\x00\x00\x00", 4 - ((x * 3) % 4));
		x = 0;
		y--;
	}
	close(fd);
}
