/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:52:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 08:58:50 by rlucas        ########   odam.nl         */
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
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 4)
		return (BAD_FILETYPE);
	ext = (char *)(str + i - 4);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (BAD_FILETYPE);
	return (0);
}

/*
** Open the file after checking for errors in the supply of arguments.
*/

int			open_file(int argc, char **argv, t_cub *cub)
{
	int			fd;

	if (argc > 3)
		exit(ft_error(MORE_ARG, 0));
	if (argc < 2)
		exit(ft_error(INVALID_ARGUMENT, 0));
	if (check_file(argv[1]) == BAD_FILETYPE)
		exit(ft_error(BAD_FILETYPE, 0));
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) == 0)
			cub->save = 1;
		else
		{
			ft_printf_fd(2, "Error\n'%s' is not a valid argument for cub3D\n",
					argv[2]);
			exit(0);
		}
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(ft_error(INVALID_FILE, 0));
	return (fd);
}
