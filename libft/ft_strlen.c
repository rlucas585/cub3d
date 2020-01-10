/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 14:05:51 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/07 17:50:38 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *string)
{
	size_t		count;

	count = 0;
	while (string[count] != '\0')
		count++;
	return (count);
}
