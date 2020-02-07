/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_info2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:43:48 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/07 14:44:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

/*
** Get color information for floor and ceiling from .cub file, store as single
** integers with correct format for mlx_pixel_put().
*/

static int	validate_color(char *line)
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
