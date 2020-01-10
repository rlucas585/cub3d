/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 08:57:19 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/31 17:12:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *nptr)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((*(nptr + i) >= 9 && *(nptr + i) <= 13) || *(nptr + i) == 32)
		i++;
	if (*(nptr + i) == '+' || *(nptr + i) == '-')
	{
		if (*(nptr + i) == '-')
			sign = -1;
		i++;
	}
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		result = result * 10 + (*(nptr + i) - 48);
		i++;
	}
	if (sign == 1 && result >= 9223372036854775807)
		return (-1);
	if (sign == -1 && result > 9223372036854775807)
		return (0);
	return ((int)(result * sign));
}
