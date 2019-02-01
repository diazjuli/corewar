/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tholzheu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:01:01 by tholzheu          #+#    #+#             */
/*   Updated: 2019/01/31 12:06:17 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_memory(char memory[MEM_SIZE])
{
	int		addr;

	addr = 0;
	printf("0x");
	while (addr < MEM_SIZE)
	{
		if (addr % 64 == 0)
			printf("%#.4x :", addr);
		else if ((addr + 1) % 64 == 0)
			printf("\n");
		else
			printf(" %.2x", memory[addr] & 255);
		addr++;
	}
}
