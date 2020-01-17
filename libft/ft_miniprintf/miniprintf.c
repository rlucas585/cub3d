/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniprintf3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 16:26:24 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 11:49:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <miniprintf.h>
#include <stdarg.h>

static int	arglength(const char *str)
{
	int			i;

	i = 1;
	while (str[i] && !ft_isalpha(str[i]))
		i++;
	if (str[i] == 0)
		return (i);
	return (i + 1);
}

static int	print_num(int fd, t_miniprint opts, int base, long n)
{
	char		*output;
	int			sign;
	int			len;

	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	output = ft_abs_base_itoa(n, base);
	if (!output)
		return (-1);
	output = num_processing(opts, output, sign);
	if (!output)
		return (-1);
	ft_putstr_fd(output, fd);
	len = ft_strlen(output);
	free(output);
	return (len);
}

static int	print_str(int fd, t_miniprint opts, char *str)
{
	int			len;

	if (!str)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (!str)
		return (-1);
	str = str_processing(opts, str);
	if (!str)
		return (-1);
	ft_putstr_fd(str, fd);
	len = ft_strlen(str);
	free(str);
	return (len);
}

static int	print_arg(int fd, const char *str, va_list arg)
{
	t_miniprint	opts;

	opts.width = get_width(str);
	opts.prec = get_prec(str);
	if (get_type(str) == 'd')
		return (print_num(fd, opts, 10, va_arg(arg, int)));
	else if (get_type(str) == 'x')
		return (print_num(fd, opts, 16, va_arg(arg, unsigned int)));
	else if (get_type(str) == 's')
		return (print_str(fd, opts, va_arg(arg, char *)));
	return (-1);
}

int			ft_printf_fd(int fd, const char *str, ...)
{
	va_list		args;
	int			i;
	int			count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += print_arg(fd, str + i, args);
			i += arglength(str + i) - 1;
			if (count == -1)
			{
				ft_putstr_fd("error\n", fd);
				return (-1);
			}
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
