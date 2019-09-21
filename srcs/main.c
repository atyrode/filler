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

int main(void)
{
	char 			buffer[15000];
	t_game_state	game;

	while((read(0, buffer, 15000)));
	if (!parser(&game, buffer))
		return (-1);

	dprintf(2, "(main) Player number = %d\n", game.player_number);
	dprintf(2, "(main) Map x = [%d], y = [%d]\n", game.map->coords->x, game.map->coords->y);
	dprintf(2, "(main) Map representation = [%s]\n", game.map->representation);
	dprintf(2, "(main) Piece x = [%d], y = [%d]\n", game.piece->coords->x, game.piece->coords->y);
	dprintf(2, "(main) Piece representation = [%s]\n", game.piece->representation);
	write(1, "10 10\n", 6);
	return (0);
}
