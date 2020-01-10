/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 09:23:33 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 12:59:37 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>

int			ft_printf(char *str, ...)
{
	va_list		args;
	int			i;
	int			x;
	int			printed;

	i = 0;
	printed = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			x = output(str + i, args, &printed);
			if (x == -1)
				return (x);
			i += x;
			printed--;
		}
		else
			ft_putchar_fd(str[i], 1);
		printed++;
		i++;
	}
	va_end(args);
	return (printed);
}
