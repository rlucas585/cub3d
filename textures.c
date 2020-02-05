/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:29:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 18:40:44 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <cub3d.h>
#include <libft.h>
#include <stdio.h>

static void		one_tex(t_cub *cub, int side, void **img)
{
	cub->info.texinf[side] = (t_imginf *)malloc(sizeof(t_imginf));
	if (!cub->info.texinf[side])
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	*img = mlx_png_file_to_image(cub->xsrv.dpy,
			cub->info.texs[side], &cub->info.texinf[side]->size.x,
			&cub->info.texinf[side]->size.y);
	if (!(*img))
		exit(ft_error(delete_all(MISSING_TEX, *cub), 0));
	cub->info.texstrs[side] = (unsigned int *)mlx_get_data_addr(*img,
			&cub->info.texinf[side]->bpp,
			&cub->info.texinf[side]->size_line,
			&cub->info.texinf[side]->endian);
	if (!cub->info.texstrs[side])
		exit(ft_error(delete_all(MISSING_TEX, *cub), 0));
}

void			init_tex(t_cub *cub)
{
	one_tex(cub, NORTH, &cub->info.imgs[NORTH]);
	one_tex(cub, EAST, &cub->info.imgs[EAST]);
	one_tex(cub, SOUTH, &cub->info.imgs[SOUTH]);
	one_tex(cub, WEST, &cub->info.imgs[WEST]);
	one_tex(cub, SPRITE, &cub->info.imgs[SPRITE]);
	if (cub->info.f_or_c.x == 2)
		one_tex(cub, FLOOR, &cub->info.imgs[FLOOR]);
	if (cub->info.f_or_c.y == 2)
		one_tex(cub, CEILING, &cub->info.imgs[CEILING]);
}
