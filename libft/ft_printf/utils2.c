/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 16:20:46 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:51 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int			ft_chkchar_instr(char c, const char *s1)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (c == s1[i])
			return (1);
		i++;
	}
	return (0);
}

size_t		ignore_sign_len(const char *stringnum)
{
	size_t			i;

	i = 0;
	while (stringnum[i] != '\0')
		i++;
	if (stringnum[0] == '-' || stringnum[0] == '+' || stringnum[0] == ' ')
		i--;
	return (i);
}

int			arglength(const char *str)
{
	int			i;

	i = 1;
	while (!ft_chkchar_instr(str[i], "dDiuUfFeEgGxXoOscCpaAn%")
		&& str[i] != '\0')
		i++;
	return (i);
}

char		*add_flag(char *flags)
{
	char		*newflags;
	int			i;

	i = ft_strlen(flags);
	if (ft_strnstr(flags, "-", 3))
		return (flags);
	else
	{
		newflags = (char *)ft_calloc(i + 2, sizeof(char));
		if (!newflags)
		{
			free(flags);
			return (NULL);
		}
		ft_strlcpy(newflags, flags, i);
		newflags[i] = '-';
		newflags[i + 1] = '\0';
	}
	if (flags)
		free(flags);
	return (newflags);
}

t_opts		*arg_width_prcs(t_opts *options, va_list arg)
{
	if (options->width == -2)
		options->width = va_arg(arg, int);
	if (options->prcs == -2)
		options->prcs = va_arg(arg, int);
	return (options);
}
