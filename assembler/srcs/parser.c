/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:29:05 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/06 19:58:19 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		count_params(int op_code, int num_args, int *arg_types, char *args)
{
	int	mem;
	int i;
	char **split;

	i = 0;
	mem = 0;
	split = ft_strsplit(args, SEPARATOR_CHAR);
	while (i < num_args)
	{
		if (split[i][0] == 'r')
			mem++;
		else if (split[i][0] == DIRECT_CHAR)
			mem += DIR_SIZE;
		else
			mem += IND_SIZE;
	}
	return (mem);
}

/*
** Second pass through the file. Will check validity of all labels used and 
** get addresses for each label. Uses counter to keep track of current address
*/

int		get_label_address(t_vars *ob, int fd)
{
	int		counter;
	char	*line;
	char	**inst;

	counter = 0;
	while ((get_next_line(fd, &line) > 0))
	{
		ob->label = 0;
		if (line[0] != COMMENT_CHAR && line[0] != '.' && ft_strcmp(line, "\n"))
		{
			inst = ft_strsplit(line, ' ');
			if (ft_strchr(inst[0], LABEL_CHAR))
			{
				set_address(inst[0], counter);
				ob->label = 1;
			}
			ob->op_code = get_op(inst[ob->label]);
			counter += 1 + op_tab[ob->op_code].encoding_byte;
			count += count_params(ob->op_code, op_tab[ob->op_code].num_args,
					op_tab[ob->op_code].arg_types, inst[ob->label + 1]);
			free_split(inst);
		}
		free(line);
	}
	return (1);
}
