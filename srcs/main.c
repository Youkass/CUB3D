/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 16:53:35 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h>

void	ft_init_player_pos(void)
{
	_player()->x = 300;
	_player()->y = 300;
}

int	ft_hook(int keycode)
{
	if (_var()->mode == GAME)
		ft_game_hook(keycode);
	else if (_var()->mode == MENU)
		menu_hook(keycode);
	return (0);
}

int	ft_mouse_hook(int keycode)
{
	printf("lol\n");
	if (_var()->mode == MENU)
		menu_mouse_hook(keycode);
	return (0);
}

int	ft_loop_hook(void)
{
	if (_var()->mode == GAME)
		ft_loop();
	else if (_var()->mode == MENU)
		menu_loop();
	return (0);
}

/*
On verra
*/
int	ft_game(void)
{
	mlx_hook(_mlx()->mlx_win, 2, 1L<<0, &ft_hook, NULL);
	mlx_loop_hook(_mlx()->mlx, &ft_loop_hook, NULL);
	mlx_mouse_hook(_mlx()->mlx_win, &menu_mouse_hook, NULL);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
    (void)argv;
	ft_init_mlx();
	ft_init_img();
	ft_init_player_pos();
	gen_menu_images();
	ft_game();
	mlx_loop(_mlx()->mlx);
    return (0);
}
