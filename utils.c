/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 12:48:38 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/20 16:23:26 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

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

char		**row_ptrs(char *newrow, t_map map)
{
	int			i;
	char		**ptr_array;

	i = 0;
	if (!newrow)
		exit(ft_error(delete_info(MEM_FAIL, map), 0));
	while (map.coords != NULL && map.coords[i] != NULL)
		i++;
	ptr_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!ptr_array)
		return (NULL);
	i = 0;
	while (map.coords != NULL && map.coords[i] != NULL)
	{
		ptr_array[i] = map.coords[i];
		i++;
	}
	ptr_array[i] = newrow;
	ptr_array[i + 1] = NULL;
	if (map.coords)
		free(map.coords);
	return (ptr_array);
}

/*
** Print the mapinfo information. Should be removed from directory prior to
** submission of project, only for troubleshooting.
*/

void		print_mapinfo(t_map mapinfo)
{
	int			x;

	x = 0;
	ft_printf("Resolution = %dx%d\n", mapinfo.res[0], mapinfo.res[1]);
	while (x < 5)
	{
		ft_printf("textures: %d = %s\n", x, mapinfo.textures[x]);
		x++;
	}
	x = 0;
	while (mapinfo.coords[x])
	{
		ft_printf("%s\n", mapinfo.coords[x]);
		x++;
	}
}

void		print_playerinfo(t_player player)
{
	printf("Player coordinates: X = %d Y = %d dirX = %f dirY = %f\n",
			(int)player.location[X], (int)player.location[Y], player.dir[X],
			player.dir[Y]);
}

void		print_gameinfo(t_game game)
{
	print_mapinfo(game.map);
	print_playerinfo(game.player);
}