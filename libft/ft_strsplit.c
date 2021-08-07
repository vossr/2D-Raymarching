/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:12:58 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 08:34:00 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_set_value(char **fresh, const char *s, int wrd, char c)
{
	int	i;
	int	len;
	int	wnum;

	i = 0;
	wnum = 0;
	while (s[i] == c && s[i])
		i++;
	while (wnum < wrd)
	{
		len = 0;
		while (s[i] != c && s[i])
		{
			fresh[wnum][len++] = s[i];
			i++;
		}
		while (s[i] == c && s[i])
			i++;
		wnum++;
	}
}

static void	ft_allocate_sizes(char **fresh, const char *s, int wrd, char c)
{
	int		wnum;
	int		len;
	int		i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	wnum = 0;
	while (wnum < wrd)
	{
		len = 0;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		while (s[i] == c && s[i])
			i++;
		fresh[wnum] = (char *)malloc(sizeof(char) * (len + 1));
		if (!fresh[wnum])
			return ;
		fresh[wnum][len] = '\0';
		wnum++;
	}
	ft_set_value(fresh, s, wrd, c);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**fresh;
	int		wrd;
	int		i;

	i = 0;
	wrd = 0;
	if (!s)
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		wrd++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	fresh = (char **)malloc(sizeof(char *) * (wrd + 1));
	if (!fresh)
		return (NULL);
	fresh[wrd] = NULL;
	ft_allocate_sizes(fresh, s, wrd, c);
	return (fresh);
}
