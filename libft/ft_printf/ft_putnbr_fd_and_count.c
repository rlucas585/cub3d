/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd_and_count.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 09:24:48 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/20 12:59:55 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_putnbr_fd_and_count(int n, int fd, int *printed)
{
	unsigned int		nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		(*printed)++;
		nb = n * -1;
	}
	else
		nb = n;
	if (nb >= 10)
		ft_putnbr_fd_and_count(nb / 10, fd, printed);
	ft_putchar_fd((nb % 10) + '0', fd);
	(*printed)++;
}
