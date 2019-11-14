/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/19 05:38:52 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "structures.h"
# ifdef __SIZEOF_UINT128__
#endif

/*
 ** Those includes might need to get removed before giving the project
*/

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef __uint128_t 	uint128;

int						parser(t_game_state	*game);
void					filler(t_game_state *game);
void					solver(t_game_state *game);
void					print_bits(uint128 x, int size, int width);
void					ft_exit(char 		*str);

#endif
