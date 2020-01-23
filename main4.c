/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main4.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 11:06:36 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/23 19:57:23 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>

/*
** Sample case of constructor and destructor function attributes
** Requires a header file with the prototype for the functions
*/

static char	*g_str;

void	show_x(int *x)
{
	printf("x = %d\n", *x);
}

/*
** The below is not norm-compliant. Use header file for prototypes.
*/

__attribute__((constructor)) void	setup2(void)
{
	printf("djksghsdfj\n");
}

void	setup(void)
{
	printf("Setting up program...\n");
	g_str = ft_strdup("this is a string");
}

void	setdown(void)
{
	free(g_str);
}

int		main(void)
{
	int x __attribute__((cleanup(show_x)));

	x = 5;
	printf("Test: %s\n", g_str);
	return (0);
}
