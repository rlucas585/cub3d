/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 16:46:41 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/07 13:58:03 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <stdio.h>
#include <math.h>

/* TO DO: Change the validation of the map to validate_map2(), which should use
 * something like a flood fill algorithm. May need to duplicate the map in order
 * to implement solution in a somewhat simple way. */

static int		only_chars_in_set(char *str, char *validchars)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(validchars, str[i]))
			return (0);
		i++;
	}
	return (1);
}


int				validate_map1(char *line)
{
	if (!only_chars_in_set(line, VALID_MAP_CHARS))
		return (0);
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	if (line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}

int				all_params_present(t_info info)
{
	int		i;

	i = 0;
	if (info.map == NULL)
		return (0);
	if (info.res.x == 0 || info.res.y == 0)
		return (0);
	while (i < 5)
	{
		if (info.texs[i] == NULL)
			return (0);
		i++;
	}
	if (info.f_or_c.x == 0 || info.f_or_c.y == 0)
		return (0);
	return (1);
}

int				copy_map(char **map, char ***newmap)
{
	size_t		i;

	i = 0;
	while (map[i] != NULL)
		i++;
	*newmap = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(*newmap))
		return (0);
	i = 0;
	while (map[i] != NULL)
	{
		(*newmap)[i] = (char *)malloc(ft_strlen(map[i]) + 1);
		if (!(*newmap)[i])
		{
			delete_map(*newmap);
			return (0);
		}
		ft_strlcpy((*newmap)[i], map[i], ft_strlen(map[i]) + 1);
		i++;
	}
	(*newmap)[i] = NULL;
	return (1);
}

int				is_hole(char **map, int pos_y, int pos_x)
{
	if (pos_y - 1 < 0 || pos_x - 1 < 0)
		return (1);
	if (pos_x + 1 >= (int)ft_strlen(map[pos_y]))
		return (1);
	if (pos_y + 1 >= (int)ft_arrlen(map))
		return (1);
	if (pos_x >= (int)ft_strlen(map[pos_y + 1]) ||
			pos_x >= (int)ft_strlen(map[pos_y - 1]))
		return (1);
	return (0);
}

int				flood_fill(char ***map, int pos_y, int pos_x)
{	
	/* int		y; */
	/* int		x; */
    /*  */
	/* y = 0; */
	/* x = 0; */
	/* while ((*map)[y]) */
	/* { */
	/* 	while ((*map)[y][x]) */
	/* 	{ */
	/* 		if ((*map)[y][x] == 'X') */
	/* 			printf("\033[0;31m"); */
	/* 		else */
	/* 			printf("\033[0m"); */
	/* 		printf("%c", (*map)[y][x]); */
	/* 		x++; */
	/* 	} */
	/* 	printf("\n"); */
	/* 	x = 0; */
	/* 	y++; */
	/* }	 */
	if ((*map)[pos_y][pos_x] == '1' || (*map)[pos_y][pos_x] == 'X')
		return (1);
	if ((*map)[pos_y][pos_x] == '0' || (*map)[pos_y][pos_x] == '2')
	{
		if (is_hole(*map, pos_y, pos_x))
			return (0);
		(*map)[pos_y][pos_x] = 'X';
	}
	if (!flood_fill(map, pos_y + 1, pos_x))
		return (0);
	if (!flood_fill(map, pos_y - 1, pos_x))
		return (0);
	if (!flood_fill(map, pos_y, pos_x + 1))
		return (0);
	if (!flood_fill(map, pos_y, pos_x - 1))
		return (0);
	return (1);
}

int				validate_map2(t_info info, t_2d pos_d)
{
	char		**map;
	t_2i		pos;
	int		y;
	int		x;

	y = 0;
	x = 0;
	if(!copy_map(info.map, &map))
		exit(ft_error(delete_info(MEM_FAIL, info), 0));
	pos.x = (int)(floor(pos_d.x));
	pos.y = (int)(floor(pos_d.y));
	if (!flood_fill(&map, pos.y, pos.x))
	{
		free(map);
		return (0);
	}
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'X')
				printf("\033[0;31m");
			else
				printf("\033[0m");
			printf("%c", map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	free(map);
	return (1);
}

void			validate(t_info info)
{
	if (!all_params_present(info))
		exit(ft_error(delete_info(MISSING_PARAM, info), 0));
	if (ft_arrlen(info.map) < 3)
		exit(ft_error(delete_info(TOO_SHORT, info), 0));
	if (ft_strlen(info.map[0]) < 3)
		exit(ft_error(delete_info(TOO_THIN, info), 0));
	if (!only_chars_in_set(info.map[0], "1"))
		exit(ft_error(delete_info(N_S_WALL_ERROR, info), 0));
	if (!only_chars_in_set(info.map[ft_arrlen(info.map) - 1], "1"))
		exit(ft_error(delete_info(N_S_WALL_ERROR, info), 0));
	if (!validate_map2(info, info.pos))
		exit(ft_error(delete_info(NOT_CONTAINED, info), 0));
}
