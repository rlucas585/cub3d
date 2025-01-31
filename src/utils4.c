/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 16:34:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/18 14:42:16 by rlucas        ########   odam.nl         */
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
	if (get_row_width(*line) == 0)
		return (0);
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

int			check_file_content(char *line)
{
	size_t			i;

	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
			return (0);
		i++;
	}
	return (1);
}
