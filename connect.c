/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   connect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:48:46 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 16:06:01 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

t_display	establish_connection(t_game info)
{
	t_display	xsrv;

	xsrv.dpy = mlx_init();
	if (xsrv.dpy == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.w = mlx_new_window(xsrv.dpy, info.map.res[0], info.map.res[1], "cub3d");
	if (xsrv.w == NULL)
		exit(ft_error(delete_info(CONNECTION_FAIL, info.map), 0));
	xsrv.imginf = (t_imginf *)malloc(sizeof(t_imginf));
	if (xsrv.imginf == NULL)
		exit(ft_error(delete_info(MEM_FAIL, info.map), 0));
	mlx_clear_window(xsrv.dpy, xsrv.w);
	return (xsrv);
}
