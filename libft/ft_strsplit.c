/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:34:19 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/11 17:07:44 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_words(char const *s, char c, char d)
{
	int len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		while (*s != '\0' && *s != c && *s != d)
			s++;
		while (*s == c || *s == d)
			s++;
	}
	return (len);
}

static char	**get_words(char **result, char const *s, char *str, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		while (s[i] != '\0' && s[i] != str[0] && s[i] != str[1])
			i++;
		result[j] = ft_strnew(i + 1);
		result[j] = ft_strncpy(result[j], s, i);
		result[j][i] = '\0';
		s += i;
		i = 0;
		j++;
		while (*s == str[0] || *s == str[1])
			s++;
	}
	result[j] = 0;
	return (result);
}

char		**ft_strsplit(char const *s, char *str)
{
	char	**result;
	int		len;

	if (!s)
		return (NULL);
	while (*s == str[0] || *s == str[1])
		s++;
	len = num_words(s, str[0], str[1]);
	result = (char **)malloc(sizeof(char *) * len + 1);
	if (!result)
		return (NULL);
	result = get_words(result, s, str, len);
	return (result);
}
