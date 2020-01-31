/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 16:46:41 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:10:45 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

/* static int		check_repeat(char *str) */
/* { */
/* 	size_t		i; */
/*  */
/* 	i = 0; */
/* 	while (str[i]) */
/* 	{ */
/* 		if (str[i] == str[i + 1] && str[i + 1] != '\0') */
/* 			return (1); */
/* 		i++; */
/* 	} */
/* 	return (0); */
/* } */

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
	/* if (check_repeat(line)) */
	/* 	return (0); */
	if (!only_chars_in_set(line, VALID_MAP_CHARS))
		return (0);
	if (line[0] != '1' || line[width - 1] != '1')
		return (0);
	return (1);
}

void			validate_n_s_walls(t_info info)
{
	if (ft_arrlen(info.map) < 3)
		exit(ft_error(delete_info(TOO_SHORT, info), 0));
	if (ft_strlen(info.map[0]) < 3)
		exit(ft_error(delete_info(TOO_THIN, info), 0));
	if (!only_chars_in_set(info.map[0], "1"))
		exit(ft_error(delete_info(N_S_WALL_ERROR, info), 0));
	if (!only_chars_in_set(info.map[ft_arrlen(info.map) - 1], "1"))
		exit(ft_error(delete_info(N_S_WALL_ERROR, info), 0));
}
