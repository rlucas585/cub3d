/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _bonus_ft_lstmap.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 13:23:04 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/07 15:13:02 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*temp;
	t_list			*copy_head;
	t_list			*copy_elem;
	void			*value;

	temp = lst;
	while (temp != NULL)
	{
		value = f(temp->content);
		copy_elem = ft_lstnew(value);
		if (!copy_elem)
		{
			ft_lstclear(&copy_head, del);
			return (NULL);
		}
		if (temp == lst)
			copy_head = copy_elem;
		else
			ft_lstadd_back(&copy_head, copy_elem);
		temp = temp->next;
	}
	return (copy_head);
}
