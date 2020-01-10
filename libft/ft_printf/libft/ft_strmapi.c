/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:19:33 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 11:33:47 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstr;

	i = 0;
	if (!s)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!newstr)
		return (NULL);
	while (s[i] != '\0')
	{
		newstr[i] = (*f)(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
