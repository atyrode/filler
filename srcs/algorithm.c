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

void			swap_if_needed(t_game_state game, int x, int y)
{
	int			abs_value;

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

void			horizontal_and_aura_pass(t_game_state game)
{
	int			x;
	int			y;
	int			aura;

	x = -1;
	while (++x < game.map.length)
	{
		y = -1;
		while (++y + 1 < game.map.height)
			swap_if_needed(game, x, y);
		while (y--)
			swap_if_needed(game, x, y);
	}
	aura = (game.map.size < 500) ? 2 : 3;
	aura = (game.map.size < 1000) ? 3 : 4;
	x = -1;
	while (++x < game.map.height)
	{
		y = -1;
		while (++y < game.map.length)
			if (game.heatmap[x][y] > 0 && aura > game.heatmap[x][y])
				game.heatmap[x][y] += aura * 2;
	}
}

void			vertical_pass(t_game_state game, int x, char **map, char sign)
{
	int			heat;
	int			current;
	int			y;

	current = 0;
	y = -1;
	while (++y < game.map.length)
		if (ft_toupper(map[x][y]) == sign || y == 0)
		{
			game.heatmap[x][y] = (ft_toupper(map[x][y]) == sign) ? 0 : 99;
			current = y++;
			heat = 1;
			while (y < game.map.length && ft_toupper(map[x][y]) != sign)
				game.heatmap[x][y++] = heat++;
			if (ft_toupper(map[x][y]) == sign)
			{
				game.heatmap[x][y] = 0;
				heat = 0;
				while (y >= 0 && ((ft_toupper(map[x][y]) != sign)
				|| game.heatmap[x][y] >= heat))
					game.heatmap[x][y--] = heat++;
			}
			y = current;
		}
}

void			fill_heatmap(t_game_state game)
{
	int			x;

	x = -1;
	while (++x < game.map.height)
	{
		if (!ft_strchr(game.map.table[x], game.opponent.sign))
			continue ;
		vertical_pass(game, x, game.map.table, game.opponent.sign);
	}
	horizontal_and_aura_pass(game);
}

int				algorithm(int x, int y, t_game_state game)
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
	return (fitness);
}
