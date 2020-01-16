/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 16:29:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/16 18:12:50 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <fcntl.h>

int		get_resolution(char *line, t_map *mapinfo)
{
	int		i;

	i = 1;
	if (line[i] == 0)
		return (ERROR);
	mapinfo->res[0] = ft_atoi(line + i);
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == 0)
		return (ERROR);
	mapinfo->res[1] = ft_atoi(line + i);
	if (mapinfo->res[0] > 0 && mapinfo->res[1] > 0)
		return (1);
	return (ERROR);
}

int		textures(int c)
{
	int			ret;
	static int	compass[5] = {
		['N'] = NORTH,
		['E'] = EAST,
		['X'] = SOUTH,
		['W'] = WEST,
		['S'] = SPRITE,
	};

	return (compass[(int)c]);
}

int		get_texture(char *line, t_map *mapinfo)
{
	char	*texpath;
	int		i;
	int		textureid;

	i = 0;
	textureid = textures(line[0]);
	while (line[i] != '/')
		i++;
	if (line[i] == 0)
		return (ERROR);
	texpath = ft_strdup(line + i);
	if (!texpath)
		return (ERROR);
	mapinfo->textures[textureid] = texpath;
	return (1);
}

int		get_color(char *line, t_map *mapinfo)
{
	int		red;
	int		green;
	int		blue;
	int		i;

	i = 1;
	if (line[1] == 0)
		return (ERROR);
	if (ft_strchr(line, ',') == ft_strrchr(line, ',') ||
			ft_strchr(line, ',') + 1 == ft_strrchr(line, ','))
		return (ERROR);
	while (line[i])
	{
		if (line[i] != ',' && line[i] != ' ' && !ft_isdigit(line[i]))
			return (ERROR);
		i++;
	}
	red = ft_atoi(line + 1);
	green = ft_atoi(ft_strchr(line, ',') + 1);
	blue = ft_atoi(ft_strrchr(line, ',') + 1);
	if (line[0] == 'F')
		mapinfo->floorcolor = rgb(red, green, blue);
	else
		mapinfo->ceilingcolor = rgb(red, green, blue);
	return (1);
}
