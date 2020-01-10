/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 16:31:03 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/29 16:44:16 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == c)
		return ((char *)(str + i));
	else
		return (NULL);
}
