/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 11:29:54 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 11:36:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			get_width(const char *str)
{
	int			i;
	int			total;

	i = 1;
	total = 0;
	if (!ft_strchr("0123456789", str[i]))
		return (-1);
	while (ft_strchr("0123456789", str[i]))
	{
		total = total * 10 + (str[i] - '0');
		i++;
	}
	return (total);
}

int			get_prec(const char *str)
{
	int			i;
	int			total;

	i = 1;
	total = 0;
	while (str[i] && !ft_strchr(".", str[i]) && !ft_isalpha(str[i]))
		i++;
	if (str[i] != '.')
		return (-1);
	i++;
	while (str[i] && ft_strchr("0123456789", str[i]))
	{
		total = total * 10 + (str[i] - '0');
		i++;
	}
	return (total);
}

int			get_type(const char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_isalpha(str[i]))
		i++;
	return (str[i]);
}
