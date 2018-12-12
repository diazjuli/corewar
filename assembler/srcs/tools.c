/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 21:08:10 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/10 22:41:08 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler.h>

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

int		get_address(char *str, t_vars *ob)
{
	t_label *temp;
	size_t	len;

	temp = ob->labels;
	while (temp)
	{
		len = ft_strlen(str);
		if (len + 1 == ft_strlen(temp->label) &&
				ft_strncmp(str, temp->label, len) == 0)
			return (temp->address);
		temp = temp->next;
	}
	return (-1);
}

int		print_direct(char *param, t_vars *ob, int begin_address)
{
	int		num;
	int 	i;
	int		temp;

	i = 3;
	param = param + 1;
	if (*(param + 1) == LABEL_CHAR)
	{
		num = get_address(param + 1, ob);
		num = begin_address - num;
	}
	else
		num = ft_atoi(param);
	while (i >= 0)
	{
		temp = num;
		temp = temp >> (8 * i);
		temp = temp & 255;
		ft_putchar_fd((char)temp, ob->output_fd);
		i--;
	}
	return (1);
}

int		print_indirect(char *param, t_vars *ob, int begin_address)
{
	int		num;
	char	byte1;
	char	byte2;

	byte1 = 0;
	byte2 = 0;
	if (*(param + 1) == LABEL_CHAR)
	{
		num = get_address(param + 2, ob);
		num = begin_address - num;
	}
	else
		num = ft_atoi(param + 1);
	byte2 = (char)(num & 255);
	byte1 = (char)(num >> 8);
	if (num < 0)
		byte1 = byte1 | 128;
	ft_putchar_fd(byte1, ob->output_fd);
	ft_putchar_fd(byte2, ob->output_fd);
	return (1);
}