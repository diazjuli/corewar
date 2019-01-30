/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:56:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/01/30 09:20:45 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "../../assembler/includes/op.h"

typedef struct		s_flag
{
	int				dump_bl;
	int				cycles;
	int				n_bl;
	int				n_num;
	int				interactive;
}					t_flag;

typedef struct		s_player
{
	int				reg[16];
	int				carry;
	int				life_bl;
	int				dead;
	int				xy[2];   //start location
	int				pc;
	int				pnum;
	
	t_inst			*inst;
	int				prog_size;
	char			*name;
	char			*comment;
	char			*prog;
	struct s_player *nx;
}					t_player;

typedef struct		s_inst
{
	int 			counter;
	int				op_code;
	unsigned char	ebyte;
	int				arg1;
	int				arg2;
	int				arg3;
	}				t_inst;

typedef struct	s_arena
{
	char		arena[64][MEM_SIZE / 64];
	int			num_plys;
	int			cycle_to_die;
	int			total_cycles;
	int			cycle_counter;
	int			dump;
	int			num;
	int			interactive;
	int			last_alive;
	
}				t_arena;

#endif
