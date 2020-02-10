/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:48:37 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/10 13:43:34 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <math.h>
#include <mlx.h>

void		turn_left(t_cub *cub)
{
	cub->info.dir -= TURNANGLE;
	if (cub->info.dir < 0)
		cub->info.dir += 360;
}

void		turn_right(t_cub *cub)
{
	cub->info.dir += TURNANGLE;
	if (cub->info.dir >= 360)
		cub->info.dir -= 360;
}

void		escape(t_cub *cub)
{
	delete_all(0, *cub);
}

void		player_actions(t_cub *cub)
{
	if (cub->key.left)
		turn_left(cub);
	if (cub->key.right)
		turn_right(cub);
	if (cub->key.w)
		move_forward(cub);
	if (cub->key.s)
		move_back(cub);
	if (cub->key.a)
		move_left(cub);
	if (cub->key.d)
		move_right(cub);
}
