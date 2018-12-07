/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:57 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/06 21:33:31 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		print_name(t_vars *ob, char **inst, int counter)
{
	//print either name or comment;
	return (counter);
}

int		print_params(t_vars *ob, char **params, int op_code)
{
	int	counter;


	return (counter);
}

int		print_encoding(t_vars *ob, int op_code, char **params, int num_params)
{
	int counter;
	int	byte;
	int i;

	i = 0;
	byte = 0;
	counter = 0;
	if (op_tab[op_code].encoding_byte == 1)
	{
		counter++;
		while (i < num_params)
		{
			if (split[i][0] == 'r')
				byte = byte | 2 ^ (6 - 2 * i);
			else if (split[i][0] == DIRECT_CHAR)
				byte = byte | 2 ^ (7 - 2 * i);
			else
			{
				byte = byte | 2 ^ (6 - 2 * i);
				byte = byte | 2 ^ (7 - 2 * i);
			}
			i++;
		}
	}
	print_bits(byte);
	return (counter);
}

int		print_inst(t_vars *ob, char **inst, int counter)
{
	char **params;

	if (ft_strchr(inst[0], LABEL_CHAR))
		ob->label = 1;
	params = ft_strsplit(inst[ob->label + 1], SEPARATOR_CHAR);
	ob->op_code = get_op(inst[ob->label]);
	print_bits(ob, ob->op_code);
	counter++;
	counter += print_encoding(ob, ob->op_code, params,
			op_tab[op_code].num_args);
	counter += print_params(ob, params, ob->op_code);
	return (counter);
}

/*
** 3rd pass. Write to output file. Print each line in bytecode.
** Skip any label declarations. Print encoding byte if necessary.
** Substitute label references with relative address.
** Print parameters to correct number of bytes.
*/

int		generator(t_vars *ob, int fd)
{
	int		counter;
	char	*line;
	char	**inst;

	counter = 0;
	while ((get_next_line(fd, &line) > 0))
	{
		ob->label = 0;
		inst = ft_strsplit(line, ' ');
		if (ft_strcmp(inst[0], NAME_CMD_STRING) == 0 || 
				ft_strcmp(inst[0], COMMENT_CMD_STRING) == 0)
			counter = print_name(ob, inst);
		else
		{
			if ((counter = print_inst(ob, inst, counter)) == -1)
				return (-1);
		}
		free(line);
		free_split(inst);
	}
	return (1);
}
