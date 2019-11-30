/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/19 05:38:52 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				free_the_world(t_game_state *game, int old_piece_height)
{
	int				x;

	x = -1;
	while (++x < game->map.height)
		free(game->map.table[x]);
	free(game->map.table);
	x = -1;
	while (++x < old_piece_height)
		free(game->piece.table[x]);
	free(game->piece.table);
	x = -1;
	while (++x < game->map.height)
		free(game->heatmap[x]);
	free(game->heatmap);
}

/*
 ** The main function represents the game loop. It calls the different functions
 ** of the game all the way to the solving algorithm.
*/

int					main(void)
{
	t_game_state	game;
	char			*line;
	int				old_piece_height;
	int				value;

	value = 1;
	ft_bzero(&game, sizeof(t_game_state));
	get_next_line(0, &line);
	if (ft_strlen(line) < 11 || (line[10] != '1' && line[10] != '2'))
		return (0);
	game.challenger.sign = (line[10] == '1' ? 'O' : 'X');
	game.opponent.sign = (game.challenger.sign == 'O' ? 'X' : 'O');
	free(line);
	while (1)
	{
		old_piece_height = parser(&game);
		value = solver(game);
		free_the_world(&game, old_piece_height);
		if (value == 2147483647)
			break ;
	}
	return (0);
}
