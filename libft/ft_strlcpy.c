/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:27:09 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 11:17:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t		i;

	i = 0;
	if (!dest || !src)
		return (0);
	while (destsize > 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
		destsize--;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
