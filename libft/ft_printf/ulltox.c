/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ulltox.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 14:43:19 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:44 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <printf.h>

unsigned long long	upower(unsigned int number, int power)
{
	unsigned long long	total;

	total = number;
	if (power == 0)
		return (1);
	while (power > 1)
	{
		total = number * total;
		power--;
	}
	return (total);
}

static int			low_up(char c)
{
	if (c == 'X')
		return (55);
	else
		return (87);
}

static	char		*if_empty(int digits, unsigned long long num)
{
	char		*result;

	if (num == 0)
		result = ft_strdup("0");
	else
		result = (char *)malloc(digits + 1);
	return (result);
}

char				*ft_ulltox(unsigned long long num, char c, int base)
{
	int			digits;
	int			i;
	int			loworup;
	char		*result;

	digits = 0;
	i = 0;
	loworup = low_up(c);
	while (upower(base, digits) != 0 && num / upower(base, digits) > 0)
		digits++;
	result = if_empty(digits, num);
	if (!result)
		return (NULL);
	while (digits > 0)
	{
		if ((num / upower(base, digits - 1) % base) <= 9)
			result[i] = ((num / upower(base, digits - 1)) % base) + '0';
		else
			result[i] = ((num / upower(base, digits - 1)) % base) + loworup;
		i++;
		digits--;
	}
	if (num != 0)
		result[i] = '\0';
	return (result);
}
