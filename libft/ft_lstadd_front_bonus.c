/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 10:10:46 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 12:31:42 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft.h"

void		ft_lstadd_front(t_list **alst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}
