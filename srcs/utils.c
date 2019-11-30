/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/19 05:38:52 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		piece_position_sender(int x, int y)
{
	//ft_printf("x = [%i] | y = [%i]\n", x, y);
	ft_putstr(ft_itoa(x));
	ft_putchar(' ');
	ft_putstr(ft_itoa(y));
	ft_putchar('\n');
}

void		piece_placement_viewer(int x, int y, int p_color, t_game_state game)
{
	int 	i;
	int 	j;
	int		color;

	ft_printf("=========================================\n");
	i = -1;
	while (++i < game.map.height)
	{
		j = -1;
		while (++j < game.map.length)
		{
			if (game.map.table[i][j] == '.')
				color = 1;
			else if (game.map.table[i][j] == 'X')
				color = 7;
			else if (game.map.table[i][j] == 'O')
				color = 5;
			if ((i >= x && i < x + game.piece.height)
			&& (j >= y && j < y + game.piece.length)
			&& game.piece.table[i - x][j - y] != '.')
				ft_printf("%*~%c%~", p_color, game.challenger.sign);
			else
				ft_printf("%*~%c%~", color, game.map.table[i][j]);
		}
		ft_printf("\n");
	}
}

void		heatmap_viewer(t_game_state game)
{
	int		x;
	int		y;

	x = 0;
	while (x < game.map.height)
	{
		y = 0;
		while (y < game.map.length)
		{
			ft_printf("%02i ", game.heatmap[x][y]);
			y++;
		}
		ft_printf("\n\n");
		x++;
	}

}

void		skip_line(char  **line)
{
	get_next_line(0, line);
}

void				ft_exit(char *str)
{
	ft_putstr(str);
	exit(0);
}