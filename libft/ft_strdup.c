/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:20:13 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/30 11:27:15 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	size_t		len;
	size_t		i;
	char		*newptr;

	i = 0;
	len = ft_strlen(s1);
	newptr = (char *)malloc(len + 1);
	if (!newptr)
		return (NULL);
	while (i < len)
	{
		*(newptr + i) = s1[i];
		i++;
	}
	*(newptr + i) = '\0';
	return (newptr);
}
