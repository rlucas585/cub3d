/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_get_next_line.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/24 17:21:27 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/27 13:01:51 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	*ft_realloc(char *existing, int newsize)
{
	char		*new;

	new = (char *)malloc(newsize);
	if (!new)
	{
		free(existing);
		return (NULL);
	}
	ft_strlcpy(new, existing, newsize);
	free(existing);
	return (new);
}

static char	*line_from_buf(char **line, char *buf, char **store)
{
	size_t		linelen;

	if (ft_strchr(buf, '\n'))
	{
		linelen = ft_strclen(buf, '\n');
		*store = (char *)malloc(ft_strclen(buf, 0) - linelen);
		if (!(*store))
			return (NULL);
		ft_strlcpy(*store, buf + linelen + 1, ft_strclen(buf, 0) - linelen);
	}
	else
		linelen = ft_strclen(buf, 0);
	if (*line == NULL)
	{
		*line = (char *)malloc(linelen + 1);
		if (*line)
			ft_strlcpy(*line, buf, linelen + 1);
	}
	else
	{
		*line = ft_realloc(*line, ft_strclen(*line, 0) + linelen + 1);
		if (*line)
			ft_strlcat(*line, buf, ft_strclen(*line, 0) + linelen + 1);
	}
	return (*line);
}

static int	line_from_store(char **line, char **store, int fd)
{
	size_t		ll;
	int			more;
	char		*new;

	more = 1;
	ll = (ft_strchr(store[fd], '\n')) ?
		(ft_strclen(store[fd], '\n')) : (ft_strclen(store[fd], 0));
	if (ft_strchr(store[fd], '\n'))
		more = 0;
	*line = (char *)malloc(ll + 1);
	if (!(*line))
		return (-1);
	ft_strlcpy(*line, store[fd], ll + 1);
	if (!more)
	{
		new = ft_substr(store[fd], ll + 1, ft_strclen(store[fd], 0) - ll);
		if (!new)
			return (-1);
	}
	free(store[fd]);
	if (!more)
		store[fd] = new;
	if (more)
		store[fd] = NULL;
	return (more);
}

static int	ret_value(int ret, char *buf, char **line, char **store)
{
	if (buf)
		free(buf);
	if (ret < 0)
	{
		free(*line);
		*line = NULL;
		free(*store);
		return (INVALID_FD_OR_MALLOC_FAIL);
	}
	else if (ret == 0)
		if (*line == NULL)
		{
			*line = (char *)malloc(1);
			if (!(*line))
			{
				free(*store);
				return (MALLOC_FAIL);
			}
			*line[0] = 0;
		}
	if (ret == 0)
		return (END_OF_FILE);
	return (SUCCESSFUL_READ);
}

int			get_next_line(int fd, char **line)
{
	static char		*store[1000];
	char			*out;
	t_gnlopts		opts;

	opts.more = 1;
	opts.ret = 1;
	out = NULL;
	if (store[fd])
		opts.more = line_from_store(&out, store, fd);
	opts.buf = (char *)malloc(BUFFER_SIZE + 1);
	if (opts.more == -1 || !(opts.buf))
		return (ret_value(MALLOC_FAIL, opts.buf, &out, &store[fd]));
	opts.buf[0] = 0;
	while (opts.ret != 0 && !ft_strchr(opts.buf, '\n') && opts.more)
	{
		opts.ret = read(fd, opts.buf, BUFFER_SIZE);
		if (opts.ret >= 0)
			opts.buf[opts.ret] = '\0';
		if (opts.ret > 0)
			out = line_from_buf(&out, opts.buf, &store[fd]);
		if ((opts.ret != 0 && !out) || opts.ret < 0)
			return (ret_value(-1, opts.buf, &out, &store[fd]));
	}
	*line = out;
	return (ret_value(opts.ret, opts.buf, line, &store[fd]));
}
