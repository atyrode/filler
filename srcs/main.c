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

void				ft_exit(char *str)
{
	ft_putstr(str);
	exit(0);
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
		parser(&game);
		solver(game);
	}
	return (0);
}
