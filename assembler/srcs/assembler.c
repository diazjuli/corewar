/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:14:37 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/04 19:23:20 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

int		main(int argc, char **argv)
{
	if (argc != 2)
		printf("arrgument must be a file\n");
	else
	{
		printf("aassembling file %s\n", argv[1]);
	}
	return (0);
}
