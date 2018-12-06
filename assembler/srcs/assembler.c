/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:09:01 by jcruz-y-          #+#    #+#             */
/*   Updated: 2018/12/05 18:33:19 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


int        main(int argc, char **argv)
{
    t_vars	ob;
	int		fd;

    if (argc != 2)
        printf("incorrect number of arguments\n");
    else
    {
        if (lexer(argv[1], &ob) == -1)
            return(printf("lexical error in the input file\n"));
		if (parser(argv[1], &ob) == -1)
			return(printf("parser/label error in the input file\n"));
        fd = open("new_file", O_WRONLY);
        generator(fd, &ob);
        close(fd);
    }
    return (0);
}
