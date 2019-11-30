/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/19 05:38:52 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
 ** This structure represents a game object with its width, length
 ** and a two dimensional array filled with characters
*/

typedef struct		s_game_object
{
	int				height;
	int				length;
	int				size;
	char 			**table;
}					t_game_object;

/*
 ** This structure represents the player in the current game state
 ** It stores the player sign and its starting coordinates
*/

typedef struct		s_player
{
	char 			sign;
	int				x;
	int				y;
}					t_player;

/*
 ** This structure represents the game as its current state.
 ** It stores two game objects (current map and piece) and a player
*/

typedef struct		s_game_state
{
	t_game_object	map;
	t_game_object	piece;
	t_player		challenger;
	t_player		opponent;
	int				turn;
	int				**heatmap;
}					t_game_state;

#endif
