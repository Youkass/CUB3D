/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:07:32 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

void	escape_menu(void)
{
	if (_menu()->mode == MENU_START)
		ft_black_hole(0);
	if (_menu()->mode == MENU_PLAYER)
		_menu()->mode = MENU_START;
	if (_menu()->mode == MENU_IP)
		_menu()->mode = MENU_PLAYER;
	if (_menu()->mode == MENU_PSEUDO)
		_menu()->mode = MENU_PLAYER;
	if (_menu()->mode == MENU_LOBBY)
		_menu()->mode = MENU_START;
	click();
}

void	escape_game(void)
{
	restart_player();
	mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
	_var()->mode = MENU;
	_menu()->mode = MENU_START;
	click();
}

void	escape_server(void)
{
	mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
	close(_var()->socket);
	if (_var()->pid > 0)
		kill((pid_t)_var()->pid, SIGKILL);
	_var()->pid = -1;
	click();
	_var()->is_host = NONE;
}

int	ft_escape(void)
{
	if (click_delay())
		return (0);
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER)
		&& _player()->id == 0)
		escape_server();
	if (_var()->mode == GAME)
		escape_game();
	else if (_var()->mode == MENU)
		escape_menu();
	else
		ft_black_hole(1);
	return (0);
}
