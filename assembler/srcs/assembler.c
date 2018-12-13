/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:09:01 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/12 21:52:44 by jdiaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		get_op(char *mnemonic, t_vars *ob)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(op_tab[i].mnemonic, mnemonic) == 0)
		{
			ob->op_code = i;
			return (i);
			printf("op_code = %d\n", i);
		}
		i++;
	}
	return (-1);
}

int	free_split(char **inst)
{
	int	i;

	i = 0;
	if (inst)
	{
		while (inst[i])
		{
			free(inst[i]);
			i++;
		}
		free(inst);
	}
	return (0);
}	

int		main(int argc, char **argv)
{
	t_vars	ob;
	int		fd;

	ob.counter = 0;
	if (argc != 2)
		printf("incorrect number of arguments\n");
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (lexer(&ob, fd) == -1 || fd == -1)
			return(printf("error in the input file\n"));
		printf("lexer is good\n\n");
		fd = open(argv[1], O_RDONLY);
		get_label_address(&ob, fd);
		printf("got addresses\n");
		close(fd);
		fd = open(argv[1], O_RDONLY);
		ob.output_fd = open("new_file.cor", O_CREAT | O_RDWR, 0644);
		printf("outpufd: %d\n", ob.output_fd);
		if (generator(&ob, fd) == -1)
			return (printf("incorrect label used as a parameter\n"));
		close(fd);
		close(ob.output_fd);
	}
	return (0);
}
