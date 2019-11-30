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

/*
**
**
*/

int			create_heatmap(t_game_state *game) {
	int 	i;
	int		x;
	int		y;

	i = -1;
	x = -1;
	if (!(game->heatmap = malloc(game->map.height * sizeof(int *))))
		return (KO);
	while (++i < game->map.height)
	{
		if (!(game->heatmap[i] = malloc(game->map.length * sizeof(int))))
			return (KO);
	}
	while (++x < game->map.height)
	{
		y = -1;
		while (++y < game->map.length)
			game->heatmap[x][y] = 99;
	}
	fill_heatmap(*game);
	return (OK);
}

/*
**
**
*/

void		fix_piece_size(t_game_object *piece, int old_height, int old_length)
{
	int		x;
	int		y;
	int		new_height;
	int		new_length;

	new_height = 0;
	new_length = 0;
	x = -1;
	while (++x < old_height)
	{
		y = -1;
		while (++y < old_length)
			if (piece->table[x][y] == '*')
			{
				if (x > new_height)
					new_height = x;
				if (y > new_length)
					new_length = y;
			}
	}
	piece->height = ++new_height;
	piece->length = ++new_length;
}

/*
**
**
*/

void		get_object_dimensions(t_game_object *object, char *line, int i)
{
	object->height = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]) || line[i] == ' ')
		if (line[i++] == ' ')
			break;
	object->length = ft_atoi(&line[i]);
	object->size = object->height * object->length;
}

/*
** Here we get the first 'Plateau X Y' line and gather the width and length
** of the board from which we create the bitfields with the correct size.
** We then fill the bitfields, one for the player map and one for the
** challenger map.
*/

int			get_object_info(t_game_object *object, char *line,
														int x_pos, int shift)
{
	int		i;

	i = 0;
	get_object_dimensions(object, line, x_pos);
	if (!(object->size))
		return (KO);
	if (!(object->table = malloc(object->height * sizeof(char *))))
		return (KO);
	if (shift == 4)
	{
		skip_line(&line);
		ft_printf("%p\n", line);
		free(line);
	}
	while (i < object->height)
	{
		get_next_line(0, &line);
		if (!(object->table[i] = malloc(object->length * sizeof(char))))
			return (KO);
		ft_strcpy(object->table[i], &line[shift]);
		free(line);
		i++;
	}
	return (OK);
}

/*
**
**
*/

int			parser(t_game_state *game)
{
	char	*line;

	ft_printf("1\n");
	get_next_line(0, &line);
	if (ft_strlen(line) < 8
	|| (ft_strncmp(line, "Plateau ", 8)) != 0
	|| get_object_info(&game->map, line, 8, 4)
	|| create_heatmap(game))
		ft_exit("ERROR: Invalid map received as input\n");
	free(line);
	ft_printf("2\n");
	get_next_line(0, &line);
	if (ft_strlen(line) < 6
	|| (ft_strncmp(line, "Piece ", 6)) != 0
	|| get_object_info(&game->piece, line, 6, 0))
		ft_exit("ERROR: Invalid piece received as input\n");
	free(line);
	ft_printf("3\n");
	fix_piece_size(&game->piece, game->piece.height, game->piece.length);
	return (1);
}
