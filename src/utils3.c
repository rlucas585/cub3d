/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:34:28 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 09:00:38 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

/*
** Bubble sort function for an array of sprites sorted by identity and
** distance.
*/

void		sortsprites(int number, int **order, double **dist)
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

int			close_file(int fd, int errno)
{
	close(fd);
	return (errno);
}

/*
** Get the distance between the start of a string and the first index of the
** string that contains one of a set of characters. Useful for moving through
** strings.
*/

int			travel_to_char(char *line, char *stopatchars)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(stopatchars, line[i]))
			return (i);
		i++;
	}
	return (i);
}

/*
** The inverse of the above function, move through a string until a character
** that is NOT in the specified set is reached.
*/

int			travel_through_char(char *line, char *movethroughchars)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(movethroughchars, line[i]))
			return (i);
		i++;
	}
	return (i);
}

/*
** Free a character string and exit. Used in parse_line() to fit norm.
*/

void		free_exit(int fd, char *line, t_info *info, int linenum)
{
	free(line);
	exit(ft_error(delete_info(close_file(fd, BAD_FORMAT), *info), linenum));
}
