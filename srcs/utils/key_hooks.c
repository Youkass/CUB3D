/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/28 21:16:32 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_game_hook(int keycode)
{
	int			i;
	t_enum_key	tab[MAX_KEYS];

	i = 0;
	tab[0].id = 119;
	tab[0].ft_hook_key = &ft_forward;
	tab[1].id = 115;
	tab[1].ft_hook_key = &ft_back;
	tab[2].id = 97;
	tab[2].ft_hook_key = &ft_left;
	tab[3].id = 100;
	tab[3].ft_hook_key = &ft_right;
	tab[4].id = 65307;
	tab[4].ft_hook_key = &ft_escape;
	//printf("keycode : %d\n", keycode);
	while (i < MAX_KEYS)
	{
		//printf("id : %d\n",tab[i].id);
		if (tab[i].id == keycode)
			return (tab[i].ft_hook_key());
		++i;
	}
	return (0);
}

int	ft_forward(void)
{
	printf("i'm moving up\n");
	_player()->y -= 5;
	return (0);
}

int	ft_back(void)
{
	printf("i'm moving down\n");
	_player()->y += 5;
	return (0);
}

int	ft_left(void)
{
	printf("i'm moving left\n");
	_player()->x -= 5;
	return (0);
}

int	ft_right(void)
{
	printf("i'm moving right\n");
	_player()->x += 5;
	return (0);
}

int	ft_escape(void)
{
	exit(1);
}
