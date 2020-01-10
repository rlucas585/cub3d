/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 13:24:13 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 13:00:27 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int			astcheck(const char *str)
{
	int			i;
	int			star;
	int			on_prcs;

	i = 1;
	star = 0;
	on_prcs = 0;
	while (!ft_chkchar_instr(str[i], "diufFeEgGxXoscCpaAn%"))
	{
		if (ft_chkchar_instr(str[i], "*") && !on_prcs)
			star = 1;
		else if (ft_chkchar_instr(str[i], "*") && on_prcs)
			star = 2;
		if (ft_chkchar_instr(str[i], "."))
			on_prcs = 1;
		i++;
	}
	return (star);
}

t_opts		*parser(const char *str)
{
	t_opts		*options;

	options = malloc(sizeof(t_opts));
	if (!options)
		return (NULL);
	options->flags = flagchk(str);
	if (!options->flags)
		return (NULL);
	options->width = widthchk(str);
	options->prcs = prcschk(str);
	options->length = lenchk(str);
	options->type = typechk(str);
	return (options);
}
