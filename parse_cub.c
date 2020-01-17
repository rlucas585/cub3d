/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:54:27 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 16:44:36 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

/*
** Jumptable to select the correct function based on what info is being
** collected from a .cub file.
*/

t_parsef	route_parsing(char c)
{
	static const t_parsef	route_parsing_table[128] = {
		['R'] = &get_resolution,
		['N'] = &get_texture,
		['X'] = &get_texture,
		['W'] = &get_texture,
		['E'] = &get_texture,
		['S'] = &get_texture,
		['F'] = &get_color,
		['C'] = &get_color,
		['1'] = &get_color,
	};

	return (route_parsing_table[(int)c]);
}

/*
** Read from a .cub file from the first line of the map onwards, and convert the
** map into an array of strings, with each string containing a row of the map
*/

char		**parse_map(int fd, char *line, int linenum)
{
	char		**map;
	int			gnlret;
	size_t		linewidth;

	map = NULL;
	gnlret = 1;
	linewidth = ft_strlen(line);
	while (gnlret)
	{
		map = row_ptrs(make_row(line), map);
		if (!map)
			exit(ft_error(MEM_FAIL, 0));
			/* change to this: exit(ft_error(delete_all(MEM_FAIL, map))); */
		free(line);
		line = NULL;
		gnlret = get_next_line(fd, &line);
		linenum++;
		if (!line)
			exit(ft_error(MEM_FAIL, 0));
		if (gnlret == 1 && !validate_map(line, linewidth))
			exit(ft_error(BAD_FORMAT, linenum));
	}
	return (map);
}

/*
** Reads a line from the .cub file, and directs parsing of information to the
** relevant function. Information is placed in the t_map structure mapinfo.
*/

int			parse_line(int fd, char *line, t_map *mapinfo, int linenum)
{
	t_parsef		funct;

	if (ft_strncmp(line, "", 1) == 0)
		return (0);
	if (ft_strncmp(line, "SO", 2) == 0)
		line[0] = 'X';
	funct = route_parsing(line[0]);
	if (!funct)
		exit(ft_error(BAD_FORMAT, linenum));
	if (line[0] == '1')
	{
		mapinfo->coords = parse_map(fd, line, linenum);
		return (1);
	}
	else if (funct(line, mapinfo) == -1)
		exit(ft_error(BAD_FORMAT, linenum));
	return (0);
}

/*
** Reads through the .cub file, directing each line to parse_line(). Iterates
** through linenum to give linenumber in error messages.
*/

t_map		cub_parser(int fd)
{
	char		*line;
	int			exitno;
	int			linenum;
	t_map		mapinfo;

	linenum = 1;
	exitno = get_next_line(fd, &line);
	while (exitno > 0)
	{
		if (!line)
			break ;
		if (!parse_line(fd, line, &mapinfo, linenum))
			free(line);
		line = NULL;
		linenum++;
		exitno = get_next_line(fd, &line);
	}
	if (exitno < 0)
		exit(ft_error(MEM_FAIL, 0));
	return (mapinfo);
}
