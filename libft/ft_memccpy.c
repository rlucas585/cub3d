/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:25:21 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 11:15:22 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char				*ptr1;
	const unsigned char			*ptr2;
	size_t						i;

	i = 0;
	ptr1 = dest;
	ptr2 = src;
	while (n > 0)
	{
		*(ptr1 + i) = *(ptr2 + i);
		i++;
		n--;
		if (*(ptr2 + i) == (unsigned char)c)
		{
			*(ptr1 + i) = *(ptr2 + i);
			return (ptr1 + i + 1);
		}
	}
	return (NULL);
}
