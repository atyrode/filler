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
			if (game.piece.table[i][j] == '*')
			{
				if (ft_toupper(game.map.table[x + i][y + j])
				== game.challenger.sign)
					challenger_count++;
				else if (ft_toupper(game.map.table[x + i][y + j])
				== game.opponent.sign)
					opponent_count++;
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

int				solver(t_game_state game)
{
	int			coords[2];
	int			fitness[2];
	int			best_coords[2];

	best_coords[0] = 0;
	best_coords[1] = 0;
	fitness[0] = 2147483647;
	coords[0] = -1;
	while (++coords[0] + game.piece.height <= game.map.height)
	{
		coords[1] = -1;
		while (++coords[1] < game.map.length)
			if (check_position_validity(coords[0], coords[1], game))
			{
				fitness[1] = algorithm(coords[0], coords[1], game);
				if (fitness[1] < fitness[0])
				{
					fitness[0] = fitness[1];
					best_coords[0] = coords[0];
					best_coords[1] = coords[1];
				}
			}
	}
	piece_position_sender(best_coords[0], best_coords[1]);
	return (fitness[0]);
}
