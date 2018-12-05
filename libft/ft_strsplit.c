/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:34:19 by jdiaz             #+#    #+#             */
/*   Updated: 2018/10/19 21:04:28 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_words(char const *s, char c)
{
	int len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		while (*s != '\0' && *s != c)
			s++;
		while (*s == c)
			s++;
	}
	return (len);
}

static char	**get_words(char **result, char const *s, char c, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
		result[j] = ft_strnew(i + 1);
		result[j] = ft_strncpy(result[j], s, i);
		result[j][i] = '\0';
		s += i;
		i = 0;
		j++;
		while (*s == c)
			s++;
	}
	result[j] = 0;
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;
	int		len;

	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	len = num_words(s, c);
	result = (char **)malloc(sizeof(char *) * len + 1);
	if (!result)
		return (NULL);
	result = get_words(result, s, c, len);
	return (result);
}
