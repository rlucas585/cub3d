/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 09:58:53 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 14:26:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	char		*ptr;
	void		*vp;

	vp = malloc(sizeof(char) * count * size);
	if (!vp)
		return (NULL);
	ptr = (char *)vp;
	ft_bzero(ptr, count * size);
	return (vp);
}
