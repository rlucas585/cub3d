/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 17:06:26 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

char		*pad_with_zeros(char *str, size_t init, int prcs)
{
	char		*new;
	size_t		i;
	size_t		j;
	int			slim;

	i = 0;
	j = prcs;
	slim = (ft_strlen(str) > init);
	new = (char *)ft_calloc(((int)ft_strlen(str) + prcs - init) + 1, 1);
	if (!new)
		return (free_and_null(str, str));
	if (slim)
	{
		new[i] = str[i];
		i++;
	}
	while (j > init)
	{
		new[i] = '0';
		i++;
		j--;
	}
	ft_strlcat(new, str + slim, (int)ft_strlen(str) + prcs - init + 1);
	free(str);
	return (new);
}

char		*apply_precision(size_t prcs, char *string)
{
	size_t			digits;
	char			c;

	if (!string)
		return (string);
	digits = ignore_sign_len(string);
	c = string[0];
	if (prcs == 0 && ft_atoi(string) == 0 &&
		!ft_chkchar_instr(string[0], "abcdefABCDEF"))
	{
		free(string);
		if (c == '-' || c == ' ' || c == '+')
			string = onecharstring(c);
		else
			string = ft_strdup("");
	}
	else if (prcs == 0 || prcs <= ignore_sign_len(string))
		return (string);
	else
		string = pad_with_zeros(string, digits, prcs);
	return (string);
}

char		*left_align(int width, char *string)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	new = (char *)ft_calloc(width + 1, 1);
	if (!new || !string)
		return (free_and_null(string, new));
	len = ft_strlen(string);
	while (i < len)
	{
		new[i] = string[i];
		i++;
		width--;
	}
	while (width > 0)
	{
		new[i] = ' ';
		i++;
		width--;
	}
	new[i] = '\0';
	free(string);
	string = new;
	return (string);
}

char		*right_align(int width, char *string)
{
	int		i;
	int		len_j;
	char	*new;

	i = 0;
	new = (char *)ft_calloc(width + 1, 1);
	if (!new || !string)
		return (free_and_null(new, string));
	len_j = ft_strlen(string);
	while (i < width - len_j)
	{
		new[i] = ' ';
		i++;
	}
	len_j = 0;
	while (i < width + 1)
	{
		new[i] = string[len_j];
		i++;
		len_j++;
	}
	new[i] = '\0';
	free(string);
	string = new;
	return (new);
}

char		*apply_width(t_opts *options, char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (NULL);
	if (options->width < 0)
		options = neg_width(options);
	if (options->width <= (int)ft_strlen(str))
		return (str);
	else if (ft_strnstr(options->flags, "-", 6))
		str = left_align(options->width, str);
	else if (ft_strnstr(options->flags, "0", 6) &&
			ft_chkchar_instr(options->type, "sc"))
		str = pad_with_zeros(str, ft_strlen(str), options->width);
	else if (ft_strnstr(options->flags, "0", 6) && options->prcs == -1)
	{
		if (str[i] != '-' && str[i] != '+' && str[i] != ' ')
			str = pad_with_zeros(str, ignore_sign_len(str), options->width);
		else
			str = pad_with_zeros(str, ignore_sign_len(str), options->width - 1);
	}
	else
		str = right_align(options->width, str);
	return (str);
}
