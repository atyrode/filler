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

/*
 ** Those includes might need to get removed before giving the project
 ** Todo: Add these as a preprocessor/makefile rule?
*/

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void		piece_placement_viewer(int x, int y, int color, t_game_state game);
void		heatmap_viewer(t_game_state game);
void		board_viewer(t_game_state game);

/*
 ** End of might remove
*/

# define KO 1
# define OK 0

# define VALID 1
# define INVALID 0

int			parser(t_game_state *game, int first_parse);
int			solver(t_game_state game);
int			algorithm(int x, int y, t_game_state game);
void		skip_line(char **line);
void		ft_exit(char *str);
void		piece_position_sender(int x, int y);
void		fill_heatmap(t_game_state game);

#endif
