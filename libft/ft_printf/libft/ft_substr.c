/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:32:34 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/05 11:17:11 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ss;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start + 1) <= len)
		ss = (char *)malloc(ft_strlen(s) - start + 1);
	else
		ss = (char *)malloc(len + 1);
	if (!ss)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		*(ss + i) = s[i + start];
		i++;
	}
	*(ss + i) = '\0';
	return (ss);
}
