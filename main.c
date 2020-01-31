/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 13:31:01 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>

void		toggle(int key, t_all *all, int on_off)
{
	if (key == KEY_A)
		all->key.a = on_off;
	if (key == KEY_S)
		all->key.s = on_off;
	if (key == KEY_D)
		all->key.d = on_off;
	if (key == KEY_W)
		all->key.w = on_off;
	if (key == KEY_LEFT)
		all->key.left = on_off;
	if (key == KEY_RIGHT)
		all->key.right = on_off;
}

int			keypress(int key, t_all *all)
{
	if (key == KEY_ESC)
	{
		escape(all);
		exit(0);
	}
	toggle(key, all, 1);
	return (1);
}

int			keyrelease(int key, t_all *all)
{
	toggle(key, all, 0);
	return (1);
}

int			crosspress(t_all *all)
{
	escape(all);
	exit(0);
}

void		one_tex(t_all *all, int dir, void **img)
{
	int			x;
	int			y;

	x = TEXWIDTH;
	y = TEXHEIGHT;
	img[dir] = mlx_png_file_to_image(all->xsrv->dpy,
			all->info->map.textures[dir], &x, &y);
	if (!img[dir])
		exit(ft_error(delete_all(MISSING_TEX, *all), 0));
	all->info->texstrs[dir] = (int *)mlx_get_data_addr(img[dir],
			&all->info->texinf->bpp,
			&all->info->texinf->size_line,
			&all->info->texinf->endian);
	if (!all->info->texstrs[dir])
		exit(ft_error(delete_all(MISSING_TEX, *all), 0));
}

void		init_tex(t_all *all)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		all->info->texstrs[i] = NULL;
		all->info->imgs[i] = NULL;
		i++;
	}
	all->info->texinf = (t_imginf *)malloc(sizeof(t_imginf));
	if (!all->info->texinf)
		exit(ft_error(delete_all(MEM_FAIL, *all), 0));
	one_tex(all, NORTH, &all->info->imgs[NORTH]);
	one_tex(all, EAST, &all->info->imgs[EAST]);
	one_tex(all, SOUTH, &all->info->imgs[SOUTH]);
	one_tex(all, WEST, &all->info->imgs[WEST]);
	one_tex(all, SPRITE, &all->info->imgs[SPRITE]);
}

int			loop_func(t_all *all)
{
	player_actions(all);
	create_image(*all->xsrv, *all->info);
	return (1);
}

void		init_keys(t_all *all)
{
	all->key.w = 0;
	all->key.s = 0;
	all->key.a = 0;
	all->key.d = 0;
	all->key.left = 0;
	all->key.right = 0;
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

void		count_sprites(t_game *info)
{
	size_t		y;

	y = 0;
	info->spritenum = 0;
	while (info->map.coords[y])
	{
		info->spritenum += numstrchr(info->map.coords[y], '2');
		y++;
	}
}

int			main(int argc, char **argv)
{
	t_game		game;
	t_display	xsrv;
	t_all		all;

	game.map = cub_parser(open_file(argc, argv));
	validate_n_s_walls(game.map);
	game.player = find_player(game);
	if (game.player.location[X] == 0)
		exit(ft_error(delete_info(NO_PLAYER, game.map), 0));
	count_sprites(&game);
	print_gameinfo(game);
	xsrv = establish_connection(game);
	all.xsrv = &xsrv;
	all.info = &game;
	init_tex(&all);
	init_keys(&all);
	mlx_do_key_autorepeatoff(all.xsrv->dpy);
	mlx_hook(all.xsrv->w, 2, 0, &keypress, &all);
	mlx_hook(all.xsrv->w, 3, 0, &keyrelease, &all);
	mlx_hook(all.xsrv->w, 17, 0, &crosspress, &all);
	mlx_loop_hook(xsrv.dpy, &loop_func, &all);
	mlx_loop(xsrv.dpy);
	return (0);
}
