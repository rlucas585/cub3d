/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hexprocessing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 14:13:57 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 11:10:22 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int			check_hex(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_chkchar_instr(str[i], "abcdefABCDEF123456789"))
			return (1);
		i++;
	}
	return (0);
}

char		*zeroed_processing(t_opts *options, char *result)
{
	if (ft_strnstr(options->flags, "#", 6))
	{
		if (options->width > (int)ft_strlen(result) + 2 &&
				options->prcs == -1)
		{
			options->width -= 2;
			result = apply_width(options, result);
			result = hashflags(options, result);
		}
		else
		{
			result = hashflags(options, result);
			result = apply_width(options, result);
		}
	}
	else
		result = apply_width(options, result);
	return (result);
}

char		*hex_processing(t_opts *options, char *result)
{
	if (options->prcs != -1)
		result = apply_precision(options->prcs, result);
	if (options->type == 'o' || options->type == 'O')
	{
		if (ft_strnstr(options->flags, "#", 6) && result[0] != '0')
			result = prepend(result, "0");
		return (apply_width(options, result));
	}
	else if (!check_hex(result))
		return (apply_width(options, result));
	else if (ft_strnstr(options->flags, "0", 6))
		result = zeroed_processing(options, result);
	else
	{
		if (ft_strnstr(options->flags, "#", 6))
			result = hashflags(options, result);
		result = apply_width(options, result);
	}
	return (result);
}

char		*hashflags(t_opts *options, char *result)
{
	if (!result)
		return (NULL);
	if (options->type == 'x')
		result = prepend(result, "0x");
	else if (options->type == 'X')
		result = prepend(result, "0X");
	return (result);
}
