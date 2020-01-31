/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 16:29:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:22:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <fcntl.h>

/*
** Get resolution from .cub file and place in 2-length integer array for x and y
** values.
*/

int			get_resolution(char *line, t_info *info)
{
	int		i;

	i = 1;
	if (line[i] == 0)
		return (ERROR);
	info->res.x = ft_atoi(line + i);
	i++;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == 0)
		return (ERROR);
	info->res.y = ft_atoi(line + i);
	if (info->res.x > 0 && info->res.y > 0)
		return (1);
	return (ERROR);
}

/*
** Jumptable to assign path to texture path to correct location in array.
*/

static int	textures(int c)
{
	static int	compass[128] = {
		['N'] = NORTH,
		['E'] = EAST,
		['X'] = SOUTH,
		['W'] = WEST,
		['S'] = SPRITE,
	};

	return (compass[(int)c]);
}

/*
** Get texture paths from .cub file.
*/

int			get_texture(char *line, t_info *info)
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
	if (line[i + 1] == 0)
		return (ERROR);
	i++;
	texpath = ft_strdup(line + i);
	if (!texpath)
		return (ERROR);
	info->texs[textureid] = texpath;
	return (1);
}

/* Get color information for floor and ceiling from .cub file, store as single
*  integers with correct format for mlx_pixel_put(). */
int			get_color(char *line, t_info *info)
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
		info->floor = rgb(red, green, blue);
	else
		info->ceiling = rgb(red, green, blue);
	return (1);
}
