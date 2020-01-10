/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 16:41:20 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 17:19:17 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *str, int c)
{
	int			i;
	char		*ptr;

	i = 0;
	ptr = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			ptr = (char *)(str + i);
		i++;
	}
	if (c == 0)
		return ((char *)(str + i));
	else
		return (ptr);
}
