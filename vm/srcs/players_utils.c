/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 20:16:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/02/01 14:34:46 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_player	*create_player(void)
{
	t_player	*player;

	player = (t_player*)malloc(sizeof(t_player));
	player->name = NULL;
	player->comment = NULL;
	player->pnum = 0;
	player->dead = 0;
	player->carry = 0;
	player->life_bl = 0;
	player->inst = NULL;
	player->prog = NULL;
	player->prog_size = 0;
	player->total_size = 0;
	player->first = 0;
	return (player);
}

t_player	*add_player(t_player **head)
{
	t_player	*elem;

	elem = create_player();
	elem->next = *head;
	return (elem);
}

void		print_chararr(char arr[], int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ft_printf("%c", arr[i]);
		i++;
	}
	ft_printf("\n");
}
