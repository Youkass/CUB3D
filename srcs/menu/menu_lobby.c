/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/31 22:13:46 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	get_pseudos(void)
{
	static int	i = 0;
	static int sendo = 0;
	t_obj	player;
	int		start;

	if (!sendo)
	{
		memset(&player, 0, sizeof(player));
		ft_copy_data_before_pong(&player);
		send(_var()->socket, &player, sizeof(player), 0);
		sendo = 1;
	}
	start = 0;
	if (recv(_var()->socket, &(_var()->linked_players), sizeof(int), 
			0) < 0)
		exit(1); //TODO
	if (send(_var()->socket, &(_var()->started), sizeof(int), 0) < 0)
		exit(1); //TODO
	if (recv(_var()->socket, &start, sizeof(int), 0) < 0)
		exit(1); //TODO
	if (start)
	{
		_var()->started = start;
		_var()->mode = GAME;
	}
	while (i < _var()->linked_players && !_var()->started)
	{
		if (recv(_var()->socket, &player, sizeof(player), 0) < 0)
			exit(1); //TODO
		_var()->o_player[i] = player;
		if (!(_image()->pseudo_img[i].img))
			_image()->pseudo_img[i] = create_text_img(player.pseudo);
		i++;
	}
}

void	menu_pong(void)
{
	get_pseudos();
}
