/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:10:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/01 10:21:09 by yobougre         ###   ########.fr       */
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
	{
		image = malloc(sizeof(t_image));
		if (!image)
			return (NULL);
		memset(image, 0, sizeof(t_image));
	}
	return (image);
}
