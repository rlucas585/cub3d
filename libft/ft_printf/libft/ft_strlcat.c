/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:48:33 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 13:35:30 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t		i;
	size_t		j;
	size_t		init;

	i = 0;
	j = 0;
	init = ft_strlen(dest);
	if (destsize <= ft_strlen(dest))
		return (destsize + ft_strlen(src));
	while (dest[i])
		i++;
	while (src[j] != '\0' && i < destsize - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (init + ft_strlen(src));
}
