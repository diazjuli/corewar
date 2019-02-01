/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:01:01 by tholzheu          #+#    #+#             */
/*   Updated: 2019/02/01 15:48:04 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_memory(char memory[MEM_SIZE])
{
	int		addr;

	addr = 0;
	printf("0x");
	printf("%x\n", memory[0]);
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
