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
	t_coords		*coords;
	char			representation[15000];
}					t_game_object;

/*
 ** This structure represents the game as its current state
 ** it stores a map game object and a piece game object
 ** as well as different informations about the game
*/

typedef struct 		s_game_state
{
	t_game_object	*map;
	t_game_object	*piece;
	int				turn;
	int				player_number;
}					t_game_state;

#endif
