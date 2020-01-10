/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 10:11:19 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/06 09:30:03 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *lst)
{
	t_list		*current;
	int			size;

	size = 0;
	current = lst;
	if (current == NULL)
		return (size);
	while (current->next != NULL)
	{
		size++;
		current = current->next;
	}
	size++;
	return (size);
}
