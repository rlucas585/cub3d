/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 12:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:21:56 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

#include <stdio.h>
/* delete this later */

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
** spaces.
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

size_t			ft_arrlen(char **array)
{
	size_t		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}


/*
** Print the mapinfo information. Should be removed from directory prior to
** submission of project, only for troubleshooting.
*/

void		print_mapinfo(t_info info)
{
	int			y;

	y = 0;
	ft_printf("Resolution = %dx%d\n", info.res.x, info.res.y);
	while (y < 5)
	{
		ft_printf("textures: %d = %s\n", y, info.texs[y]);
		y++;
	}
	y = 0;
	while (info.map[y])
	{
		ft_printf("%s\n", info.map[y]);
		y++;
	}
}

void		print_playerinfo(t_info info)
{
	printf("Player coordinates: X = %f Y = %f dirX = %f dirY = %f angle=%f\n",
			info.pos.x, info.pos.y, sin(to_radians(info.dir)),
			-cos(to_radians(info.dir)), info.dir);
}

void		print_spriteinfo(t_info info)
{
	printf("Number of sprites: %d\n", info.spritenum);
}

void		print_gameinfo(t_info info)
{
	print_mapinfo(info);
	print_playerinfo(info);
	print_spriteinfo(info);
}

double		to_degrees(double radians)
{
	return ((180 / M_PI) * radians);
}

double		to_radians(double degrees)
{
	return ((degrees * M_PI) / 180);
}
