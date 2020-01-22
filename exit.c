/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 12:21:20 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 16:49:43 by rlucas        ########   odam.nl         */
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

int			delete_info(int err, t_map map)
{
	delete_map(map.coords);
	delete_tex(map.textures);
	return (err);
}
