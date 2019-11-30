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

void				free_the_world(t_game_state *game)
{
	int				x;

	//ft_printf("%p || %p || %p\n", game->map.table, game->piece.table, game->heatmap);
	x = -1;
	while(++x < game->map.height)
	{
		//ft_printf("map table: %p\n", game->map.table[x]);
		free(game->map.table[x]);
	}
	free(game->map.table);

	x = -1;
	while(++x < game->piece.height)
	{
		//ft_printf("piece table: %p\n", game->piece.table[x]);
		free(game->piece.table[x]);
	}
	free(game->piece.table);

	x = -1;
	while(++x < game->map.height)
	{
		//ft_printf("heatmap: %p\n", game->heatmap[x]);
		free(game->heatmap[x]);
	}
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

	ft_bzero(&game, sizeof(t_game_state));
	get_next_line(0, &line);
	if (ft_strlen(line) < 11 || (line[10] != '1' && line[10] != '2'))
		return (0);
	game.challenger.sign = (line[10] == '1' ? 'O' : 'X');
	game.opponent.sign = (game.challenger.sign == 'O' ? 'X' : 'O');
	free(line);
	while (1)
	{
		ft_printf("first\n");
		parser(&game);
		ft_printf("second\n");
		solver(game);
		ft_printf("test final\n");
		//free_the_world(&game);
	}
	return (0);
}
