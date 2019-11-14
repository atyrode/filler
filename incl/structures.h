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
 ** This structure represents a set of coordinates
 ** represented by two ints: x and y
*/

typedef struct		s_coords
{
	int				x;
	int				y;
}					t_coords;

/*
 ** This structure represents a game object that
 ** has a set of coordinates (x, y) and a string representation
*/

typedef struct		s_game_object
{
	t_coords		coords;
	__uint128_t		*bitfield;
	__uint128_t		*bitfield2;
}					t_game_object;

/*
 ** This structure represents the player in the current game state
 ** It stores the player sign
*/

typedef struct		s_player
{
	char 			sign;
	t_coords		starting_coords;
}					t_player;

/*
 ** This structure represents the game as its current state.
 ** It stores two game objects (current map and piece) and a  player
*/

typedef struct		s_game_state
{
	t_game_object	map;
	t_game_object	piece;
	t_player		player;
	int				turn;
}					t_game_state;

#endif
