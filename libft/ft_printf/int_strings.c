/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   int_strings.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 17:22:01 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:04 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

char		*prepend(char *old, char *c)
{
	char	*result;
	size_t	newlen;

	if (!old)
		return (old);
	newlen = ft_strlen(old) + ft_strlen(c);
	result = (char *)malloc(newlen + 1);
	if (!result)
	{
		free(old);
		return (result);
	}
	ft_strlcpy(result, c, ft_strlen(c) + 1);
	ft_strlcat(result, old, newlen + 1);
	free(old);
	return (result);
}

char		*type_i_d(t_opts *options, va_list arg)
{
	char		*result;

	result = NULL;
	if (options->type == 'D')
		result = ft_lltoa(va_arg(arg, long long));
	else if (options->length == 'h')
		result = ft_itoa((short)va_arg(arg, int));
	else if (options->length == 'i')
		result = ft_itoa((char)va_arg(arg, int));
	else if (options->length == 'l')
		result = ft_ltoa(va_arg(arg, long));
	else if (options->length == 'z')
		result = ft_ltoa(va_arg(arg, size_t));
	else if (options->length == 'm' || options->length == 'j')
		result = ft_lltoa(va_arg(arg, long long));
	else
		result = ft_itoa(va_arg(arg, int));
	if (ft_strnstr(options->flags, "+", 6) && result[0] != '-')
		result = prepend(result, "+");
	else if (ft_strnstr(options->flags, " ", 6) && result[0] != '-')
		result = prepend(result, " ");
	return (result);
}

char		*type_u_o_x(t_opts *options, va_list arg)
{
	unsigned long long	n;
	char				*result;

	if (ft_chkchar_instr(options->length, "mjt"))
		n = va_arg(arg, unsigned long long);
	else if (options->length == 'h')
		n = (unsigned short)(va_arg(arg, int));
	else if (options->length == 'i')
		n = (unsigned char)(va_arg(arg, int));
	else if (options->length == 'l')
		n = va_arg(arg, unsigned long);
	else if (options->length == 'z')
		n = va_arg(arg, size_t);
	else
		n = va_arg(arg, unsigned int);
	result = NULL;
	if (options->type == 'u' || options->type == 'U')
		result = ft_ulltoa(n);
	else if (options->type == 'o' || options->type == 'O')
		result = ft_ulltox(n, options->type, 8);
	else if (options->type == 'x' || options->type == 'X')
		result = ft_ulltox(n, options->type, 16);
	return (result);
}

char		*int_string(t_opts *options, va_list arg)
{
	char		*result;

	options = arg_width_prcs(options, arg);
	result = NULL;
	if (ft_chkchar_instr(options->type, "diD"))
		result = type_i_d(options, arg);
	else if (ft_chkchar_instr(options->type, "uUoOxX"))
		result = type_u_o_x(options, arg);
	if (!result)
		return (NULL);
	if (ft_chkchar_instr(options->type, "oOxX"))
		return (hex_processing(options, result));
	if (options->prcs != -1)
		result = apply_precision(options->prcs, result);
	if (options->width != 0)
		result = apply_width(options, result);
	return (result);
}
