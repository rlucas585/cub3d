/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 16:46:41 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 18:06:07 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

static int		check_repeat(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == str[i + 1] && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static int		only_chars_in_set(char *str, char *validchars)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(validchars, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				validate_map(char *line, size_t width)
{
	if (ft_strlen(line) != width)
		return (0);
	if (check_repeat(line))
		return (0);
	if (!only_chars_in_set(line, VALID_MAP_CHARS))
		return (0);
	if (line[0] != '1' || line[width - 1] != '1')
		return (0);
	return (1);
}

size_t			ft_arrlen(char **array)
{
	size_t		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void			validate_n_s_walls(t_map mapinfo)
{
	if (ft_arrlen(mapinfo.coords) < 3)
		exit(ft_error(TOO_SHORT, 0));
	if (ft_strlen(mapinfo.coords[0]) < 3)
		exit(ft_error(TOO_THIN, 0));
	if (!only_chars_in_set(mapinfo.coords[0], "1"))
		exit(ft_error(N_S_WALL_ERROR, 0));
			/* change to this: exit(ft_error(delete_all(MEM_FAIL,
			 * mapinfo.coords))); */
	if (!only_chars_in_set(mapinfo.coords[ft_arrlen(mapinfo.coords) - 1], "1"))
		exit(ft_error(N_S_WALL_ERROR, 0));
}
