/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:57 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/12 13:38:19 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		print_name(t_vars *ob, char **inst, char *line)
{
	int	length;
	int i;

	i = 0;
	length = ft_strcmp(inst[0], NAME_CMD_STRING) == 0 ?
		PROG_NAME_LENGTH + 5: COMMENT_LENGTH + 9;
	free_split(inst);
	inst = ft_strsplit(line, "\"\"\"");
	i = ft_strlen(inst[1]);
	ft_putstr_fd(inst[1], ob->output_fd);
	while (i <= length)
	{
		ft_putchar_fd(0, ob->output_fd);
		i++;
	}
	free_split(inst);
	return (1);
}

int		print_params(t_vars *ob, char **inst, int op_code, int begin_address)
{
	int	counter;
	int i;

	i = ob->bl_label + 1;
	counter = 0;
	while (inst[i] != NULL)
	{
		if (inst[i][0] == 'r')
		{
			counter++;
			ft_putchar_fd(ft_atoi(inst[i] + 1), ob->output_fd);
		}
		else if (inst[i][0] == DIRECT_CHAR && check_index(op_code) == -1)
		{
			counter += 4;
			print_direct(inst[i], ob, begin_address);
		}
		else
		{
			counter += 2;
			print_indirect(inst[i], ob, begin_address);
		}
		i++;
	}
	return (counter);
}

int		print_encoding(t_vars *ob, int op_code, char **inst, int num_params)
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
			if (inst[i + 1 + ob->bl_label][0] == 'r')
				byte = byte | power_of2(6 - 2 * i);
			else if (inst[i + 1 + ob->bl_label][0] == DIRECT_CHAR)
				byte = byte | power_of2(7 - 2 * i);
			else
			{
				byte = byte | power_of2(6 - 2 * i);
				byte = byte | power_of2(7 - 2 * i);
			}
			i++;
		}
	}
	ft_putchar_fd(byte, ob->output_fd);
	return (counter);
}

int		print_inst(t_vars *ob, char **inst, int counter)
{
	int		begin_address;

	begin_address = counter;
	if (ft_strchr(inst[0], LABEL_CHAR))
		ob->bl_label = 1;
	get_op(inst[ob->bl_label], ob);
	ft_putchar_fd(ob->op_code + 1, ob->output_fd);
	counter++;
	counter += print_encoding(ob, ob->op_code, inst,
			op_tab[ob->op_code].num_args);
	counter += print_params(ob, inst, ob->op_code, begin_address);
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

	counter = 2189;
	while ((get_next_line(fd, &line) > 0))
	{
		ob->bl_label = 0;
		if (!all_whitespace(line))
		{
			inst = ft_strsplit(line, " ,	");
			if (ft_strcmp(inst[0], NAME_CMD_STRING) == 0 || 
					ft_strcmp(inst[0], COMMENT_CMD_STRING) == 0)
				print_name(ob, inst, line);
			else
			{
				if ((counter = print_inst(ob, inst, counter)) == -1)
					return (-1);
				free_split(inst);
			}
		}	
		free(line);
	}
	return (1);
}
