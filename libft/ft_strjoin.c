/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:47:48 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 11:22:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t		newlen;
	size_t		i;
	size_t		j;
	char		*newstring;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newlen = ft_strlen(s1) + ft_strlen(s2);
	newstring = (char *)malloc(sizeof(char) * newlen + 1);
	if (!newstring)
		return (NULL);
	while (s1[i])
	{
		*(newstring + i) = s1[i];
		i++;
	}
	while (i + j < newlen)
	{
		*(newstring + i + j) = s2[j];
		j++;
	}
	*(newstring + i + j) = '\0';
	return (newstring);
}
