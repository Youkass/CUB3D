/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/28 11:23:15 by yobougre         ###   ########.fr       */
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
	tab[0].id = W;
	tab[0].ft_hook_key = &ft_forward;
	tab[1].id = S;
	tab[1].ft_hook_key = &ft_back;
	tab[2].id = A;
	tab[2].ft_hook_key = &ft_left;
	tab[3].id = D;
	tab[3].ft_hook_key = &ft_right;
	tab[4].id = ESC;
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
	_player()->y += _player()->dy;
	_player()->x += _player()->dx;
	return (0);
}

int	ft_back(void)
{
	printf("i'm moving down\n");
	_player()->y -= _player()->dy;
	_player()->x -= _player()->dx;
	return (0);
}

int	ft_left(void)
{
	printf("i'm moving left %f\n", _player()->angle);
	_player()->angle -= 0.1;
	printf("%f\n", _player()->angle);
	if (_player()->angle < 0)
		_player()->angle += 2 * PI;
	_player()->dx = cos(_player()->angle) * 5;
	_player()->dy = sin(_player()->angle) * 5;
	return (0);
}

int	ft_right(void)
{
	printf("i'm moving right %f\n", _player()->angle);
	_player()->angle += 0.1;
	printf("%f\n", _player()->angle);
	if (_player()->angle > 2 * PI)
		_player()->angle -= 2 * PI;
	_player()->dx = cos(_player()->angle) * 5;
	_player()->dy = sin(_player()->angle) * 5;
	return (0);
}

int	ft_escape(void)
{
	exit(1);
}
