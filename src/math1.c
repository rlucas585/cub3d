/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math1.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 20:21:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/17 08:58:36 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double		to_degrees(double radians)
{
	return ((180 / M_PI) * radians);
}

double		to_radians(double degrees)
{
	return ((degrees * M_PI) / 180);
}
