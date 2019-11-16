/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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
		//z <<= (sizeof(uint128) * 8 - 1);
		while (z > 0)
		{
			/*if ((count/128 == size/128) && (skipped < (((size/128 + 1) * 128) - size)))
			{
				skipped++;
				z >>= 1;
				continue;
			}*/
			if (count % 128 == 0)
				write(2, "||", 2);
			if (bitfield[count/128] & z)
				write(2, "1", 1);
			else
				write(2, "0", 1);
			if (count % width == width - 1)
				write(2, "\n", 1);
			z <<= 1;
			count++;
		}
	}
}