/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tholzheu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:49:47 by tholzheu          #+#    #+#             */
/*   Updated: 2019/02/01 14:58:26 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static t_windows	*new_t_window(WINDOW *win)
{
	t_windows	*new;

	new = (t_windows *)malloc(sizeof(t_windows));
	if (!new)
		return (NULL);
	new->win = win;
	new->next = NULL;
	return (new);
}

void				add_window_back(t_windows *window_head, WINDOW *win)
{
	t_windows	*cur;
	t_windows	*new;

	new = new_t_window(win);
	if (!window_head)
	{
		window_head = new;
		return ;
	}
	cur = window_head;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}

static WINDOW 	*create_mainwin(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	wborder(local_win, '>', '<', 'V', 'V', '>', '<', '>', '<');
	/*box(local_win, 0 , 0);*/
	wrefresh(local_win);
	return (local_win);
}

/*static void 	destroy_win(WINDOW *local_win)*/
/*{	*/
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	/*wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');*/
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	/*wrefresh(local_win);*/
	/*delwin(local_win);*/
/*}*/

static WINDOW 	*create_sidewin(int height, int width, int starty, int startx)
{	
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);
	return (local_win);
}

static void		init_windows(t_windows *window_head)
{
	int		startx;
	int		starty;
	int		width;
	int		height;
	WINDOW *my_win;

	height = LINES; // 75
	width = height * 3;
	starty = (LINES - height) / 2;	/* Calculating for a center placement */
	startx = (COLS - width) / 2;	/* of the window		*/
	refresh();
	my_win = create_mainwin(height, width, starty, startx);
	add_window_back(window_head, my_win);

	height = LINES / 2.5;
	width = height * 1.7;
	starty = 0;
	startx = 0;
	refresh();
	create_sidewin(height, width, starty, startx);

	starty = height;
	refresh();
	create_sidewin(height, width, starty, startx);

	starty = height * 2;
	startx = 0;
	height = LINES / 5;
	width = height * 3.5;
	refresh();
	create_sidewin(height, width, starty, startx);

	height = LINES / 2.5;
	width = height * 1.7;
	starty = 0;
	startx = 308;
	refresh();
	create_sidewin(height, width, starty, startx);

	starty = height;
	startx = 308;
	height = LINES / 2.5;
	width = height * 1.7;
	refresh();
	create_sidewin(height, width, starty, startx);

	starty = height * 2;
	startx = 308;
	height = LINES / 5;
	width = height * 3.5;
	refresh();
	create_sidewin(height, width, starty, startx);
}

void	 		graphics(void)
{	
	t_windows	*window_head;

	initscr();			/* Start curses mode 		*/
	init_windows(window_head);
	getch();
	endwin();			/* End curses mode		  */
}

int				main(void)
{
	graphics();
	return (0);
}
