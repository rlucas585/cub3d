/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/16 18:12:47 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <fcntl.h>

static int	check_file(const char *str)
{
	char		*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		return (BAD_FILETYPE);
	if (ft_strncmp(ext, ".cub", 5) != 0)
		return (BAD_FILETYPE);
	return (0);
}

int			ft_error(int err, int linenum)
{
	static char	*error_array[128] = {
		[BAD_FORMAT] = ".cub file is incorrectly formatted: \n"
		[INVALID_FILE] = "No such file or directory\n",
		[MORE_ARG] = "Argument list too long\n",
		[MEM_FAIL] = "Out of memory\n",
		[INVALID_ARGUMENT] = "Not enough arguments\n",
		[BAD_FILETYPE] = "Inappropriate file type or format\n",
	};
	
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_array[err], 2);
	if (linenum != 0)
	{
		/* Create ft_printf_fd for this section */
		ft_putstr_fd("Line ");
	}
	return (err);
}

int			open_file(int argc, char **argv)
{
	int			fd;

	if (argc > 3)
		exit (ft_error(MORE_ARG, 0));
	if (argc < 2)
		exit(ft_error(INVALID_ARGUMENT, 0));
	if (check_file(argv[1]))
		exit(ft_error(BAD_FILETYPE, 0));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(ft_error(INVALID_FILE, 0));
	return (fd);
}

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
		['1'] = &get_map,
	};

	return (route_parsing_table[(int)c]);
}

int			parse_line(int fd, char *line, t_map *mapinfo, int linenum)
{
	t_parsef		funct;

	if (ft_strncmp(line, "", 1) == 0)
		return (0);
	if (ft_strncmp(line, "SO", 2) == 0)
		line[0] = 'X';
	funct = route_parsing(line[0]);
	if (!funct)
		return (ft_error(BAD_FORMAT, linenum));
	if(funct(line, mapinfo) == -1)
		return (ft_error(BAD_FORMAT, linenum));
	return (1);
}

t_map		parser(int fd)
{
	char		*line;
	int			exit;
	int			linenum;
	t_map		mapinfo;

	linenum = 1;
	exit = get_next_line(fd, &line);
	while (exit != -1 && line)
	{
		if (!line)
			break ;
		parse_line(fd, line, &mapinfo, linenum);
		if (line)
		{
			free(line);
			line = NULL;
		}
		linenum++;
		exit = get_next_line(fd, &line);
	}
	if (exit < 0)
	{
		ft_putstr_fd("Out of memory\n", 2);
		exit(MEM_FAIL);
	}
}

int			main(int argc, char **argv)
{
	parser(open_file(argc, argv));
	return (0);
}
