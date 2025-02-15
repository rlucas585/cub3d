/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 14:49:52 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 08:53:08 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

/*
** Jumptable of error messages. Line number of .cub file printed if there is a
** formatting error.
*/

int			ft_error(int err, int linenum)
{
	static char	*error_array[128] = {
		[BAD_FORMAT] = ".cub file is incorrectly formatted: ",
		[INVALID_FILE] = "No such file or directory\n",
		[NOT_CONTAINED] = "The map is not correctly contained\n",
		[TOO_SHORT] = "Your map is too short\n",
		[BIG_MAP] = "Your map is too large to be validated\n",
		[NO_MAP] = "There is no map in your .cub file\n",
		[NO_PLAYER] = "There is no player on the map\n",
		[DUP_PLAYERS] = "There are two players on the map\n",
		[MORE_ARG] = "Argument list too long\n",
		[MEM_FAIL] = "Memory failure\n",
		[INVALID_ARGUMENT] = "Not enough arguments\n",
		[BAD_FILETYPE] = "Inappropriate file type or format\n",
		[CONNECTION_FAIL] = "Connection failed\n",
		[MISSING_TEX] = "One or more textures not found\n",
		[MISSING_PARAM] = "One or more params is not present in .cub file\n",
		[DUP_PARAM] = "A parameter has been supplied more than once\n",
		[BMP_FAIL] = "A BMP file could not be created.\n"
	};

	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_array[err], 2);
	if (err == BAD_FORMAT)
		ft_printf_fd(2, "Line %d\n", linenum);
	return (err);
}
