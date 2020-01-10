/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ltoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 13:35:21 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/19 14:50:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_getlength(long n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len++;
	while (n / 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static char	*create_string(int len, int sign, long n)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	len--;
	while (len >= 0)
	{
		if (len == 0 && sign == 1)
			result[len] = '-';
		else
			result[len] = ft_abs((n % 10)) + 48;
		n /= 10;
		len--;
	}
	return (result);
}

char		*ft_ltoa(long n)
{
	char		*result;
	int			len;
	int			sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_getlength(n);
	result = create_string(len, sign, n);
	return (result);
}
