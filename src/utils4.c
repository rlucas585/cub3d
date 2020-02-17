/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 16:34:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 09:00:48 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <libft.h>

int			create_map(int fd, char **line, int *linenum, t_info *info)
{
	int			ret;

	info->map = row_ptrs(make_row(*line), *info);
	if (!info->map)
		exit(ft_error(delete_info(MEM_FAIL, *info), 0));
	free(*line);
	*line = NULL;
	ret = get_next_line(fd, line);
	(*linenum)++;
	if (!(*line))
		exit(ft_error(delete_info(close_file(fd, MEM_FAIL), *info), 0));
	if (ret == 1 && !validate_map1(*line))
		exit(ft_error(delete_info(close_file(fd, BAD_FORMAT),
						*info), *linenum));
	return (ret);
}

int			check_after_map(int fd, char *line, t_info *info, int *linenum)
{
	while (get_next_line(fd, &line))
	{
		(*linenum)++;
		if (ft_strlen(line) != 0)
			free_exit(fd, line, info, *linenum);
		free(line);
	}
	(*linenum)++;
	if (ft_strlen(line) != 0)
		free_exit(fd, line, info, *linenum);
	free(line);
	return (1);
}
