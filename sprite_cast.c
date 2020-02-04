/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_cast.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 10:25:30 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/04 19:37:01 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <stdio.h>

void		int_swap(int *a, int *b)
{
	int		temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void		double_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void		print_sprites(int number, int *order, double *dist)
{
	int		i;

	i = 0;
	printf("Order: [");
	while (i < number)
	{
		if (i == number - 1)
			printf("%d]\n", order[i]);
		else
			printf("%d, ", order[i]);
		i++;
	}
	i = 0;
	printf("Distance: [");
	while (i < number)
	{
		if (i == number - 1)
			printf("%f]\n", dist[i]);
		else
			printf("%f, ", dist[i]);
		i++;
	}
}

void		sortsprites(int number, int **order, double **dist)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < number)
	{
		while (y < number - x - 1)
		{
			if ((*dist)[y] < (*dist)[y + 1])
			{
				int_swap(&(*order)[y], &(*order)[y + 1]);
				double_swap(&(*dist)[y], &(*dist)[y + 1]);
			}
			y++;
		}
		y = 0;
		x++;
	}
}

void		sprite_setup1(t_cub cub, t_sray *sray)
{
	int		i;
	t_2d	pos;
	t_2d	spos;

	i = 0;
	pos = cub.info.pos;
	sray->sprite_order = (int *)malloc(sizeof(int) * cub.info.spritenum);
	if (!sray->sprite_order)
		exit(ft_error(delete_all(MEM_FAIL, cub), 0));
	sray->sprite_dist = (double *)malloc(sizeof(double) * cub.info.spritenum);
	if (!sray->sprite_dist)
	{
		free(sray->sprite_order);
		exit(ft_error(delete_all(MEM_FAIL, cub), 0));
	}
	while (i < cub.info.spritenum)
	{
		spos = cub.info.sprts[i].pos;
		sray->sprite_order[i] = i;
		sray->sprite_dist[i] = ((pos.x - spos.x) * (pos.x - spos.x) +
				(pos.y - spos.y) * (pos.y - spos.y));
		i++;
	}
	sortsprites(cub.info.spritenum, &sray->sprite_order, &sray->sprite_dist);
}

void		sprite_setup2(t_info info, t_sray *sray, int i, t_2d plane)
{
	sray->spos.x = info.sprts[sray->sprite_order[i]].pos.x - info.pos.x;
	sray->spos.y = info.sprts[sray->sprite_order[i]].pos.y - info.pos.y;
	sray->inv_det = 1.0 / (plane.x * -cos(to_radians(info.dir)) -
				sin(to_radians(info.dir)) * plane.y);
	sray->transform.x = sray->inv_det * (-cos(to_radians(info.dir)) *
			sray->spos.x - sin(to_radians(info.dir)) * sray->spos.y);
	sray->transform.y = sray->inv_det * (-plane.y * sray->spos.x + plane.x *
			sray->spos.y);
	sray->sscreenx = (int)((info.res.x / 2) * (1 + sray->transform.x /
				sray->transform.y));
	sray->sprt.height = ft_abs((int)(info.res.y / (sray->transform.y)));
	sray->draw_start.y = -sray->sprt.height / 2 + info.res.y / 2;
	if (sray->draw_start.y < 0)
		sray->draw_start.x = 0;
	sray->draw_end.y = sray->sprt.height / 2 + info.res.y / 2;
	if (sray->draw_end.y >= info.res.y)
		sray->draw_end.y = info.res.y - 1;
	sray->sprt.width = ft_abs((int)(info.res.y / (sray->transform.y)));
	sray->draw_start.x = -sray->sprt.width / 2 + sray->sscreenx;
	if (sray->draw_start.x < 0)
		sray->draw_start.x = 0;
	sray->draw_end.x = sray->sprt.width / 2 + sray->sscreenx;
	if (sray->draw_end.x >= info.res.x)
		sray->draw_end.x = info.res.x - 1;
}

void		sprite_cast(t_cub *cub, double *z_buffer, t_sray *sray)
{
	int			stripe;
	int			y;
	int			d;

	stripe = sray->draw_start.x;
	while (stripe < sray->draw_end.x)
	{
		sray->tx.x = (int)(256 * (stripe - (-sray->sprt.width / 2 +
						sray->sscreenx)) * TEXWIDTH / sray->sprt.width) / 256;
		y = sray->draw_start.y;
		if (sray->transform.y > 0 && stripe > 0 && stripe < cub->info.res.x &&
				sray->transform.y < z_buffer[stripe])
		{
			while (y < sray->draw_end.y)
			{
				d = (y) * 256 - cub->info.res.y * 128 + sray->sprt.height * 128;
				sray->tx.y = ((d * TEXHEIGHT) / sray->sprt.height) / 256;
				sray->color = cub->info.texstrs[SPRITE][TEXWIDTH * sray->tx.y +
				sray->tx.x];
				if ((sray->color & 0x00FFFFFF) != 0)
					img_put_pixel(*cub, stripe, y, sray->color);
				y++;
			}
		}
		stripe++;
	}
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
		sprite_cast(cub, z_buffer, &sray);
		i++;
	}
	free(sray.sprite_order);
	free(sray.sprite_dist);
}
