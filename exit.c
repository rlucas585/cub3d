/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 12:21:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/03 13:15:38 by rlucas        ########   odam.nl         */
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

void		delete_tex(char *textures[5])
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (textures[i])
			free(textures[i]);
		i++;
	}
}

void		delete_imgs(void *imgs[5])
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (imgs[i])
			free(imgs[i]);
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
	int		i;

	i = 0;
	delete_map(cub.info.map);
	delete_tex(cub.info.texs);
	if (cub.xsrv.imginf)
		free(cub.xsrv.imginf);
	while (i < 5)
	{
		if (cub.info.texinf[i])
			free(cub.info.texinf);
		i++;
	}
	delete_imgs(cub.info.imgs);
	return (err);
}
