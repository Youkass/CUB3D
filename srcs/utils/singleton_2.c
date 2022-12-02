/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:10:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/02 14:06:15 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_obj	*_player2(void)
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
t_spritecasting	*_pc(void)
{
	static t_spritecasting	*pc = NULL;

	if (!pc)
		pc = ft_malloc(sizeof(t_spritecasting));
	if (!pc)
		return (NULL);
	return (pc);
}

t_menu	*_menu(void)
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
	int				i;

	if (!weapon)
	{
		weapon = ft_malloc(sizeof(t_weapon *) * NB_WEAPONS);
		i = 0;
		while (i < NB_WEAPONS)
		{
			weapon[i] = ft_malloc(sizeof(t_weapon));
			++i;
		}
	}
	if (!weapon)
		return (NULL);
	return (weapon);
}

t_team	**_team(void)
{
	static t_team	**team = NULL;
	int				i;

	if (!team)
	{
		team = ft_malloc(sizeof(t_team *) * 3);
		i = 0;
		while (i < 3)
		{
			team[i] = ft_malloc(sizeof(t_team));
			++i;
		}
	}
	if (!team)
		return (NULL);
	return (team);
}

t_image	*_image(void)
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
