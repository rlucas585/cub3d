/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 08:58:26 by rlucas        #+#    #+#                 */
/*   Updated: 2019/10/30 09:29:13 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	else
		return (0);
}
