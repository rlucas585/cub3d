/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hex.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 16:12:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 21:06:20 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		ft_is_hex(int c)
{
	return ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'Z'));
}

static int		single_hex(int c)
{
	if (c >= 'a' && c <= 'f')
		return (9 + (c + 1 - 'a'));
	if (c >= 'A' && c <= 'F')
		return (9 + (c + 1 - 'A'));
	return (-1);
}

/*
** MAX_INT in hexadecimal is 7FFFFFF.
** -1 returned in event of error.
*/

int				ft_hex(const char *str)
{
	int			result;
	size_t		len;
	size_t		i;

	i = 0;
	len = ft_strlen(str);
	if (len > 8)
		return (-1);
	if (len == 8 && str[i] > '7')
		return (-1);
	result = 0;
	while (i < len)
	{
		if (ft_is_hex(str[i]))
			result += single_hex(str[i]) * ft_power(16, len - i - 1);
		else
			result += (str[i] - '0') * ft_power(16, len - i - 1);
		i++;
	}
	return (result);
}
