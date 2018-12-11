/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:28:57 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/10 22:34:16 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

int		print_name(t_vars *ob, char **inst)
{
	int	length;
	int i;

	i = 0;
	length = ft_strcmp(inst[0], NAME_CMD_STRING) == 0 ?
		PROG_NAME_LENGTH : COMMENT_LENGTH;
	i = ft_strlen(inst[1]);
	ft_putstr_fd(inst[1], ob->output_fd);
	while (i < length)
	{
		ft_putchar_fd(0, ob->output_fd);
		i++;
	}
	return (1);
}

int		print_params(t_vars *ob, char **params, int op_code, int begin_address)
{
	int	counter;

	counter = 0;
	while (*params != NULL)
	{
		if (params[0][0] == 'r')
		{
			counter++;
			ft_putchar_fd(ft_atoi(*(params + 1)), ob->output_fd);
		}
		else if (params[0][0] == DIRECT_CHAR && check_index(op_code) == -1)
		{
			counter += 4;
			print_direct(params[0], ob, begin_address);
		}
		else
		{
			counter += 2;
			print_indirect(params[0], ob, begin_address);
		}
		params++;
	}
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
			if (params[i][0] == 'r')
				byte = byte | power_of2(6 - 2 * i);
			else if (params[i][0] == DIRECT_CHAR)
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
	char **params;
	int begin_address;

	begin_address = counter;
	if (ft_strchr(inst[0], LABEL_CHAR))
		ob->bl_label = 1;
	params = ft_strsplit(inst[ob->bl_label + 1], SEPARATOR_CHAR);
	ob->op_code = get_op(inst[ob->bl_label]);
	ft_putchar_fd(ob->op_code, ob->output_fd);
	counter++;
	counter += print_encoding(ob, ob->op_code, params,
			op_tab[ob->op_code].num_args);
	counter += print_params(ob, params, ob->op_code, begin_address);
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

	counter = 2176;
	while ((get_next_line(fd, &line) > 0))
	{
		ob->bl_label = 0;
		inst = ft_strsplit(line, ' ');
		if (ft_strcmp(inst[0], NAME_CMD_STRING) == 0 || 
				ft_strcmp(inst[0], COMMENT_CMD_STRING) == 0)
			print_name(ob, inst);
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
