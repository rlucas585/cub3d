/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   connect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:48:46 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 08:52:01 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>

void		init_images(t_cub *cub)
{
	cub->xsrv.img = mlx_new_image(cub->xsrv.dpy, cub->info.res.x,
			cub->info.res.y);
	if (!cub->xsrv.img)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	cub->xsrv.img2 = mlx_new_image(cub->xsrv.dpy, cub->info.res.x,
			cub->info.res.y);
	if (!cub->xsrv.img2)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	cub->xsrv.imga = mlx_get_data_addr(cub->xsrv.img, &cub->xsrv.imginf->bpp,
			&cub->xsrv.imginf->size_line, &cub->xsrv.imginf->endian);
	if (!cub->xsrv.imga)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	cub->xsrv.imga2 = mlx_get_data_addr(cub->xsrv.img2, &cub->xsrv.imginf->bpp,
			&cub->xsrv.imginf->size_line, &cub->xsrv.imginf->endian);
	if (!cub->xsrv.imga2)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
}

void		establish_connection(t_cub *cub)
{
	cub->xsrv.dpy = mlx_init();
	if (cub->xsrv.dpy == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, cub->info), 0));
	cub->xsrv.w = mlx_new_window(cub->xsrv.dpy,
			cub->info.res.x, cub->info.res.y, "Ryan's cub3d");
	if (cub->xsrv.w == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, cub->info), 0));
	cub->xsrv.imginf = (t_imginf *)malloc(sizeof(t_imginf));
	if (cub->xsrv.imginf == NULL)
		exit(ft_error(delete_info(MEM_FAIL, cub->info), 0));
	mlx_clear_window(cub->xsrv.dpy, cub->xsrv.w);
	init_images(cub);
}
