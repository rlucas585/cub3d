/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 18:49:25 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>

void		init_info(t_info *info)
{
	int		i;

	i = 0;
	info->map = NULL;
	while (i < 7)
	{
		info->texs[i] = NULL;
		info->texstrs[i] = NULL;
		info->imgs[i] = NULL;
		info->texinf[i] = NULL;
		i++;
	}
	info->z_buffer = NULL;
	info->sprts = NULL;
	info->res.x = 0;
	info->res.y = 0;
	info->f_or_c.x = 0;
	info->f_or_c.y = 0;
}

int			main(int argc, char **argv)
{
	t_cub		cub;

	init_info(&cub.info);
	cub.info = cub_parser(open_file(argc, argv, &cub));
	validate(cub.info);
	find_player(&cub.info);
	if (cub.info.pos.x == 0)
		exit(ft_error(delete_info(NO_PLAYER, cub.info), 0));
	init_sprites(&cub.info);
	print_gameinfo(cub.info);
	establish_connection(&cub);
	init_tex(&cub);
	init_keys(&cub);
	init_hooks(&cub);
	mlx_loop(cub.xsrv.dpy);
	return (0);
}
