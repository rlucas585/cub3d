/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 11:28:21 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 11:48:39 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <miniprintf.h>

char		*ft_charset(int n, int c)
{
	char		*new;
	int			i;

	i = 0;
	new = (char *)malloc(n + 1);
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = c;
		i++;
	}
	new[n] = '\0';
	return (new);
}

char		*ft_combine(char *s1, char *s2)
{
	char		*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

char		*ft_cutstr(char *str, int n)
{
	char		*new;

	new = ft_substr(str, 0, n);
	free(str);
	return (new);
}

char		*ft_abs_base_itoa(long n, int base)
{
	char	*new;
	int		digits;
	int		i;
	int		x;

	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	digits = 1;
	while (n / ft_power(base, digits))
		digits++;
	new = (char *)malloc(digits + 1);
	if (!new)
		return (NULL);
	while (i < digits)
	{
		x = n / ft_power(base, digits - i - 1) % base;
		if (x > 9)
			new[i] = 'a' + (x - 10);
		else
			new[i] = '0' + x;
		i++;
	}
	new[digits] = '\0';
	return (new);
}
