/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/23 15:07:00 by rlucas        #+#    #+#                 */
/*   Updated: 2019/12/01 11:33:04 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t		ft_strclen(const char *string, int c)
{
	size_t		count;

	count = 0;
	while (string[count] != c)
		count++;
	return (count);
}
