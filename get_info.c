/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_info.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 16:29:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 14:29:59 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>

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
** Check valid texture name.
*/

int			chktex(char *line)
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

/*
** Check to see if the floor and ceiling have been given as a color, or as a
** texture.
*/

int			get_floor_ceiling(char *line, t_info *info)
{
	if (line[0] == 'F' && info->f_or_c.x == 1)
		exit(ft_error(delete_info(DUP_PARAM, *info), 0));
	if (line[0] == 'C' && info->f_or_c.y == 1)
		exit(ft_error(delete_info(DUP_PARAM, *info), 0));
	if (line[0] == 'F')
		info->f_or_c.x = 1;
	if (line[0] == 'C')
		info->f_or_c.y = 1;
	if (ft_strchr(line, '.'))
	{
		if (line[0] == 'F')
			info->floor.rgb.a = 1;
		if (line[0] == 'C')
			info->floor.rgb.a = 1;
		return (get_texture(line, info));
	}
	else
		return (get_color(line, info));
}

/*
** Get color information for floor and ceiling from .cub file, store as single
** integers with correct format for mlx_pixel_put().
*/

int			validate_color(char *line)
{
	char		*last;
	size_t		i;

	i = 0;
	last = ft_strrchr(line, ',') + 1;
	if (ft_atoi(line + 1) > 255 || ft_atoi(line + 1) < 0)
		return (0);
	if (ft_atoi(ft_strchr(line, ',') + 1) > 255 ||
			ft_atoi(ft_strchr(line, ',') + 1) < 0)
		return (0);
	if (ft_atoi(ft_strrchr(line, ',') + 1) > 255 ||
			ft_atoi(ft_strrchr(line, ',') + 1) < 0)
		return (0);
	while (last[i] >= '0' && last[i] <= '9')
		i++;
	if (last[i] != '\0')
		return (0);
	return (1);
}

int			get_color(char *line, t_info *info)
{
	int		i;
	t_color	*f_or_c;

	i = 1;
	if (line[0] == 'F')
		f_or_c = &info->floor;
	else
		f_or_c = &info->ceiling;
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
	if (!validate_color(line))
		return (ERROR);
	(*f_or_c).rgb.r = (unsigned char)ft_atoi(line + 1);
	(*f_or_c).rgb.g = (unsigned char)ft_atoi(ft_strchr(line, ',') + 1);
	(*f_or_c).rgb.b = (unsigned char)ft_atoi(ft_strrchr(line, ',') + 1);
	return (1);
}
