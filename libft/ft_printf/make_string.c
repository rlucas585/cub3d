/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_string.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 11:01:30 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:14 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

char		*make_string(t_opts *options, va_list arg)
{
	char		*result;

	result = NULL;
	if (ft_chkchar_instr(options->type, "dDiuUoOxX"))
		result = int_string(options, arg);
	else if (options->type == 'p')
		result = ptr_to_hex(options, arg);
	else if (ft_chkchar_instr(options->type, "scC"))
		result = char_string(options, arg);
	return (result);
}
