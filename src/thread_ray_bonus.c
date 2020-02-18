/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_ray.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 17:25:56 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/18 14:49:09 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <pthread.h>

static void	*thread0(void *value)
{
	t_cub		*cub;
	t_ray		ray;
	int			x;

	cub = (t_cub *)value;
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	x = 0;
	while (x < cub->info.res.x / 4)
	{
		ray_setup1(cub->info, &ray, x);
		ray_setup2(cub->info, &ray);
		dda(cub->info, &ray);
		draw_setup(cub->info, &ray);
		floorcast(cub, &ray, x);
		wallcast(cub, &ray, x);
		cub->info.z_buffer[x] = ray.pdist;
		x++;
	}
	return (NULL);
}

static void	*thread1(void *value)
{
	t_cub		*cub;
	t_ray		ray;
	int			x;

	cub = (t_cub *)value;
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	x = cub->info.res.x / 4;
	while (x < cub->info.res.x / 2)
	{
		ray_setup1(cub->info, &ray, x);
		ray_setup2(cub->info, &ray);
		dda(cub->info, &ray);
		draw_setup(cub->info, &ray);
		floorcast(cub, &ray, x);
		wallcast(cub, &ray, x);
		cub->info.z_buffer[x] = ray.pdist;
		x++;
	}
	return (NULL);
}

static void	*thread2(void *value)
{
	t_cub		*cub;
	t_ray		ray;
	int			x;

	cub = (t_cub *)value;
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	x = cub->info.res.x / 2;
	while (x < 3 * cub->info.res.x / 4)
	{
		ray_setup1(cub->info, &ray, x);
		ray_setup2(cub->info, &ray);
		dda(cub->info, &ray);
		draw_setup(cub->info, &ray);
		floorcast(cub, &ray, x);
		wallcast(cub, &ray, x);
		cub->info.z_buffer[x] = ray.pdist;
		x++;
	}
	return (NULL);
}

static void	*thread3(void *value)
{
	t_cub		*cub;
	t_ray		ray;
	int			x;

	cub = (t_cub *)value;
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	x = 3 * cub->info.res.x / 4;
	while (x < cub->info.res.x)
	{
		ray_setup1(cub->info, &ray, x);
		ray_setup2(cub->info, &ray);
		dda(cub->info, &ray);
		draw_setup(cub->info, &ray);
		floorcast(cub, &ray, x);
		wallcast(cub, &ray, x);
		cub->info.z_buffer[x] = ray.pdist;
		x++;
	}
	return (NULL);
}

void		thread_ray(t_cub *cub)
{
	t_ray		ray;
	pthread_t	thread[4];

	if (!cub->info.z_buffer)
		cub->info.z_buffer = (double *)malloc(sizeof(double) * cub->info.res.x);
	if (!cub->info.z_buffer)
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	ray.plane.x = 0.66 * cos(to_radians(cub->info.dir));
	ray.plane.y = 0.66 * sin(to_radians(cub->info.dir));
	if (pthread_create(&thread[0], NULL, &thread0, cub) ||
			pthread_create(&thread[1], NULL, &thread1, cub) ||
			pthread_create(&thread[2], NULL, &thread2, cub) ||
			pthread_create(&thread[3], NULL, &thread3, cub))
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	if (pthread_join(thread[0], NULL) ||
			pthread_join(thread[1], NULL) ||
			pthread_join(thread[2], NULL) ||
			pthread_join(thread[3], NULL))
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	draw_sprites(cub, cub->info.z_buffer, ray.plane);
	ft_bzero(cub->info.z_buffer, (size_t)cub->info.res.x);
}
