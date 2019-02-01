/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tholzheu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:13:28 by tholzheu          #+#    #+#             */
/*   Updated: 2019/01/31 11:24:53 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_memory(char memory[MEM_SIZE]);

int		main(void)
{
	char	memory[MEM_SIZE];
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		memory[i] = i++;
	}
	print_memory(memory);
	return (0);
}
