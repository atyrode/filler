/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/23 22:40:24 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

// Todo: Some sort of algorithm to determine where to place the piece?
// Todo: It seems like I am done with determining wether a place can be place
// Todo: While abiding to the gamerules

int				check_piece_superposition(int x, int y, t_game_state game)
{
	int			i;
	int			j;
	int			challenger_count;
	int			opponent_count;

	challenger_count = 0;
	opponent_count = 0;
	i = -1;
	while (++i < game.piece.height)
	{
		j = -1;
		while (++j < game.piece.length)
		{
			if (game.piece.table[i][j] == '*')
			{
				if (ft_toupper(game.map.table[x + i][y + j]) ==
														game.challenger.sign)
					challenger_count++;
				else if (ft_toupper(game.map.table[x + i][y + j]) ==
														game.opponent.sign)
					opponent_count++;
			}
		}
	}
	if (challenger_count != 1 || opponent_count > 0)
		return (KO);
	return (OK);
}

int				check_piece_overflow(int x, int y, t_game_state game)
{
	if ((x + game.piece.height) <= game.map.height
	&& (y + game.piece.length) <= game.map.length)
		return (OK);
	return (KO);
}

int				check_position_validity(int x, int y, t_game_state game)
{
	if (check_piece_overflow(x, y, game)
	|| check_piece_superposition(x, y, game))
		return (INVALID);
	return (VALID);
}

void			solver(t_game_state	game)
{
	int			x;
	int			y;

	x = 0;
	while (x + game.piece.height <= game.map.height)
	{
		y = 0;
		while (y < game.map.length)
		{
			//ft_printf("=====================\n");
			//piece_placement_viewer(x, y, 4, game);
			if (check_position_validity(x, y, game))
			{
				//ft_printf("x = [%i] | y = [%i]\n", x, y);
				ft_putstr(ft_itoa(x));
				ft_putchar(' ');
				ft_putstr(ft_itoa(y));
				ft_putchar('\n');
				return ;
			}
			y++;
		}
		x++;
	}
}


