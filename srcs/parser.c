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
** This function takes a bitfield (an array of __uint128_t) and prints it out
** under its binary representation, it also visually format so that it
** looks just like the real board.
*/

void		print_bitfield(uint128 *bitfield, int size, int width)
{
	uint128 z;
	int		count;
	int		skipped;

	count = 0;
	skipped = 0;
	while (count < size)
	{
		z = 1;
		z <<= (sizeof(uint128) * 8 - 1);
		while (z > 0) {

			if (count % 128 == 0)
				ft_printf("@");

			if ((count/128 == size/128) && (skipped < (((size/128 + 1) * 128) - size)))
			{
				skipped++;
				z >>= 1;
				continue;
			}
			if (bitfield[count/128] & z)
				write(2, "1", 1);
			else
				write(2, "0", 1);

			if (count % width == width - 1)
				write(2, "\n", 1);

			z >>= 1;
			count++;
		}
	}
}

/*
** This function takes a bitfield (an array of __uint128_t) and a line of a game
** object (either a map or a piece) and we fill the bitfield with the binary
** representation of the line (e.g. : ..TT.TT..T translates to 0011011001
** where T is the token to map ('X', 'O' or '*')
*/

//TODO: Fixing piece -> bitfield dimensional problems
void		bitfield_conv(uint128 *bitfield, char *line, int read, char token)
{
	int 	i;
	int 	chunk;

	i = 0;
	while (line[i])
	{
		chunk = (read + i) / 128;
		bitfield[chunk] = bitfield[chunk] << 1;
		if (line[i] == token)
			bitfield[chunk] = bitfield[chunk] | 1;
		i++;
	}
}

/*
** Here we get the first 'Piece X Y' line and gather the width and length
** of the piece from which we create the bitfields with the correct size.
** We then fill the bitfields, one for the piece mapping and one for the
** empty space mapping (..** would become 0011 and 1100).
*/

int			get_piece_info(t_game_object *piece,
							t_game_object *map,
							char *line)
{
	int		i;
	int 	total_read;

	i = 6;
	while (ft_isdigit(line[i]) || line[i] == ' ')
		if (line[i++] == ' ')
			break;
	piece->coords.x = ft_atoi(&line[6]);
	piece->coords.y = ft_atoi(&line[i]);
	if (!(piece->coords.x && piece->coords.y))
		return (1);
	i = sizeof(uint128) * ((map->coords.x * map->coords.y / 128) + 1);
	piece->bitfield = malloc(i);
	piece->bitfield2 = malloc(i);
	ft_bzero(piece->bitfield, i);
	ft_bzero(piece->bitfield2, i);
	total_read = 0;
	while (total_read < piece->coords.x * piece->coords.y)
	{
		get_next_line(0, &line);
		ft_printf("line = [%s]\n", line);
		bitfield_conv(piece->bitfield, line, total_read, '*');
		bitfield_conv(piece->bitfield2, line, total_read, '.');
		total_read += ft_strlen(line);
	}
	ft_printf("Piece bitfields: %i\n", total_read);
	ft_printf("\n");
	print_bitfield(piece->bitfield, map->coords.x * map->coords.y, map->coords.y);
	ft_printf("\n-----------------------------------------------------------\n");
	print_bitfield(piece->bitfield2, map->coords.x * map->coords.y, map->coords.y);
	ft_printf("\n");
	return (0);
}

/*
** Here we get the first 'Plateau X Y' line and gather the width and length
** of the board from which we create the bitfields with the correct size.
** We then fill the bitfields, one for the player map and one for the
** challenger map.
*/

int			get_map_info(t_game_object *map, char *line)
{
	int		i;
	int 	total_read;

	i = 8;
	while (ft_isdigit(line[i]) || line[i] == ' ')
		if (line[i++] == ' ')
			break;
	map->coords.x = ft_atoi(&line[8]);
	map->coords.y = ft_atoi(&line[i]);
	if (!(map->coords.x && map->coords.y))
		return (1);
	i = sizeof(uint128) * ((map->coords.x * map->coords.y / 128) + 1);
	map->bitfield = malloc(i);
	map->bitfield2 = malloc(i);
	ft_bzero(map->bitfield, i);
	ft_bzero(map->bitfield2, i);
	get_next_line(0, &line);
	total_read = 0;
	while (total_read < map->coords.x * map->coords.y)
	{
		get_next_line(0, &line);
		ft_printf("line = [%s]\n", &line[4]);
		bitfield_conv(map->bitfield, &line[4], total_read, 'O');
		bitfield_conv(map->bitfield2, &line[4], total_read, 'X');
		total_read += ft_strlen(&line[4]);
	}
	ft_printf("Map bitfields: %i\n", total_read);
	ft_printf("\n");
	print_bitfield(map->bitfield, total_read, map->coords.y);
	ft_printf("\n-----------------------------------------------------------\n");
	print_bitfield(map->bitfield2, total_read, map->coords.y);
	ft_printf("\n");
	return (0);
}

/*
**
**
*/

int			parser(t_game_state *game)
{
	char	*line;

	get_next_line(0, &line);
	if (ft_strlen(line) < 8 || (ft_strncmp(line, "Plateau ", 8)) != 0 ||
			get_map_info(&game->map, line))
		ft_exit("ERROR: Invalid map received from the VM\n");

	get_next_line(0, &line);
	if (ft_strlen(line) < 6 || (ft_strncmp(line, "Piece ", 6)) != 0 ||
		get_piece_info(&game->piece, &game->map, line))
		ft_exit("ERROR: Invalid piece received from the VM\n");

	return (1);
}
