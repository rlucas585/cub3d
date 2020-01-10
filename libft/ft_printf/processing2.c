/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processing2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 15:54:13 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/19 16:07:15 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

t_opts		*neg_width(t_opts *options)
{
	options->flags = add_flag(options->flags);
	options->width = options->width * -1;
	return (options);
}

void		*free_and_null(void *ptr, void *ptr2)
{
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	return (NULL);
}
