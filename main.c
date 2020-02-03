/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 17:16:18 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/03 13:33:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>

int			main(int argc, char **argv)
{
	t_cub		cub;

	cub.info = cub_parser(open_file(argc, argv));
	validate_n_s_walls(cub.info);
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
