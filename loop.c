/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/03 10:14:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 15:44:07 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>
#include <stdio.h>

/* void		save_init_img() */
/* { */
/* 	int			fd; */
/*  */
/* 	fd = open("output.bmp", O_WRONLY | O_CREAT, 0644); */
/* } */

/*
** Create a raycasted image, put it to the window, then destroy it.
*/

static void		create_image(t_cub *cub)
{
	cub->xsrv.img = mlx_new_image(cub->xsrv.dpy, cub->info.res.x,
			cub->info.res.y);
	if (!cub->xsrv.img)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	cub->xsrv.imga = mlx_get_data_addr(cub->xsrv.img, &cub->xsrv.imginf->bpp,
			&cub->xsrv.imginf->size_line, &cub->xsrv.imginf->endian);
	if (!cub->xsrv.imga)
		exit(ft_error(delete_all(CONNECTION_FAIL, *cub), 0));
	ray(cub);
	mlx_put_image_to_window(cub->xsrv.dpy, cub->xsrv.w, cub->xsrv.img, 0, 0);
	/* if (cub->info.save) */
	/* { */
	/* 	save_init_img(); */
	/* 	cub->info.save = 0; */
	/* } */
	mlx_destroy_image(cub->xsrv.dpy, cub->xsrv.img);
}

/*
** Remember to fix the error in map parsing, "NOO" is accepted instead of "NO";
*/

int				loop_func(t_cub *cub)
{
	player_actions(cub);
	create_image(cub);
	return (1);
}
