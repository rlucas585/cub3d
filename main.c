/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:29:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>

void		toggle(int key, t_cub *cub, int on_off)
{
	if (key == KEY_A)
		cub->key.a = on_off;
	if (key == KEY_S)
		cub->key.s = on_off;
	if (key == KEY_D)
		cub->key.d = on_off;
	if (key == KEY_W)
		cub->key.w = on_off;
	if (key == KEY_LEFT)
		cub->key.left = on_off;
	if (key == KEY_RIGHT)
		cub->key.right = on_off;
}

int			keypress(int key, t_cub *cub)
{
	if (key == KEY_ESC)
	{
		escape(cub);
		exit(0);
	}
	toggle(key, cub, 1);
	return (1);
}

int			keyrelease(int key, t_cub *cub)
{
	toggle(key, cub, 0);
	return (1);
}

int			crosspress(t_cub *cub)
{
	escape(cub);
	exit(0);
}

void		one_tex(t_cub *cub, int side, void **img)
{
	int			x;
	int			y;

	x = TEXWIDTH;
	y = TEXHEIGHT;
	img[side] = mlx_png_file_to_image(cub->xsrv.dpy,
			cub->info.texs[side], &x, &y);
	if (!img[side])
		exit(ft_error(delete_all(MISSING_TEX, *cub), 0));
	cub->info.texstrs[side] = (int *)mlx_get_data_addr(img[side],
			&cub->info.texinf->bpp,
			&cub->info.texinf->size_line,
			&cub->info.texinf->endian);
	if (!cub->info.texstrs[side])
		exit(ft_error(delete_all(MISSING_TEX, *cub), 0));
}

void		init_tex(t_cub *cub)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		cub->info.texstrs[i] = NULL;
		cub->info.imgs[i] = NULL;
		i++;
	}
	cub->info.texinf = (t_imginf *)malloc(sizeof(t_imginf));
	if (!cub->info.texinf)
		exit(ft_error(delete_all(MEM_FAIL, *cub), 0));
	one_tex(cub, NORTH, &cub->info.imgs[NORTH]);
	one_tex(cub, EAST, &cub->info.imgs[EAST]);
	one_tex(cub, SOUTH, &cub->info.imgs[SOUTH]);
	one_tex(cub, WEST, &cub->info.imgs[WEST]);
	one_tex(cub, SPRITE, &cub->info.imgs[SPRITE]);
}

int			loop_func(t_cub *cub)
{
	player_actions(cub);
	create_image(cub);
	return (1);
}

void		init_keys(t_cub *cub)
{
	cub->key.w = 0;
	cub->key.s = 0;
	cub->key.a = 0;
	cub->key.d = 0;
	cub->key.left = 0;
	cub->key.right = 0;
}

int			numstrchr(char *str, int c)
{
	size_t		i;
	int			total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == c)
			total++;
		i++;
	}
	return (total);
}

void		count_sprites(t_info *info)
{
	size_t		y;

	y = 0;
	info->spritenum = 0;
	while (info->map[y])
	{
		info->spritenum += numstrchr(info->map[y], '2');
		y++;
	}
}

int			main(int argc, char **argv)
{
	t_cub		cub;

	cub.info = cub_parser(open_file(argc, argv));
	validate_n_s_walls(cub.info);
	find_player(&cub.info);
	if (cub.info.pos.x == 0)
		exit(ft_error(delete_info(NO_PLAYER, cub.info), 0));
	count_sprites(&cub.info);
	print_gameinfo(cub.info);
	establish_connection(&cub);
	init_tex(&cub);
	init_keys(&cub);
	mlx_do_key_autorepeatoff(cub.xsrv.dpy);
	mlx_hook(cub.xsrv.w, 2, 0, &keypress, &cub);
	mlx_hook(cub.xsrv.w, 3, 0, &keyrelease, &cub);
	mlx_hook(cub.xsrv.w, 17, 0, &crosspress, &cub);
	mlx_loop_hook(cub.xsrv.dpy, &loop_func, &cub);
	mlx_loop(cub.xsrv.dpy);
	return (0);
}
