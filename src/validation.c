/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 16:46:41 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/12 17:38:00 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

int				only_chars_in_set(char *str, char *validchars)
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

static int		all_params_present(t_info info)
{
	int		i;

	i = 0;
	if (info.map == NULL)
		return (0);
	if (info.res.x == 0 || info.res.y == 0)
		return (0);
	while (i < 5)
	{
		if (info.texs[i] == NULL)
			return (0);
		i++;
	}
	if (info.f_or_c.x == 0 || info.f_or_c.y == 0)
		return (0);
	return (1);
}

int				validate_map1(char *line)
{
	if (!only_chars_in_set(line, VALID_MAP_CHARS))
		return (0);
	return (1);
}

void			validate(t_info info)
{
	if (!all_params_present(info))
		exit(ft_error(delete_info(MISSING_PARAM, info), 0));
	if (ft_arrlen(info.map) < 3)
		exit(ft_error(delete_info(TOO_SHORT, info), 0));
	if (!validate_map2(info))
		exit(ft_error(delete_info(NOT_CONTAINED, info), 0));
}
