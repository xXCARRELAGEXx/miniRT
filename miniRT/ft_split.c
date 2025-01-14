/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramier <aramier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:41:30 by rrault            #+#    #+#             */
/*   Updated: 2024/02/23 17:05:58 by aramier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	i = 0;
	while (src[i])
		i++;
	return (i);
}

static int	ft_countwords(char *s, char *delimiters)
{
	int	i;
	int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && ft_strchr(delimiters, s[i]))
		i++;
	while (s[i])
	{
		if (ft_strchr(delimiters, s[i]))
		{
			nb_strs++;
			while (s[i] && ft_strchr(delimiters, s[i]))
				i++;
			continue ;
		}
		i++;
	}
	if (!ft_strchr(delimiters, s[i - 1]))
		nb_strs++;
	return (nb_strs);
}

static void	ft_next_str(char **next_str, int *next_str_len, char *delimiters)
{
	int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && ft_strchr(delimiters, **next_str))
		(*next_str)++;
	while ((*next_str)[i])
	{
		if (ft_strchr(delimiters, (*next_str)[i]))
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char *s, char *delimiters, t_exvar *var)
{
	char	**tab;
	char	*next_str;
	int		next_str_len;
	int		nb_strs;
	int		i;

	nb_strs = ft_countwords(s, delimiters);
	tab = ft_malloc_save(sizeof(char *) * (nb_strs + 1), var);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_next_str(&next_str, &next_str_len, delimiters);
		tab[i] = ft_malloc_save(sizeof(char) * (next_str_len + 1), var);
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
