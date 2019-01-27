/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 21:08:10 by jdiaz             #+#    #+#             */
/*   Updated: 2019/01/26 16:24:56 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	byte_print(int nb, int bytes, int fd)
{
	int		tmp;

	while (--bytes >= 0)
	{
		tmp = nb; // save the number in 4 bytes
		tmp = tmp >> (8 * bytes); // shift 24 then 16 then 8 then 0
		tmp = tmp & 255; // save only the last byte 
		ft_putchar_fd((char)tmp, fd); // print it in the file
	}
}

int		all_whitespace(char *line)
{
	while(*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

int		power_of2(int exp)
{
	int result;

	result = 1;
	while (exp > 0)
	{
		result *=2;
		exp--;
	}
	return (result);
}

int		get_address(char *str, t_vars *ob, int arg) // str is the label without LABEL_CHAR
{
	t_label *temp;
	size_t	len;

	temp = ob->labels;
	while (temp) // iterating through labels
	{
		len = ft_strlen(str);
		if (len + 1 == ft_strlen(temp->label) && // check why do we have to do it like this
				ft_strncmp(str, temp->label, len) == 0)
			return (temp->address);
		temp = temp->next;
	}
	return (error_message(12, ob->counter, arg));
}

int		print_direct(char *param, t_vars *ob, int begin_address, int arg)
{
	int		num;

	param = param + 1; // skip the DIRECT_CHAR
	if (param[0] == LABEL_CHAR) // if it's a label
	{
		if ((num = get_address(param + 1, ob, arg)) == -1) // get the address that we saved before
			return (-1);
		num = num - begin_address; // dest address - begin_address
	}
	else
		num = ft_atoi(param); // get the number after the DIRECT_CHAR
	byte_print(num, 4, ob->output_fd);
	return (1);
}

int		print_indirect(char *param, t_vars *ob, int begin_address, int arg)
{
	int		num;

	if (param[0] == DIRECT_CHAR) // add 1 to skip the DIRECT_CHAR (if it is DIR)
		param = param + 1;
	if (param[0] == LABEL_CHAR) // if it's a label get the address
	{
		if ((num = get_address(param + 1, ob, arg)) == -1)
			return (-1);
		num = num - begin_address;
	}
	else
		num = ft_atoi(param); // just get the plain number
	byte_print(num, 2, ob->output_fd);
	return (1);
}
