/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_cast_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 17:36:45 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/21 11:18:50 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <pthread.h>

static void	sray_copy(t_sray orig, t_sray *new)
{
	new->sprite_order = orig.sprite_order;
	new->sprite_dist = orig.sprite_dist;
	new->spos = orig.spos;
	new->inv_det = orig.inv_det;
	new->transform = orig.transform;
	new->sscreenx = orig.sscreenx;
	new->sprt = orig.sprt;
	new->draw_start = orig.draw_start;
	new->draw_end = orig.draw_end;
	new->tx = orig.tx;
	new->color = orig.color;
}

static void	s_thread_loop(t_s_thread data[8], t_cub *cub)
{
	pthread_t	thread[8];

	if (pthread_create(&thread[0], NULL, &s_thread0, &data[0]) ||
			pthread_create(&thread[1], NULL, &s_thread1, &data[1]) ||
			pthread_create(&thread[2], NULL, &s_thread2, &data[2]) ||
			pthread_create(&thread[3], NULL, &s_thread3, &data[3]) ||
			pthread_create(&thread[4], NULL, &s_thread4, &data[4]) ||
			pthread_create(&thread[5], NULL, &s_thread5, &data[5]) ||
			pthread_create(&thread[6], NULL, &s_thread6, &data[6]) ||
			pthread_create(&thread[7], NULL, &s_thread7, &data[7]))
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	if (pthread_join(thread[0], NULL) ||
			pthread_join(thread[1], NULL) ||
			pthread_join(thread[2], NULL) ||
			pthread_join(thread[3], NULL) ||
			pthread_join(thread[4], NULL) ||
			pthread_join(thread[5], NULL) ||
			pthread_join(thread[6], NULL) ||
			pthread_join(thread[7], NULL))
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
}

void		sprite_cast(t_cub *cub, double *z_buffer, t_sray *sray)
{
	t_s_thread	data[8];
	int			x;

	x = 1;
	data[0].cub = cub;
	data[0].z_buffer = z_buffer;
	data[0].sray = *sray;
	while (x < 8)
	{
		data[x].cub = data[0].cub;
		data[x].z_buffer = data[0].z_buffer;
		sray_copy(data[0].sray, &(data[x].sray));
		x++;
	}
	s_thread_loop(data, cub);
}

void		draw_sprites(t_cub *cub, double *z_buffer, t_2d plane)
{
	t_sray		sray;
	int			i;

	i = 0;
	sprite_setup1(*cub, &sray);
	while (i < cub->info.spritenum)
	{
		sprite_setup2(cub->info, &sray, i, plane);
		if (sray.sprt.width < 1)
			sray.sprt.width = 1;
		if (sray.sprt.height < 1)
			sray.sprt.height = 1;
		sprite_cast(cub, z_buffer, &sray);
		i++;
	}
	free(sray.sprite_order);
	free(sray.sprite_dist);
}
