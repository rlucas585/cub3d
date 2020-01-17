/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:52:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 15:21:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <fcntl.h>

/*
** Check that the file has a .cub extension, return error if not.
*/

int			check_file(const char *str)
{
	char		*ext;

	ext = ft_strrchr(str, '.');
	if (!ext)
		return (BAD_FILETYPE);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (BAD_FILETYPE);
	return (0);
}

/*
** Open the file after checking for errors in the supply of arguments.
*/

int			open_file(int argc, char **argv)
{
	int			fd;

	if (argc > 3)
		exit(ft_error(MORE_ARG, 0));
	if (argc < 2)
		exit(ft_error(INVALID_ARGUMENT, 0));
	if (check_file(argv[1]))
		exit(ft_error(BAD_FILETYPE, 0));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(ft_error(INVALID_FILE, 0));
	return (fd);
}
