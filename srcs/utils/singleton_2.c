/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:10:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/31 22:13:56 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_obj	*_player2()
{
	static t_obj	*player2 = NULL;

	if (!player2)
		player2 = malloc(sizeof(t_obj));
	if (!player2)
		return (NULL);
	return (player2);
}

/*
-Singleton for player casting data
*/
t_spritecasting	*_pc()
{
	static t_spritecasting	*pc = NULL;

	if (!pc)
		pc = malloc(sizeof(t_spritecasting));
	if (!pc)
		return (NULL);
	return (pc);
}


t_image	*_image()
{
	static t_image	*image = NULL;

	if (!image)
		image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	return (image);
}