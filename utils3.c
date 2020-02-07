/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:34:28 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/07 15:07:39 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

/*
** Bubble sort function for an array of sprites sorted by identity and
** distance.
*/

void	sortsprites(int number, int **order, double **dist)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < number)
	{
		while (y < number - x - 1)
		{
			if ((*dist)[y] < (*dist)[y + 1])
			{
				int_swap(&(*order)[y], &(*order)[y + 1]);
				double_swap(&(*dist)[y], &(*dist)[y + 1]);
			}
			y++;
		}
		y = 0;
		x++;
	}
}

/*
** Very small utility function to allow for the closing of a file in the case
** of an error during the parsing stage of the .cub file. Used several times
** in parse_cub.c.
*/

int		close_file(int fd, int errno)
{
	close(fd);
	return (errno);
}
