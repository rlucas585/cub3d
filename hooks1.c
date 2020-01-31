/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:33:48 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 20:44:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <mlx.h>

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

int			loop_func(t_cub *cub)
{
	player_actions(cub);
	create_image(cub);
	return (1);
}
