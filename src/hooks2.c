/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:35:06 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/21 11:07:47 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>
#include <libft.h>

void		init_keys(t_cub *cub)
{
	cub->key.w = 0;
	cub->key.s = 0;
	cub->key.a = 0;
	cub->key.d = 0;
	cub->key.left = 0;
	cub->key.right = 0;
}

void		init_hooks(t_cub *cub)
{
	mlx_do_key_autorepeatoff(cub->xsrv.dpy);
	mlx_hook(cub->xsrv.w, 2, 1L << 0, &keypress, cub);
	mlx_hook(cub->xsrv.w, 3, 1L << 1, &keyrelease, cub);
	mlx_hook(cub->xsrv.w, 17, 1L << 1, &crosspress, cub);
	mlx_loop_hook(cub->xsrv.dpy, &loop_func, cub);
}
