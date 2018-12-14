/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 21:08:10 by jdiaz             #+#    #+#             */
/*   Updated: 2018/12/13 23:25:15 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

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
	if (param[0] == LABEL_CHAR)
	{

		if ((num = get_address(param + 1, ob)) == -1)
			return (-1);
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
	int		i;
	int		temp;

	i = 1;
	if (param[0] == DIRECT_CHAR)
		param = param + 1;
	if (param[0] == LABEL_CHAR)
	{
		if ((num = get_address(param + 1, ob)) == -1)
			return (-1);
		num = num - begin_address;
	}
	else
		num = ft_atoi(param);
	printf("num: %d ", num);
	while (i >= 0)
	{
		temp = num;
		temp = temp >> (8 * i);
		temp = temp & 255;
		printf("byte: %d ", temp);
		ft_putchar_fd((char)temp, ob->output_fd);
		i--;
	}
	printf("\n");
	return (1);
}
