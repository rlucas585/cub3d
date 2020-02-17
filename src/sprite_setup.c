/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_setup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 17:37:41 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 18:30:49 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>

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

int			init_scast(t_cub *cub, t_sray *sray, int stripe)
{
	sray->tx.x = (int)(256 * (stripe - (-sray->sprt.width / 2 +
					sray->sscreenx)) * cub->info.texinf[SPRITE]->size.x /
			sray->sprt.width) / 256;
	if (sray->tx.x >= cub->info.texinf[SPRITE]->size.x)
		sray->tx.x = cub->info.texinf[SPRITE]->size.x - 1;
	return (sray->draw_start.y);
}
