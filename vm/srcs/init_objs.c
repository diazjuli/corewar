/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 20:30:51 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/02/01 15:28:10 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	init_arena_ob(t_arena *arena, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		arena->memory[i] = 0;
		i++;
	}
	arena->argc = argc;
	arena->argv = argv;
	arena->flags = (t_flag*)malloc(sizeof(t_flag));
	arena->flags->interactive = 0;
	arena->flags->dump_bl = 0;
	arena->flags->dump_cycles = 0;
	arena->num_plys = 0;
}
