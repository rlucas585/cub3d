/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _bonus_ft_lstdelone.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 12:01:00 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/07 12:31:37 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	(*del)(lst->content);
	free(lst);
}
