/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:46:03 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 10:59:43 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*ptr;
	size_t				i;

	i = 0;
	ptr = b;
	while (i < len)
	{
		*(ptr + i) = c;
		i++;
	}
	return (b);
}
