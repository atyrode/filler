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

//TODO: Ne pas segfault s'il n'y a que un seul input

void				free_map(t_game_state *game)
{
	int				x;

	x = -1;
	while (++x < game->map.height)
	{
		free(game->map.table[x]);
		free(game->heatmap[x]);
	}
	free(game->heatmap);
	free(game->map.table);
}

void				free_piece(t_game_state *game, int old_piece_height)
{
	int				x;

	x = -1;
	while (++x < old_piece_height)
		free(game->piece.table[x]);
	free(game->piece.table);
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
	int				first_parse;

	first_parse = 1;
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
		if (!(old_piece_height = parser(&game, first_parse)))
			break;
		value = solver(game);
		free_piece(&game, old_piece_height);
		if (value == 2147483647)
			break ;
		first_parse = 0;
	}
	if (old_piece_height)
		free_map(&game);
	return (0);
}
