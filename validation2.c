/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 17:04:03 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 17:04:27 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_arrlen(char **array)
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
		exit(ft_error(TOO_THIN), 0);
	if (!only_chars_in_set(mapinfo.coords[0], "1"))
		exit(ft_error(N_S_WALL_ERROR, 0));
			/* change to this: exit(ft_error(delete_all(MEM_FAIL,
			 * mapinfo.coords))); */
	if (!only_chars_in_set(mapinfo.coords[ft_arrlen(mapinfo.coords) - 1], "1"))
		exit(ft_error(N_S_WALL_ERROR, 0));
}
