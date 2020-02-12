/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 10:14:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/12 14:23:10 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>
#include <libft.h>
#include <fcntl.h>

/*
** Raycast for the new image, then swap out the old image for the new one.
** Also, if the '--save' argument was supplied, and it's the first
** create_image() function call, then save the first image to a bmp file.
*/

void			create_image(t_cub *cub)
{
	ray(cub);
	if (cub->save == 1)
	{
		save_init_img(*cub);
		escape(cub);
		exit(0);
	}
	if (cub->imgswap == 0)
	{
		mlx_put_image_to_window(cub->xsrv.dpy, cub->xsrv.w,
				cub->xsrv.img, 0, 0);
		cub->imgswap = 1;
	}
	else
	{
		mlx_put_image_to_window(cub->xsrv.dpy, cub->xsrv.w,
				cub->xsrv.img2, 0, 0);
		cub->imgswap = 0;
	}
}

static int		check_keys(t_keys key)
{
	if (key.w == 0 && key.s == 0 && key.a == 0 && key.d == 0 &&
			key.left == 0 && key.right == 0)
		return (1);
	return (0);
}

int				loop_func(t_cub *cub)
{
	if (check_keys(cub->key))
		return (1);
	player_actions(cub);
	create_image(cub);
	return (1);
}
