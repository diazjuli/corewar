/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 08:09:03 by jdiaz             #+#    #+#             */
/*   Updated: 2018/09/12 19:26:35 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*copy;

	copy = dst;
	while (len > 0 && *src)
	{
		*copy++ = *src++;
		len--;
	}
	while (len > 0)
	{
		*copy = '\0';
		copy++;
		len--;
	}
	return (dst);
}
