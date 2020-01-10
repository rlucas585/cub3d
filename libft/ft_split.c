/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:14:22 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/04 11:32:43 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c)
{
	int				i;
	int				total;
	int				inword;

	i = 0;
	total = 0;
	inword = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && inword == 0)
		{
			total++;
			inword = 1;
		}
		if (s[i] == c && inword == 1)
			inword = 0;
		i++;
	}
	return (total);
}

static size_t	word_length(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char		*create_word(char const *s, char c)
{
	int		i;
	char	*word;
	int		len;

	i = 0;
	len = word_length(s, c);
	word = (char *)malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static char		**free_array_of_strings(char **strarray, int elemcount)
{
	while (elemcount >= 0)
	{
		free(strarray[elemcount]);
		elemcount--;
	}
	if (strarray)
		free(strarray);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int			i;
	int			m;
	char		**arr;

	i = 0;
	m = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i] != '\0' && i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			*(arr + m) = create_word(s + i, c);
			if (!arr[m])
				return (free_array_of_strings(arr, m));
			i = i + word_length(s + i, c);
			m++;
		}
		i++;
	}
	arr[m] = NULL;
	return (arr);
}
