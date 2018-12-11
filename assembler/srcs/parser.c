/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:29:05 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/10 21:19:29 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		count_params(int op_code, int num_args, char *args)
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
		else if (split[i][0] == DIRECT_CHAR && check_index(op_code) != 1)
			mem += DIR_SIZE;
		else
			mem += IND_SIZE;
	}
	return (mem);
}

int		set_address(char *label, int address, t_vars *ob)
{
	t_label *tmp;

	tmp = ob->labels;
	while (tmp)
	{
		if (ft_strcmp(tmp->label, label) == 0)
		{
			tmp->address = address;
			return (1);
		}
		tmp = tmp->next;
	}
	return (-1);
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

	counter = 2176;
	while ((get_next_line(fd, &line) > 0))
	{
		ob->labels = 0;
		if (line[0] != COMMENT_CHAR && line[0] != '.' && ft_strcmp(line, "\n"))
		{
			inst = ft_strsplit(line, ' ');
			if (ft_strchr(inst[0], LABEL_CHAR))
			{
				set_address(inst[0], counter, ob);
				ob->bl_label = 1;
			}
			ob->op_code = get_op(inst[ob->bl_label]);
			counter += 1 + op_tab[ob->op_code].encoding_byte;
			counter += count_params(ob->op_code, op_tab[ob->op_code].num_args,
					inst[ob->bl_label + 1]);
			free_split(inst);
		}
		free(line);
	}
	return (1);
}
