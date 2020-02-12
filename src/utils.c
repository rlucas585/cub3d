/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 12:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/12 15:39:00 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

/*
** Utility functions for the cub3d project
*/

static int	get_row_width(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isalnum(line[i]))
			j++;
		i++;
	}
	return (j);
}

/*
** Used in get_map, makes a string from a single line by cutting out all the
** spaces. UPDATE: Spaces are no longer considered valid input, so the if
** statement with ft_isalnum() is somewhat redundant now. UPDATE2: Never mind,
** spaces are valid again.
*/

char		*make_row(char *line)
{
	int			i;
	int			j;
	char		*row;

	i = 0;
	j = 0;
	row = (char *)malloc(get_row_width(line) + 1);
	if (!row)
		return (NULL);
	while (line[i])
	{
		if (ft_isalnum(line[i]))
		{
			row[j] = line[i];
			j++;
		}
		i++;
	}
	row[j] = '\0';
	return (row);
}

/*
** Takes an array of pointers to strings, allocates a new array of pointers to
** strings with one additional space, copies the pointer values into the new
** array and then adds one new one at the end.
*/

char		**row_ptrs(char *newrow, t_info info)
{
	int			i;
	char		**ptr_array;

	i = 0;
	if (!newrow)
		exit(ft_error(delete_info(MEM_FAIL, info), 0));
	while (info.map != NULL && info.map[i] != NULL)
		i++;
	ptr_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!ptr_array)
		return (NULL);
	i = 0;
	while (info.map != NULL && info.map[i] != NULL)
	{
		ptr_array[i] = info.map[i];
		i++;
	}
	ptr_array[i] = newrow;
	ptr_array[i + 1] = NULL;
	if (info.map)
		free(info.map);
	return (ptr_array);
}

/*
** Get the length of a 2d array of strings.
*/

size_t		ft_arrlen(char **array)
{
	size_t		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

/*
** ft_strchr, except it returns the number of occurrences of a character in a
** string.
*/

int			numstrchr(char *str, int c)
{
	size_t		i;
	int			total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == c)
			total++;
		i++;
	}
	return (total);
}
