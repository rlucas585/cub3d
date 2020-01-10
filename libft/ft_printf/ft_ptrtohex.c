/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptrtohex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 09:23:43 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 12:59:45 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>

static char		*add_0x(char *init)
{
	char		*final;
	size_t		len;

	if (!init)
		return (init);
	len = ft_strlen(init);
	final = (char *)malloc(len + 3);
	if (!final)
	{
		free(init);
		return (NULL);
	}
	final[0] = '0';
	final[1] = 'x';
	ft_strlcpy(final + 2, init, len + 1);
	free(init);
	return (final);
}

char			*ptr_to_hex(t_opts *options, va_list arg)
{
	char			*result;
	unsigned long	addr;

	options = arg_width_prcs(options, arg);
	addr = (unsigned long)(va_arg(arg, void *));
	result = ft_ulltox(addr, 'x', 16);
	if (!result)
		return (NULL);
	if (options->prcs != -1)
		result = apply_precision(options->prcs, result);
	if (options->width != 0 && ft_strnstr(options->flags, "0", 3))
	{
		options->width -= 2;
		result = apply_width(options, result);
	}
	result = add_0x(result);
	if (!result)
		return (NULL);
	if (options->width != 0)
		result = apply_width(options, result);
	return (result);
}
