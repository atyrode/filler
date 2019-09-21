/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 22:14:30 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/19 05:38:52 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				get_piece_info(t_game_object *piece, char *format)
{
	int				axis;

	axis = 0;
	while (*format != '\n')
	{
		if (ft_isdigit(*format) && axis < 2)
		{
			if (axis == 0)
				piece->coords->x = ft_atoi(format);
			else
				piece->coords->y = ft_atoi(format);
			axis++;
			while(ft_isdigit(*format))
				format++;
		}
		format++;
	}
	ft_strcpy(piece->representation, format);
}

void				get_map_info(t_game_object *map, char *format)
{
	int				axis;
	char			*piece;
	int				len;

	axis = 0;
	while (*format != '\n')
	{
		if (ft_isdigit(*format) && axis < 2)
		{
			if (axis == 0)
				map->coords->x = ft_atoi(format);
			else
				map->coords->y = ft_atoi(format);
			axis++;
			while(ft_isdigit(*format))
				format++;
		}
		format++;
	}
	piece = ft_strstr(format, "Piece");
	len = piece - format;
	ft_strncpy(map->representation, format, len);
}

int					get_player_number(char *format)
{
	if (ft_strstr(format, "$$$ exec p1"))
		return (1);
	else if (ft_strstr(format, "$$$ exec p2"))
		return (2);
	else
		return (0);
}

int					parser(t_game_state	*game, char *buffer)
{
	t_game_object	map;
	t_game_object	piece;
	t_coords		piece_coords;
	t_coords		map_coords;

	game->map = &map;
	game->map->coords = &map_coords;
	game->piece = &piece;
	game->piece->coords = &piece_coords;

	game->player_number = get_player_number(buffer);
	if (!game->player_number)
		return (0);
	buffer = ft_strstr(buffer, "Plateau");
	if (!buffer)
		return (0);
	get_map_info(&map, buffer);
	buffer = ft_strstr(buffer, "Piece");
	if (!buffer)
		return (0);
	get_piece_info(&piece, buffer);
	return(1);
}
