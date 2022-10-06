/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:10:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/05 23:13:44 by denissereno      ###   ########.fr       */
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
