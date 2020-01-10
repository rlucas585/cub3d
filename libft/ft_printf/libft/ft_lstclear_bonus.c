/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _bonus_ft_lstclear.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 12:05:08 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/06 09:29:22 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list			*current;
	t_list			*next;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}
