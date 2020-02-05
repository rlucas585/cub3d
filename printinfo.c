/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printinfo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:22:29 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 18:49:03 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <math.h>

/*
** Print the mapinfo information. Should be removed from directory prior to
** submission of project, only for troubleshooting.
*/

void		print_mapinfo(t_info info)
{
	int			y;

	y = 0;
	printf("Resolution = %dx%d\n", info.res.x, info.res.y);
	while (y < 5)
	{
		printf("textures: %d = %s\n", y, info.texs[y]);
		y++;
	}
	if (info.floor.rgb.a == 1)
		printf("textures: 5 = %s\n", info.texs[5]);
	if (info.ceiling.rgb.a == 1)
		printf("textures: 6 = %s\n", info.texs[6]);
	printf("Floor = %u\n", info.floor.x);
	printf("Ceiling = %u\n", info.ceiling.x);
	y = 0;
	while (info.map[y])
	{
		printf("%s\n", info.map[y]);
		y++;
	}
}

void		print_playerinfo(t_info info)
{
	printf("Player coordinates: X = %f Y = %f dirX = %f dirY = %f angle=%f\n",
			info.pos.x, info.pos.y, sin(to_radians(info.dir)),
			-cos(to_radians(info.dir)), info.dir);
}

void		print_spriteinfo(t_info info)
{
	int		i;

	i = 0;
	printf("Number of sprites: %d\n", info.spritenum);
	while (i < info.spritenum)
	{
		printf("Sprite %d: x: %f y: %f type: %d\n", i, info.sprts[i].pos.x,
				info.sprts[i].pos.y, info.sprts[i].type);
		i++;
	}
}

void		print_gameinfo(t_info info)
{
	print_mapinfo(info);
	print_playerinfo(info);
	print_spriteinfo(info);
}
