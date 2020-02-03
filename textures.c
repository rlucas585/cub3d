/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:29:19 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/03 13:16:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <cub3d.h>
#include <libft.h>
#include <stdio.h>

static void		one_tex(t_cub *cub, int side, void **img)
{
	int			x;
	int			y;

	x = TEXWIDTH;
	y = TEXHEIGHT;
	img[side] = mlx_png_file_to_image(cub->xsrv.dpy,
			cub->info.texs[side], &x, &y);
	if (!img[side])
		exit(ft_error(delete_all(MISSING_TEX, *cub), 0));
	cub->info.texinf[side] = (t_imginf *)malloc(sizeof(t_imginf));
	if (!cub->info.texinf[side])
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	cub->info.texstrs[side] = (int *)mlx_get_data_addr(img[side],
			&cub->info.texinf[side]->bpp,
			&cub->info.texinf[side]->size_line,
			&cub->info.texinf[side]->endian);
	if (!cub->info.texstrs[side])
		exit(ft_error(delete_all(MISSING_TEX, *cub), 0));
}

void			init_tex(t_cub *cub)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		cub->info.texstrs[i] = NULL;
		cub->info.imgs[i] = NULL;
		i++;
	}
	one_tex(cub, NORTH, &cub->info.imgs[NORTH]);
	one_tex(cub, EAST, &cub->info.imgs[EAST]);
	one_tex(cub, SOUTH, &cub->info.imgs[SOUTH]);
	one_tex(cub, WEST, &cub->info.imgs[WEST]);
	one_tex(cub, SPRITE, &cub->info.imgs[SPRITE]);
}
