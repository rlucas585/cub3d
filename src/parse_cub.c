/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:54:27 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/18 13:05:53 by rlucas        ########   odam.nl         */
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
		['F'] = &get_floor_ceiling,
		['C'] = &get_floor_ceiling,
		['1'] = &get_color,
		['0'] = &get_color,
	};

	return (route_parsing_table[(int)c]);
}

/*
** Read from a .cub file from the first line of the map onwards, and convert the
** map into an array of strings, with each string containing a row of the map
*/

void		parse_map(int fd, char *line, int *linenum, t_info *info)
{
	int			gnlret;

	info->map = NULL;
	gnlret = 1;
	while (gnlret)
	{
		gnlret = create_map(fd, &line, linenum, info);
		if (ft_strlen(line) == 0)
			break ;
	}
	if (!validate_map1(line))
		exit(ft_error(delete_info(close_file(fd, BAD_FORMAT),
						*info), *linenum));
	if (get_row_width(line) != 0)
		info->map = row_ptrs(make_row(line), *info);
	else if (ft_strlen(line) != 0)
		exit(ft_error(delete_info(close_file(fd, BAD_FORMAT),
						*info), *linenum));
	if (!info->map)
		exit(ft_error(delete_info(close_file(fd, MEM_FAIL), *info), 0));
	free(line);
}

/*
** Reads a line from the .cub file, and directs parsing of information to the
** relevant function. Information is placed in the t_map structure mapinfo.
*/

int			parse_line(int fd, char *line, t_info *info, int *linenum)
{
	t_parsef		funct;
	size_t			i;

	i = 0;
	i += travel_through_char(line + i, " ");
	if (line[i] == '\0' && ft_strlen(line) == 0)
		return (0);
	if (ft_strncmp(line + i, "SO", 2) == 0)
		line[i] = 'X';
	funct = route_parsing(line[i]);
	if (!funct)
		free_exit(fd, line, info, *linenum);
	if (line[i] == '1' || line[i] == '0')
	{
		parse_map(fd, line, linenum, info);
		return (check_after_map(fd, line, info, linenum));
	}
	else if (funct(line + i, info) == -1)
		free_exit(fd, line, info, *linenum);
	return (0);
}

/*
** Reads through the .cub file, directing each line to parse_line(). Iterates
** through linenum to give linenumber in error messages.
*/

t_info		cub_parser(int fd)
{
	char		*line;
	int			exitno;
	int			linenum;
	t_info		mapinfo;

	linenum = 1;
	exitno = get_next_line(fd, &line);
	if (exitno <= 0)
		exit(ft_error(close_file(fd, BAD_FILETYPE), 0));
	while (exitno > 0)
	{
		if (!line)
			break ;
		if (!parse_line(fd, line, &mapinfo, &linenum))
			free(line);
		line = NULL;
		linenum++;
		exitno = get_next_line(fd, &line);
	}
	if (line)
		free(line);
	if (exitno < 0)
		exit(ft_error(close_file(fd, MEM_FAIL), 0));
	close(fd);
	return (mapinfo);
}
