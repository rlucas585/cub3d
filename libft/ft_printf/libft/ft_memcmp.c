/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:08:09 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/29 13:23:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*ptr1;
	const unsigned char		*ptr2;
	int						i;

	ptr1 = s1;
	ptr2 = s2;
	i = 0;
	while (n > 0)
	{
		if (*(ptr1 + i) != *(ptr2 + i))
			return (*(ptr1 + i) - *(ptr2 + i));
		i++;
		n--;
	}
	return (0);
}
