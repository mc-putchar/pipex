/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:56:47 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/29 15:57:53 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	blckchckr(int blck, int *wrd, const char *s, const char *blckrs)
{
	if (blck)
	{
		if (*(ft_strchr(blckrs, *s)) == blck)
			return (++(*wrd), 0);
		return (++(*wrd), blck);
	}
	if (!blck && ft_strchr(blckrs, *s))
		return (++(*wrd), (int)*(ft_strchr(blckrs, *s)));
	++(*wrd);
	return (0);
}

static int	count_blocks(const char *s, char c, const char *blockers)
{
	int	count;
	int	block;
	int	word;

	count = 0;
	block = 0;
	word = 0;
	while (*s)
	{
		if (*s++ != c)
		{
			block = blckchckr(block, &word, s - 1, blockers);
			continue ;
		}
		if (!block && word)
		{
			++count;
			word = 0;
		}
		else
			++word;
	}
	if (!block && word)
		++count;
	return (count);
}

static void	*gtfo(char **spl, int i)
{
	while (i--)
		free(spl[i]);
	free(spl);
	return (NULL);
}

static int	get_block(char **spl, const char *s, int *word)
{
	if (*word)
	{
		*spl = ft_substr(s - *word, 0, *word);
		if (!*spl)
			return (EXIT_FAILURE);
		*word = 0;
	}
	else
		++(*word);
	return (EXIT_SUCCESS);
}

char	**ft_split_blocks(const char *s, char c, const char *blockers)
{
	char	**spl;
	int		count;
	int		block;
	int		word;
	int		i;

	count = count_blocks(s, c, blockers);
	spl = malloc(sizeof(char *) * (count + 1));
	if (!spl)
		return (NULL);
	block = 0;
	word = 0;
	i = 0;
	while (i < count)
	{
		if ((*s++ == c || !*(s - 1)) && !block)
		{
			if (get_block(&spl[i++], s - 1, &word))
				return (gtfo(spl, i - 1));
		}
		else
			block = blckchckr(block, &word, s - 1, blockers);
	}
	spl[i] = NULL;
	return (spl);
}
