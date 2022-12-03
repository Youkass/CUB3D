/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:06:05 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 20:21:15 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_hook(int keycode)
{
	get_key(keycode);
	if (_var()->mode == MENU)
		menu_hook(keycode);
	if (_var()->mode == MENU && _menu()->mode == MENU_PSEUDO)
	{
		menu_hook_pseudo(keycode);
	}
	if (_var()->mode == MENU && _menu()->mode == MENU_IP)
		menu_hook_ip(keycode);
	return (0);
}

int	ft_mouse_hook(int keycode)
{
	if (_var()->mode == MENU)
		menu_mouse_hook(keycode);
	return (0);
}
/*===========================================================================*/

static void	ft_loop_hook_next(void)
{
	ft_fps();
	key_hook();
	if (_var()->mode == GAME_START_ONLINE)
	{
		init_teams();
		_var()->mode = GAME;
	}
	if (_var()->mode == GAME)
	{
		ft_loop();
		if (!_var()->freeze || _player()->spectate)
		{
			mlx_mouse_hide(_mlx()->mlx, _mlx()->mlx_win);
			mouse_rotate();
		}
		else
			mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
	}
	if (_var()->mode == MENU || _var()->mode == LOBBY_WAIT)
		menu_loop();
}

int	ft_loop_hook(void)
{
	int	pid;

	click_update();
	if (_var()->mode == ONLINE_START)
	{
		_var()->is_host = SERVER;
		pid = fork();
		if (pid == 0)
		{
			system(ft_strjoin("./server ", ft_itoa(_var()->nb_player)));
			ft_black_hole(1);
		}
		else
		{
			sleep(1);
			if (ft_init_client() == EXIT_FAILURE)
				_menu()->mode = MENU_START;
		}
		_var()->mode = LOBBY_WAIT;
	}
	ft_loop_hook_next();
	return (0);
}
