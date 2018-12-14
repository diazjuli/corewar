/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:57 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/13 21:24:36 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		print_name(t_vars *ob, char *line, int fd)
{
	int	length;
	int i;

	i = 3;
	while (i >= 0)
	{
		length = COREWAR_EXEC_MAGIC;
		length = length >> (8 * i);
		length = length & 255;
		ft_putchar_fd((char)length, ob->output_fd);
		i--;
	}
	length = PROG_NAME_LENGTH + 4;
	ft_putstr_fd(ob->player_name, ob->output_fd);
	i = ft_strlen(ob->player_name);
	while (i++ < length)
		ft_putchar_fd(0, ob->output_fd);
	ft_putchar_fd(17, ob->output_fd);
	length = COMMENT_LENGTH + 8;
	i = ft_strlen(ob->comment);
	ft_putstr_fd(ob->comment, ob->output_fd);
	while (++i < length)
		ft_putchar_fd(0, ob->output_fd);
	i = 0;
	while (i < ob->begin_line)
	{
		get_next_line(fd, &line);
		free(line);
		i++;
	}
	return (1);
}

int		print_params(t_vars *ob, char **inst, int op_code, int begin_address)
{
	int	counter;
	int i;

	i = ob->bl_label + 1;
	counter = 0;
	while (inst[i] != NULL && inst[i][0] != COMMENT_CHAR && counter != -1)
	{
		if (inst[i][0] == 'r')
		{
			counter++;
			ft_putchar_fd(ft_atoi(inst[i] + 1), ob->output_fd);
		}
		else if (inst[i][0] == DIRECT_CHAR && check_index(op_code) == -1)
		{

			counter = print_direct(inst[i], ob, begin_address) == -1 ? -1
				: counter + 4;
		}
		else
		{
			counter = print_indirect(inst[i], ob, begin_address) == -1 ?
				-1 : counter + 2;
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
		ft_putchar_fd(byte, ob->output_fd);
	}
	return (counter);
}

int		print_inst(t_vars *ob, char **inst, int counter)
{
	int		begin_address;
	int		temp;

	begin_address = counter;
	if (ft_strchr(inst[0], LABEL_CHAR))
		ob->bl_label = 1;
	if (inst[0][0] == COMMENT_CHAR || (ob->bl_label == 1 &&
			(!inst[1] || inst[1][0] == COMMENT_CHAR)))
	{
		free_split(inst);
		return (counter);
	}
	get_op(inst[ob->bl_label], ob);
	ft_putchar_fd(ob->op_code + 1, ob->output_fd);
	counter++;
	counter += print_encoding(ob, ob->op_code, inst,
			op_tab[ob->op_code].num_args);
	temp = print_params(ob, inst, ob->op_code, begin_address);
	counter = temp == -1 ? -1 : counter + temp; 
	free_split(inst);
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
	line = NULL;
	print_name(ob, line, fd);
	while ((get_next_line(fd, &line) > 0))
	{
		ob->bl_label = 0;
		if (!all_whitespace(line))
		{
			inst = ft_strsplit(line, " ,	");
			if ((counter = print_inst(ob, inst, counter)) == -1)
				return (-1);
		}
		free(line);
	}
	return (1);
}
