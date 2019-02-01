/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:16:48 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/02/01 15:44:50 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Validate and fill the player data and check the -n flag
*/

int		check_size(t_player **fplayer, char *prog, t_arena *arena)
{
	int		i;
	int		addr;
	int		actual_size;

	i = 0;
	addr = COMMENT_LENGTH + PROG_NAME_LENGTH + 16;
	actual_size = (*fplayer)->total_size - PROG_NAME_LENGTH - 16 -
	COMMENT_LENGTH;
	ft_printf("actual weight: %d bytes\n", actual_size);
	ft_printf("total weight: %d bytes\n\n", (*fplayer)->total_size);
	(*fplayer)->prog = malloc(actual_size);
	ft_printf("instruction program\n");
	while (i < actual_size)
	{
		(*fplayer)->prog[i++] = prog[addr++];
		ft_printf("%.2x ", (*fplayer)->prog[i - 1]);
	}
	ft_printf("\n");
	if ((*fplayer)->next)
		ft_printf("\nSizes checked for and %s\n", (*fplayer)->name,
		(*fplayer)->next->name);
	if (actual_size != (*fplayer)->prog_size ||
	(*fplayer)->prog_size > CHAMP_MAX_SIZE)
		return (print_error(1, *fplayer, arena));
	return (1);
}

int		verify_program(t_arena *arena, t_player **fplayer, char *prog, int size)
{
	int		magic;

	magic = 0xf383ea00;
	if (ft_memcmp(prog, &magic, 4) != 0)
		return (print_error(6, *fplayer, arena));
	if (((*fplayer)->first == 2 || (*fplayer)->first == 0) &&
	(*fplayer)->pnum == 0)
	{
		*fplayer = add_player(fplayer);
		ft_printf("\n\nplayer %s added to %s\n\n", (*fplayer)->name,
		(*fplayer)->next->name);
	}
	(*fplayer)->first = 2;
	(*fplayer)->name = ft_strdup(prog + 4);
	mem_to_int(&(*fplayer)->prog_size, 136, prog, 4);
	(*fplayer)->comment = ft_strdup(prog + 128 + 12);
	(*fplayer)->total_size = size;
	ft_printf("in this corner we have: %s\n", (*fplayer)->name);
	ft_printf("comment?: %s\n", (*fplayer)->comment);
	if (check_size(fplayer, prog, arena) == -1)
		return (-1);
	return (0);
}

int		init_player(t_arena *arena, t_player **fplayer, int i)
{
	int		fd;
	char	buf;
	char	program[PROG_MAX_SIZE];
	int		j;

	j = 0;
	if ((fd = open(arena->argv[i], O_RDONLY)) == -1)
	{
		ft_printf("fd %d\n", fd);
		(*fplayer)->name = arena->argv[i];
		return (print_error(5, *fplayer, arena));
	}
	ft_printf("fd %d\n", fd);
	while (read(fd, &buf, 1) > 0)
		program[j++] = buf;
	close(fd);
	if (verify_program(arena, fplayer, program, j) == -1)
		return (print_error(3, *fplayer, arena));
	return (1);
}

void	add_player_num(t_arena *arena, t_player **fplayer, int i)
{
	if ((*fplayer)->next != NULL)
		*fplayer = add_player(fplayer);
	(*fplayer)->pnum = ft_atoi(arena->argv[i + 1]);
	ft_printf("player number: %d\n", (*fplayer)->pnum);
}

int		get_player(t_arena *arena, t_player **fplayer, int *i)
{
	if (ft_strcmp(arena->argv[*i], "-n") == 0)
	{
		if (!arena->argv[*i + 1] || ft_isdigitstr(arena->argv[*i + 1]) == -1)
			return (print_error(2, *fplayer, arena));
		else
		{
			add_player_num(arena, fplayer, *i);
			*i = *i + 2;
		}
	}
	if (init_player(arena, fplayer, *i) == -1)
		return (-1);
	return (1);
}
