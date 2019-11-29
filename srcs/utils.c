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

void		piece_placement_viewer(int x, int y, int p_color, t_game_state game)
{
	int 	i;
	int 	j;
	int		color;


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

void		board_printer(t_game_state game)
{
	int 	i;
	int 	j;
	int		color;
	char	current;

	i = -1;
	while (++i < game.map.height)
	{
		j = -1;
		while (++j < game.map.length)
		{
			current = game.map.table[i][j];
			if (current == '.')
				color = 1;
			else if (current == 'X')
				color = 7;
			else if (current == 'O')
				color = 5;
			if (game.map.table[i][j])
			ft_printf("%*~%c%~", color, game.map.table[i][j]);
		}
		ft_printf("\n");
	}
}

void		skip_line(char  **line)
{
	get_next_line(0, line);
}