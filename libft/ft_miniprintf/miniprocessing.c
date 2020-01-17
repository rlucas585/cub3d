/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 11:31:51 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 11:46:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <miniprintf.h>

static void	*free_return(char *str)
{
	free(str);
	return (NULL);
}

char		*num_processing(t_miniprint opts, char *pre, int sign)
{
	char		*tempstr;

	if (opts.prec > (int)ft_strlen(pre) && opts.prec != -1)
	{
		tempstr = ft_charset(opts.prec - (int)ft_strlen(pre), '0');
		if (!tempstr)
			return (free_return(pre));
		pre = ft_combine(tempstr, pre);
		if (!pre)
			return (NULL);
	}
	if (sign == 1)
		pre = ft_combine(ft_strdup("-"), pre);
	if (!pre)
		return (NULL);
	if (opts.width > (int)ft_strlen(pre) && opts.width != -1)
	{
		tempstr = ft_charset(opts.width - (int)ft_strlen(pre), ' ');
		if (!tempstr)
			return (free_return(pre));
		pre = ft_combine(tempstr, pre);
		if (!pre)
			return (NULL);
	}
	return (pre);
}

char		*str_processing(t_miniprint opts, char *pre)
{
	char		*tempstr;

	if (opts.prec < (int)ft_strlen(pre) && opts.prec != -1)
		pre = ft_cutstr(pre, opts.prec);
	if (!pre)
		return (NULL);
	if (opts.width > (int)ft_strlen(pre) && opts.width != -1)
	{
		tempstr = ft_charset(opts.width - ft_strlen(pre), ' ');
		if (!tempstr)
		{
			free(pre);
			return (NULL);
		}
		pre = ft_combine(tempstr, pre);
		if (!pre)
			return (NULL);
	}
	return (pre);
}
