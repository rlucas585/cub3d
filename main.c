/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 18:37:32 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/15 14:10:18 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>

int			main(void)
{
	char		*example;

	ft_printf("Testing libft %s for the %10.5dth time\n", "functionality", 100);
	while (get_next_line(0, &example))
	{
		ft_printf("%s\n", example);
		if (example)
		{
			free(example);
			example = NULL;
		}
	}
	return (0);
}
