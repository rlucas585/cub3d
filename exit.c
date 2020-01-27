/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 12:21:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/27 17:24:34 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

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

void		delete_img_data(char *strs[5])
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
}

int			delete_info(int err, t_map map)
{
	delete_map(map.coords);
	delete_tex(map.textures);
	return (err);
}

int			delete_all(int err, t_all all)
{
	delete_map(all.info->map.coords);
	delete_tex(all.info->map.textures);
	delete_img_data(all.info->texstrs);
	if (all.xsrv->imginf)
		free(all.xsrv->imginf);
	if (all.info->texinf)
		free(all.info->texinf);
	delete_imgs(all.info->imgs);
	return (err);
}
