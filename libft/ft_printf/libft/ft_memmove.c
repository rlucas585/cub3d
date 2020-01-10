/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:25:02 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 12:38:48 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_anyptrlt(const void *p1, const void *p2, size_t n)
{
	const unsigned char	*src;
	const unsigned char	*dst;

	src = p1;
	dst = p2;
	if ((src + n > dst) && (src + n < dst + n))
		return (1);
	else if ((dst + n > src) && (dst + n < src + n))
		return (0);
	return (-1);
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	i = 0;
	ptr1 = dest;
	ptr2 = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (ft_anyptrlt(src, dest, n))
		while (n > 0)
		{
			*(ptr1 + n - 1) = *(ptr2 + n - 1);
			n--;
		}
	else
		while (i < n)
		{
			*(ptr1 + i) = *(ptr2 + i);
			i++;
		}
	return (dest);
}
