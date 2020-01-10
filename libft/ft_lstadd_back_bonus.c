/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 10:10:35 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/06 09:29:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*current;

	if (new == NULL)
		return ;
	if (*alst == NULL)
	{
		ft_lstadd_front(alst, new);
		return ;
	}
	current = *alst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
