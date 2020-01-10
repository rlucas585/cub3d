/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:20:30 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 11:30:43 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chkchar_instr(char c, const char *s1)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (c == s1[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_createstring(size_t length, size_t i, const char *s1)
{
	size_t		k;
	char		*endstring;

	k = 0;
	endstring = (char *)malloc(sizeof(char) * length + 1);
	if (!endstring)
		return (NULL);
	while (k < length)
	{
		*(endstring + k) = s1[i];
		i++;
		k++;
	}
	*(endstring + k) = '\0';
	return (endstring);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t		curlen;
	char		*newstr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	curlen = ft_strlen(s1);
	while (ft_chkchar_instr(s1[i], set))
		i++;
	while (ft_chkchar_instr(s1[curlen - 1 - j], set))
		j++;
	if (i + j > curlen)
		return (ft_strdup(""));
	curlen = curlen - i - j;
	newstr = ft_createstring(curlen, i, s1);
	if (!newstr)
		return (NULL);
	return (newstr);
}
