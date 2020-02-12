/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 12:21:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/10 13:47:06 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

void		delete_map(char **map)
{
	size_t		i;

	i = 0;
	if (!map)
		return ;
	if (map)
		while (map[i])
		{
			free(map[i]);
			i++;
		}
	free(map);
}

void		delete_tex(char *textures[7])
{
	int		i;

	i = 0;
	while (i < 7)
	{
		free(textures[i]);
		i++;
	}
}

void		delete_imgs(t_cub cub, void *imgs[7])
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (imgs[i])
			mlx_destroy_image(cub.xsrv.dpy, imgs[i]);
		free(cub.info.texinf[i]);
		i++;
	}
}

int			delete_info(int err, t_info info)
{
	delete_map(info.map);
	delete_tex(info.texs);
	return (err);
}

int			delete_all(int err, t_cub cub)
{
	delete_map(cub.info.map);
	delete_tex(cub.info.texs);
	if (cub.xsrv.imginf)
		free(cub.xsrv.imginf);
	delete_imgs(cub, cub.info.imgs);
	if (cub.info.z_buffer)
		free(cub.info.z_buffer);
	if (cub.xsrv.img)
		mlx_destroy_image(cub.xsrv.dpy, cub.xsrv.img);
	if (cub.xsrv.img2)
		mlx_destroy_image(cub.xsrv.dpy, cub.xsrv.img2);
	if (cub.xsrv.w)
		mlx_destroy_window(cub.xsrv.dpy, cub.xsrv.w);
	return (err);
}
