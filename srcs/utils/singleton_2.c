/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:10:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/13 21:16:59 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_obj	*_player2()
{
	static t_obj	*player2 = NULL;

	if (!player2)
		player2 = ft_malloc(sizeof(t_obj));
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
		pc = ft_malloc(sizeof(t_spritecasting));
	if (!pc)
		return (NULL);
	return (pc);
}

t_menu	*_menu()
{
	static t_menu	*menu = NULL;

	if (!menu)
		menu = ft_malloc(sizeof(t_menu));
	if (!menu)
		return (NULL);
	return (menu);
}

t_weapon	**_weapon(void)
{
	static t_weapon	**weapon = NULL;

	if (!weapon)
	{
		weapon = ft_malloc(sizeof(t_weapon *) * NB_WEAPONS);
		for (int i = 0; i < NB_WEAPONS; i++)
			weapon[i] = ft_malloc(sizeof(t_weapon));
	}
	if (!weapon)
		return (NULL);
	return (weapon);
}

t_team	**_team(void)
{
	static t_team	**team = NULL;

	if (!team)
	{
		team = ft_malloc(sizeof(t_team *) * 3);
		for (int i = 0; i < 3; i++)
			team[i] = ft_malloc(sizeof(t_team));
	}
	if (!team)
		return (NULL);
	return (team);
}


t_image	*_image()
{
	static t_image	*image = NULL;

	if (!image)
	{
		image = ft_malloc(sizeof(t_image));
		if (!image)
			return (NULL);
		memset(image, 0, sizeof(t_image));
	}
	return (image);
}
