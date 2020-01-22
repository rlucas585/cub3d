/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:24:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 10:51:06 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	ptr1 = dest;
	ptr2 = src;
	while (n > 0)
	{
		*(ptr1 + i) = *(ptr2 + i);
		i++;
		n--;
	}
	return (dest);
}
