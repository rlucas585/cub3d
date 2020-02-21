/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_threads_2_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <ryanl585codam@gmail.com>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 11:08:40 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/21 11:16:37 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

void	*s_thread4(void *value)
{
	t_s_thread	*data;
	int			x;
	int			y;

	data = (t_s_thread *)value;
	x = data->sray.draw_start.x / 2;
	while (x <= data->sray.draw_start.x + 5 * (data->sray.draw_end.x -
				data->sray.draw_start.x) / 8 && x < data->cub->info.res.x)
	{
		y = init_scast(data->cub, &data->sray, x);
		if (data->sray.transform.y > 0 && x >= 0 && x <
				data->cub->info.res.x &&
				data->sray.transform.y < data->z_buffer[x])
		{
			while (y < data->sray.draw_end.y)
			{
				put_sprite_pixel(data->cub, y, x, &data->sray);
				y++;
			}
		}
		x++;
	}
	return (NULL);
}

void	*s_thread5(void *value)
{
	t_s_thread	*data;
	int			x;
	int			y;

	data = (t_s_thread *)value;
	x = data->sray.draw_start.x + 5 * (data->sray.draw_end.x -
			data->sray.draw_start.x) / 8;
	while (x < data->sray.draw_start.x + 3 * (data->sray.draw_end.x -
				data->sray.draw_start.x) / 4 && x < data->cub->info.res.x)
	{
		y = init_scast(data->cub, &data->sray, x);
		if (data->sray.transform.y > 0 && x >= 0 && x <
				data->cub->info.res.x &&
				data->sray.transform.y < data->z_buffer[x])
		{
			while (y < data->sray.draw_end.y)
			{
				put_sprite_pixel(data->cub, y, x, &data->sray);
				y++;
			}
		}
		x++;
	}
	return (NULL);
}

void	*s_thread6(void *value)
{
	t_s_thread	*data;
	int			x;
	int			y;

	data = (t_s_thread *)value;
	x = data->sray.draw_start.x + 3 * (data->sray.draw_end.x -
			data->sray.draw_start.x) / 4;
	while (x < data->sray.draw_start.x + 7 * (data->sray.draw_end.x -
				data->sray.draw_start.x) / 8 && x < data->cub->info.res.x)
	{
		y = init_scast(data->cub, &data->sray, x);
		if (data->sray.transform.y > 0 && x >= 0 && x <
				data->cub->info.res.x &&
				data->sray.transform.y < data->z_buffer[x])
		{
			while (y < data->sray.draw_end.y)
			{
				put_sprite_pixel(data->cub, y, x, &data->sray);
				y++;
			}
		}
		x++;
	}
	return (NULL);
}

void	*s_thread7(void *value)
{
	t_s_thread	*data;
	int			x;
	int			y;

	data = (t_s_thread *)value;
	x = data->sray.draw_start.x + 7 * (data->sray.draw_end.x -
			data->sray.draw_start.x) / 8;
	while (x <= data->sray.draw_end.x && x < data->cub->info.res.x)
	{
		y = init_scast(data->cub, &data->sray, x);
		if (data->sray.transform.y > 0 && x >= 0 && x <
				data->cub->info.res.x &&
				data->sray.transform.y < data->z_buffer[x])
		{
			while (y < data->sray.draw_end.y)
			{
				put_sprite_pixel(data->cub, y, x, &data->sray);
				y++;
			}
		}
		x++;
	}
	return (NULL);
}
