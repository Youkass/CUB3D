/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/30 10:38:53 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
instead of making a condition branch for each case 
(and to stay in the 42 norm of coding)
we assign for each element of 'tab' who is an array of t_enum_key a keycode as
an ID, that will call the corresponding function
t_enum_key struct composition :

typedef struct s_enum_key
{
	int	id;
	int	(*ft_hook_key)(void);
}	t_enum_key;

===============================================================================
*/
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
	while (i < MAX_KEYS)
	{
		if (tab[i].id == keycode)
			return (tab[i].ft_hook_key());
		++i;
	}
	return (0);
}
/*
================================================================================
all the following functions are the function we assigned just above this comment
================================================================================
*/
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
