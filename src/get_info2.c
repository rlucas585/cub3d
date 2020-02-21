/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_info2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:43:48 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/21 10:23:39 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

/*
** Get color information for floor and ceiling from .cub file, store as single
** integers with correct format for mlx_pixel_put().
*/

static int	check_three_digits(char *line)
{
	size_t		i;

	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (i > 3)
		return (ERROR);
	return (i);
}

static int	only_three_colors(char *line)
{
	size_t		i;
	int			num;

	i = 0;
	num = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			if (check_three_digits(line + i) == ERROR)
				return (ERROR);
			i += (int)check_three_digits(line + i);
			num++;
		}
		else
			i++;
	}
	if (num != 3)
		return (ERROR);
	return (1);
}

static int	validate_color(char *line)
{
	if (numstrchr(line, ',') != 2)
		return (0);
	if (only_three_colors(line) == ERROR)
		return (0);
	if (ft_atoi(line + 1) > 255 || ft_atoi(line + 1) < 0)
		return (0);
	if (ft_atoi(ft_strchr(line, ',') + 1) > 255 ||
			ft_atoi(ft_strchr(line, ',') + 1) < 0)
		return (0);
	if (ft_atoi(ft_strrchr(line, ',') + 1) > 255 ||
			ft_atoi(ft_strrchr(line, ',') + 1) < 0)
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

/*
** Check to see if the floor and ceiling have been given as a color, or as a
** texture.
*/

int			get_floor_ceiling(char *line, t_info *info)
{
	if (line[0] == 'F' && info->f_or_c.x >= 1)
		exit(ft_error(delete_info(DUP_PARAM, *info), 0));
	if (line[0] == 'C' && info->f_or_c.y >= 1)
		exit(ft_error(delete_info(DUP_PARAM, *info), 0));
	if (line[0] == 'F')
		info->f_or_c.x = 1;
	if (line[0] == 'C')
		info->f_or_c.y = 1;
	if (ft_strchr(line, '.'))
	{
		if (line[0] == 'F')
			info->f_or_c.x = 2;
		if (line[0] == 'C')
			info->f_or_c.y = 2;
		return (get_texture(line, info));
	}
	else
		return (get_color(line, info));
}
