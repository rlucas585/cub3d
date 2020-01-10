/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _bonus_ft_lstiter.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 13:11:09 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/06 09:29:35 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list			*current;

	if (lst == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		(*f)(current->content);
		current = current->next;
	}
}
