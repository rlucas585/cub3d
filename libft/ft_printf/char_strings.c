/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_strings.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 17:37:15 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 11:15:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

char		*onecharstring(char c)
{
	char		*newstring;

	newstring = (char *)malloc(2);
	if (!newstring)
		return (NULL);
	newstring[0] = c;
	newstring[1] = '\0';
	return (newstring);
}

char		*type_c(t_opts *options, va_list arg)
{
	char		*result;
	char		c;

	c = va_arg(arg, int);
	if (c == '\0')
	{
		result = (char *)malloc(1);
		if (!result)
			return (NULL);
		result[0] = '(';
		options->length = 'w';
		return (apply_width(options, result));
	}
	result = (char *)malloc(2);
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (apply_width(options, result));
}

char		*type_s(t_opts *options, va_list arg)
{
	char	*temp;
	char	*result;
	size_t	len;

	temp = va_arg(arg, char *);
	if (!temp)
		temp = ft_strdup("(null)");
	len = ft_strlen(temp);
	if (options->prcs != -1 && (size_t)options->prcs < len)
		result = (char *)malloc(options->prcs + 1);
	else
		result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	if (options->prcs != -1 && (size_t)options->prcs < len)
		ft_strlcpy(result, temp, options->prcs + 1);
	else
		ft_strlcpy(result, temp, len + 1);
	return (apply_width(options, result));
}

char		*char_string(t_opts *options, va_list arg)
{
	options = arg_width_prcs(options, arg);
	if (options->width != -1 && options->width < 0)
	{
		options->flags = add_flag(options->flags);
		if (!options->flags)
			return (NULL);
		options->width = options->width * -1;
	}
	if (options->type == 'c' || options->type == 'C')
		return (type_c(options, arg));
	else
		return (type_s(options, arg));
}
