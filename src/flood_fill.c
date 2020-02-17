/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 14:04:22 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 11:58:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

static int		copy_map(char **map, char ***newmap)
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

static int		is_hole(char **map, int pos_y, int pos_x)
{
	if (pos_y - 1 < 0 || pos_x - 1 < 0)
		return (1);
	if (pos_x + 1 >= (int)(ft_strlen(map[pos_y])))
		return (1);
	if (pos_y + 1 >= (int)(ft_arrlen(map)))
		return (1);
	if (pos_x >= (int)ft_strlen(map[pos_y + 1]) ||
			pos_x >= (int)ft_strlen(map[pos_y - 1]))
		return (1);
	return (0);
}

static int		check_pos(char ***map, int pos_y, int pos_x, int *x)
{
	if ((*map)[pos_y][pos_x] == '1' || (*map)[pos_y][pos_x] == 'X')
		return (1);
	if (pos_y >= (int)(ft_arrlen(*map)) || pos_y < 0)
		return (0);
	if (pos_x >= (int)(ft_strlen((*map)[pos_y])) || pos_x < 0)
		return (0);
	if ((*map)[pos_y][pos_x] == '0' || (*map)[pos_y][pos_x] == '2')
	{
		if (is_hole(*map, pos_y, pos_x))
			return (0);
		(*map)[pos_y][pos_x] = 'X';
	}
	(*x)++;
	if (*x == 80000)
	{
		*x = -1;
		return (0);
	}
	return (2);
}

static int		flood_fill(char ***map, int pos_y, int pos_x, int *x)
{
	int		r;

	r = check_pos(map, pos_y, pos_x, x);
	if (r != 2)
		return (r);
	if (!(flood_fill(map, pos_y + 1, pos_x, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y - 1, pos_x, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y, pos_x + 1, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y, pos_x - 1, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y + 1, pos_x + 1, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y + 1, pos_x - 1, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y - 1, pos_x + 1, x) == 1))
		return (0);
	if (!(flood_fill(map, pos_y - 1, pos_x - 1, x) == 1))
		return (0);
	*x = *x - 1;
	return (1);
}

int				validate_map2(t_info info)
{
	char		**map;
	int			x;
	int			r;

	x = 0;
	if (!copy_map(info.map, &map))
		exit(ft_error(delete_info(MEM_FAIL, info), 0));
	r = flood_fill(&map, (int)floor(info.pos.y), (int)floor(info.pos.x), &x);
	delete_map(map);
	if (x == -1)
		exit(ft_error(delete_info(BIG_MAP, info), 0));
	if (r == 0)
		return (0);
	return (1);
}
