/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   crazy_strings.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 15:34:34 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 12:59:07 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int			dist_to_char(const char *str, char c)
{
	int		i;

	i = 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (i - 1);
	return (i);
}

t_opts		*asterisk_troubles(const char *str, t_opts *options)
{
	if (astcheck(str) == 1)
		options = no_ast_parse(str, options, 0);
	else if (astcheck(str) == 2)
		options = no_ast_parse(str, options, 1);
	return (options);
}

t_opts		*no_ast_parse(const char *str, t_opts *options, int prcs)
{
	size_t		i;

	i = 1;
	while (!ft_chkchar_instr(str[i], "123456789") && str[i] != '\0')
	{
		if (ft_isalpha(str[i]) ||
			ft_chkchar_instr(str[i], "dDiufFeEgGxXoscCpaAn%"))
			return (options);
		if (ft_chkchar_instr(str[i], ".") && prcs == 1)
			break ;
		i++;
	}
	if (prcs == 1)
		while (!ft_chkchar_instr(str[i], "."))
			i++;
	if (prcs == 1)
		return (no_ast_parse(str + i, options, 0));
	while (ft_chkchar_instr(str[i], "0123456789"))
	{
		options->width = 0;
		options->width = options->width * 10 + (str[i] - '0');
		i++;
	}
	return (options);
}

int			crazy_strings(t_opts *options, va_list arg, int *printed, int sum)
{
	char		*result;

	options = arg_width_prcs(options, arg);
	result = (char *)malloc(2);
	if (!result)
		return (-1);
	result[0] = options->type;
	result[1] = '\0';
	if (options->width != 0 && ft_strnstr(options->flags, "0", 6) &&
		!ft_strnstr(options->flags, "-", 6))
		result = pad_with_zeros(result, ft_strlen(result), options->width);
	else if (options->width != 0)
		result = apply_width(options, result);
	if (!result)
		return (-1);
	ft_putstr_fd(result, 1);
	*printed += ft_strlen(result);
	free(result);
	return (sum);
}
