/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:05:00 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 18:56:45 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	menu_hook_pseudo(int keycode)
{
	static int	n = 0;

	if (((keycode >= A_ && keycode <= Z) || is_nb_keycode(keycode))
		&& n + 1 < 17)
	{
		if (is_nb_keycode(keycode))
			_player()->pseudo[n++] = get_nb_keycode(keycode);
		else
			_player()->pseudo[n++] = keycode - 32;
		_player()->pseudo[n] = 0;
	}
	if (keycode == ERASE && n > 0)
	{
		n--;
		_player()->pseudo[n] = 0;
	}
	return (menu_hook_pseudo_2(keycode, &n));
}

int	menu_hook_ip_4(int keycode)
{
	if (keycode == ENTER && _menu()->n_ip > 2 && _var()->is_host == CLIENT)
	{
		_menu()->mode = MENU_PSEUDO;
		_var()->mode = MENU;
	}
	return (0);
}

int	menu_hook_ip_3(int keycode)
{
	if (keycode == EIGHT && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '8';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == NINE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '9';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == SPACE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '.';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == ERASE && _menu()->n_ip > 0)
	{
		_menu()->n_ip--;
		_var()->ip[_menu()->n_ip] = 0;
	}
	return (menu_hook_ip_4(keycode));
}

int	menu_hook_ip_2(int keycode)
{
	if (keycode == FOUR && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '4';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == FIVE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '5';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == SIX && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '6';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == SEVEN && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '7';
		_var()->ip[_menu()->n_ip] = 0;
	}
	return (menu_hook_ip_3(keycode));
}

int	menu_hook_ip(int keycode)
{
	if (keycode == ZERO && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '0';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == ONE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '1';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == TWO && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '2';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == THREE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '3';
		_var()->ip[_menu()->n_ip] = 0;
	}
	return (menu_hook_ip_2(keycode));
}
