/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 09:35:10 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:22 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int			ft_putstr_with_null(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			ft_putchar_fd(0x00, 1);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
	return (i);
}

int			normal_strings(t_opts *options, va_list arg, int *printed, int sum)
{
	char		*out;

	out = make_string(options, arg);
	if (!out)
		return (-1);
	if (options->length == 'w')
		*printed += ft_putstr_with_null(out);
	else
	{
		ft_putstr_fd(out, 1);
		*printed += ft_strlen(out);
	}
	if (out)
		free(out);
	return (sum);
}

int			free_opts_and_null(t_opts *options)
{
	if (options->flags)
		free(options->flags);
	if (options)
		free(options);
	return (-1);
}

int			output(const char *str, va_list arg, int *printed)
{
	t_opts		*options;
	int			sum;
	int			tmp;

	sum = 0;
	options = parser(str);
	if (!options)
		return (-1);
	if (ft_chkchar_instr(options->type, "dDiuUfFeEgGxXoOscCpaAn"))
	{
		tmp = normal_strings(options, arg, printed, sum + arglength(str));
		sum += tmp;
	}
	else
	{
		options = asterisk_troubles(str, options);
		tmp = crazy_strings(options, arg, printed,
			sum + dist_to_char(str, options->type));
		sum += tmp;
	}
	if (tmp == -1)
		return (free_opts_and_null(options));
	free_opts_and_null(options);
	return (sum);
}
