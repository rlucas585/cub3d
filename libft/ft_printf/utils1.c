/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:15:46 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:48 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

char	*flagchk(const char *str)
{
	int		i;
	int		j;
	char	*flags;

	flags = ft_calloc(6, sizeof(char));
	if (!flags)
		return (NULL);
	j = 0;
	i = 1;
	while (ft_chkchar_instr(str[i], "0+- #") && i < 6)
	{
		if (!ft_chkchar_instr(str[i], flags))
		{
			flags[j] = str[i];
			j++;
		}
		i++;
	}
	return (flags);
}

int		widthchk(const char *str)
{
	size_t			i;
	int				width;

	i = 1;
	width = 0;
	while (!ft_chkchar_instr(str[i], "123456789") && str[i] != '\0')
	{
		if (ft_chkchar_instr(str[i], "*"))
			return (-2);
		if (ft_isalpha(str[i]))
			return (0);
		if (ft_chkchar_instr(str[i], ".dDiufFeEgGxXoscCpaAn%"))
			return (0);
		i++;
	}
	while (ft_chkchar_instr(str[i], "0123456789"))
	{
		width = width * 10 + (str[i] - '0');
		i++;
	}
	return (width);
}

int		prcschk(const char *str)
{
	size_t			i;
	int				prcs;

	i = 1;
	prcs = -1;
	while (!ft_chkchar_instr(str[i], ".") && str[i] != '\0')
	{
		if (ft_chkchar_instr(str[i], "dDiufFeEgGxXoscCpaAn%"))
			return (-1);
		i++;
	}
	if (ft_chkchar_instr(str[i], "."))
	{
		i++;
		prcs = 0;
	}
	if (ft_chkchar_instr(str[i], "*"))
		return (-2);
	while (ft_chkchar_instr(str[i], "0123456789"))
	{
		prcs = prcs * 10 + (str[i] - '0');
		i++;
	}
	return (prcs);
}

char	lenchk(const char *str)
{
	size_t			i;

	i = 1;
	while (!ft_chkchar_instr(str[i], "hlzjt") && str[i] != '\0' &&
		!ft_chkchar_instr(str[i], "dDiufFeEgGxXoscCpaAn%"))
	{
		if (ft_chkchar_instr(str[i], "dDiufFeEgGxXoscCpaAn%"))
			return (0);
		i++;
	}
	if (ft_chkchar_instr(str[i], "hlzjt"))
	{
		if (str[i + 1] == str[i])
			return (str[i] + 1);
		else
			return (str[i]);
	}
	return (0);
}

char	typechk(const char *str)
{
	int			i;

	i = 1;
	while (!ft_chkchar_instr(str[i], "dDiufFeEgGxXoscCpaAn%") && str[i] != '\0')
	{
		if (ft_isalpha(str[i])
				&& !ft_chkchar_instr(str[i], "hlzjt"))
			return (str[i]);
		i++;
	}
	return (str[i]);
}
