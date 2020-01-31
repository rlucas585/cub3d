/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   connect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:48:46 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 19:12:19 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

void		establish_connection(t_cub *cub)
{

	cub->xsrv.dpy = mlx_init();
	if (cub->xsrv.dpy == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, cub->info), 0));
	cub->xsrv.w = mlx_new_window(cub->xsrv.dpy,
			cub->info.res.x, cub->info.res.x, "Ryan's cub3d");
	if (cub->xsrv.w == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, cub->info), 0));
	cub->xsrv.imginf = (t_imginf *)malloc(sizeof(t_imginf));
	if (cub->xsrv.imginf == NULL)
		exit(ft_error(delete_info(MEM_FAIL, cub->info), 0));
	mlx_clear_window(cub->xsrv.dpy, cub->xsrv.w);
}
