/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/15 18:36:23 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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

int			open_file(int argc, char **argv)
{
	int			fd;

	if (argc < 2)
	{
		ft_putstr_fd("Not enough arguments\n", 2);
		exit(INVALID_ARGUMENT);
	}
	if (check_file(argv[1]))
	{
		ft_putstr_fd(strerror(BAD_FILETYPE), 2);
		ft_putchar_fd('\n', 2);
		exit (BAD_FILETYPE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(INVALID_FILE), 2);
		ft_putchar_fd('\n', 2);
		exit(INVALID_FILE);
	}
	return (fd);
}

t_map		parser(int fd)
{

}

int			main(int argc, char **argv)
{
	t_map		map;

	t_map = parser(open_file(argc, argv));
	return (0);
}
