/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:57 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/01/26 16:24:41 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		print_name(t_vars *ob, int fd) // there is no test for max comment size or max player size
{
	int	length;
	int i;

	byte_print(COREWAR_EXEC_MAGIC, 4, ob->output_fd);
	length = PROG_NAME_LENGTH + 4; // + 4 = 4 extra NULL bytes
	ft_putstr_fd(ob->player_name, ob->output_fd); // print the name of the player
	i = ft_strlen(ob->player_name);
	while (i++ < length) // use the length of the player name to calculate the rest of 0's bytes
		ft_putchar_fd(0, ob->output_fd);
	byte_print(ob->prog_size, 4, ob->output_fd);
	length = COMMENT_LENGTH + 4;
	i = ft_strlen(ob->comment);
	ft_putstr_fd(ob->comment, ob->output_fd);
	while (i++ < length) // use the length of the comment to calculate the rest of 0's bytes
		ft_putchar_fd(0, ob->output_fd);
	i = 0;
	skip_lines(ob->begin_line, fd);
	ob->counter += ob->begin_line;
	return (1);
}

int		print_params(t_vars *ob, char **inst, int op_code, int begin_address)
{
	int	counter;
	int i;

	i = ob->bl_label + 1;
	counter = 0;
	while (inst[i] != NULL && inst[i][0] != COMMENT_CHAR && counter != -1) // while inst exists and is not a comment
	{
		if (inst[i][0] == 'r') // if is a register
		{
			counter++;
			ft_putchar_fd(ft_atoi(inst[i] + 1), ob->output_fd); // print the reg number
		}
		else if (inst[i][0] == DIRECT_CHAR && check_index(op_code) == -1) // if is direct and is not index
			counter = print_direct(inst[i], ob, begin_address, i - ob->bl_label) == -1 ? -1
				: counter + 4;
		else
			counter = (print_indirect(inst[i], ob, begin_address, i - ob->bl_label) == -1) ?
				-1 : counter + 2;
		i++;
	}
	return (counter);
}

int		print_encoding(t_vars *ob, int op_code, char **inst, int num_params)
{
	int	byte;
	int i;

	i = 0;
	byte = 0;
	if (op_tab[op_code].encoding_byte == 1)
	{
		while (i < num_params) // create encoding byte from all params
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
		return (1);
	}
	return (0);
}

int		print_inst(t_vars *ob, char **inst, int counter)
{
	int		begin_address;
	int		temp;

	begin_address = counter;
	if (ft_strchr(inst[0], LABEL_CHAR)) // if the line starts with a label bl_label = 1
		ob->bl_label = 1;
	if (inst[0][0] == COMMENT_CHAR || (ob->bl_label == 1 &&
			(!inst[1] || inst[1][0] == COMMENT_CHAR)))
	{
		free_split(inst);
		return (counter);
	}
	get_op(inst[ob->bl_label], ob); // save the op_code - 1 in t_vars ob using the mnemonic
	ft_putchar_fd(ob->op_code + 1, ob->output_fd); // print op_code
	counter++;
	counter += print_encoding(ob, ob->op_code, inst, // add 1 if it has encoding byte and prints it
			op_tab[ob->op_code].num_args);
	temp = print_params(ob, inst, ob->op_code, begin_address); // print params according to their types
	counter = (temp == -1) ? -1 : counter + temp;
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

	counter = 2192;
	line = NULL;
	ob->counter = 0;
	print_name(ob, fd); // prints magic number, name, comment, size
	while ((get_next_line(fd, &line) > 0)) // we skipped already to the beginning of the program
	{
		ob->bl_label = 0;
		ob->counter++;
		if (!all_whitespace(line)) // if the line is not empty
		{
			inst = ft_strsplit(line, " ,\t"); // change here
			if ((counter = print_inst(ob, inst, counter)) == -1)
				return (-1);
		}
		free(line);
	}
	return (1);
}
