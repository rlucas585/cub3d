/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ulltoa.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 14:08:45 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:41 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

static int	ft_getlength(unsigned long long n)
{
	int		len;

	len = 0;
	while (n / 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*create_string(int len, unsigned long long n)
{
	char	*result;

	if (len == 0)
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (n == 0)
		result[0] = '0';
	result[len] = '\0';
	len--;
	while (len >= 0)
	{
		result[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (result);
}

char		*ft_ulltoa(unsigned long long n)
{
	char		*result;
	int			len;

	len = ft_getlength(n);
	result = create_string(len, n);
	return (result);
}
