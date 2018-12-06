/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:29:05 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 18:30:47 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		parser(char *filename, t_vars *ob)  //2nd pass, while counting get label addresses and check lex-labels
{
	int		fd;
	int		counter;
	char	**line;

	fd = open(filename, O_RDONLY);
	counter = 0;
	while ((get_next_line(fd, line) > 0))
	{
		get_label_addr(line, ob);
		check_label(line, ob);   //check the label is correct within the arg, get the label value inside the struct


	}
	return (1);
}
