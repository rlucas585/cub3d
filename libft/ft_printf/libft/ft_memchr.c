/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:21:37 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 11:53:07 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	int					i;
	const unsigned char	*ptr1;

	i = 0;
	ptr1 = s;
	while (n > 0)
	{
		if (*(ptr1 + i) == (unsigned char)c)
		{
			return ((void *)(ptr1 + i));
		}
		i++;
		n--;
	}
	return (NULL);
}
