/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 16:29:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/12 18:06:21 by rlucas        ########   odam.nl         */
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
	if (!only_chars_in_set(line, "R 0123456789"))
		return (ERROR);
	if (line[i] == 0)
		return (ERROR);
	i += travel_to_char(line + i, "0123456789");
	info->res.x = ft_atoi(line + i);
	i += travel_to_char(line + i, " ");
	if (line[i] == 0)
		return (ERROR);
	i += travel_to_char(line + i, "0123456789");
	info->res.y = ft_atoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != '\0')
		return (ERROR);
	if (info->res.y > 1400)
		info->res.y = 1400;
	if (info->res.x > 2560)
		info->res.x = 2560;
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
		['F'] = FLOOR,
		['C'] = CEILING
	};

	return (compass[(int)c]);
}

/*
** Check if texture name is valid.
*/

static int	chktex(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "XO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "S ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int			find_tex_path(char *line, int i)
{
	int		x;

	x = 0;
	while (line[i] != ' ' && line[i])
		i++;
	while (line[i] != '/' && line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] != '.' || x == 1)
				return (ERROR);
			else
				x = 1;
		}
		i++;
	}
	if (line[i] == 0 || x == 0)
		return (ERROR);
	if (line[i + 1] == 0)
		return (ERROR);
	i++;
	return (i);
}

/*
** Get texture paths from .cub file.
*/

int			get_texture(char *line, t_info *info)
{
	char		*texpath;
	int			i;
	int			textureid;
	static int	array[7];

	i = 0;
	if (chktex(line) != 1)
		return (ERROR);
	textureid = textures(line[0]);
	if (array[textureid] == 1)
		exit(ft_error(delete_info(DUP_PARAM, *info), 0));
	array[textureid] = 1;
	i = find_tex_path(line, i);
	if (i == ERROR)
		return (ERROR);
	texpath = ft_strdup(line + i);
	if (!texpath)
		return (ERROR);
	info->texs[textureid] = texpath;
	return (1);
}
