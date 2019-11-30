/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/23 22:40:24 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				swap_if_needed(t_game_state game, int x, int y)
{
	int				abs_value;

	abs_value = game.heatmap[y][x] - game.heatmap[y + 1][x];
	abs_value = (abs_value < 0) ? abs_value * -1 : abs_value;
	if (abs_value > 1)
	{
		if (game.heatmap[y + 1][x] > game.heatmap[y][x])
			game.heatmap[y + 1][x] = game.heatmap[y][x] + 1;
		else
			game.heatmap[y][x] = game.heatmap[y + 1][x] + 1;
	}
}

void				horizontal_and_aura_pass(t_game_state game)
{
	int				x;
	int				y;

	x = -1;
	while (++x < game.map.length)
	{
		y = -1;
		while (++y + 1 < game.map.height)
			swap_if_needed(game, x, y);
		while (y--)
			swap_if_needed(game, x, y);
	}
	// Todo: 99 is a bad idea, it makes the program sometime prefers to place far away
	// it should be weighted toward, but not too much, so that it prefers close but outwards
	x = -1;
	while (++x < game.map.height)
	{
		y = -1;
		while (++y < game.map.length)
			if (game.heatmap[x][y] > 0 && 4 > game.heatmap[x][y])
				game.heatmap[x][y] = 99;
	}
}

void				fill_heatmap(t_game_state game)
{
	int				x;
	int				y;
	int				heat;
	int				current;

	x = -1;
	while (++x < game.map.height)
	{
		// We just skip the line if there's no enemy marker in it
		if (!ft_strchr(game.map.table[x], game.opponent.sign))
			continue;
		current = 0;
		y = -1;
		heat = 0;
		while (++y < game.map.length)
			// Firstly, we check whether Y is on a enemy marker or if we're at
			// the beginning
			if (ft_toupper(game.map.table[x][y]) == game.opponent.sign || y == 0)
			{
				// Depending on the case, we set the first data to its corresponding
				// value
				game.heatmap[x][y] =
				(ft_toupper(game.map.table[x][y]) == game.opponent.sign) ? 0 : 99;

				// We save where we're at, in case we're on an enemy marker and
				// increase Y by one after saving it.
				current = y++;

				// Now we go through the map until we meet another marker,
				// and fill the heatmap value
				heat = 1;
				while (ft_toupper(game.map.table[x][y]) != game.opponent.sign)
					game.heatmap[x][y++] = heat++;

				// Then, if we're not at the end of the map and there's another
				// enemy marker, we go back and fix the value in between
				if (ft_toupper(game.map.table[x][y]) == game.opponent.sign)
				{
					game.heatmap[x][y] = 0;
					heat = 0;

					// We handle the special case in the second part of the OR
					// by using the function that fix the value in between,
					// we trigger it to go further if it's the first marker we met
					// therefore it goes back all the way to the beginning and fix
					// the value in the correct way
					while (game.heatmap[x][y] >= heat || (ft_toupper(game.map.table[x][y]) != game.opponent.sign && y > 0))
						game.heatmap[x][y--] = heat++;
				}

				// And we go back to where we came from
				y = current;
			}
		}
	horizontal_and_aura_pass(game);
	//heatmap_viewer(game);
}

int					algorithm(int x, int y, t_game_state game)
{
	int			i;
	int			j;
	int			fitness;

	fitness = 0;
	i = -1;
	while (++i < game.piece.height)
	{
		j = -1;
		while (++j < game.piece.length)
		{
			if (game.piece.table[i][j] == '*')
				fitness += game.heatmap[x + i][y + j];
		}
	}
	//ft_printf("fitness = %i | coords = %i %i\n", fitness, x, y);
	return (fitness);
}