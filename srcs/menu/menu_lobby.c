/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/02 17:29:06 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/* ************************************************************************** */
/* besoin de faire une refonte totale de wait_lobby:
	# constement envoyer ses propres data et le tableau de player ensuite, verifier
		du cote server que toute les datas sont bien recu et ensuite bien envoye
	# ne plus envoyer linked_player seul, le faire dans une structure contenant
		1-tableau des joueurs et leurs data
		2-linked_player
		3-n'importe quel data utile */
/* ************************************************************************** */

int	ft_is_start(void)
{
	int	i;

	i = 0;
	printf("linked player : %d\n", _var()->linked_players);
	while (i < _var()->linked_players)
	{
		printf("je passe bien dans cette boucle\n");
		if (_var()->o_player[i].is_start)
			printf("ce player veut start : %d\n", _var()->o_player[i].id);
		if (!_var()->o_player[i].is_start)
			return (printf("pourquoi ?\n"), 1);
		++i;
	}
	printf("i launch de the game\n");
	_var()->mode = GAME;
	_var()->started = 1;
	return (0);
}

static void	ft_cpy_tab(t_obj *o_player)
{
	int	i;

	i = 0;
	while (i < _var()->linked_players)
	{
		_var()->o_player[i] = o_player[i];
		++i;
	}
}

void	get_pseudos(void)
{
	int		i;
	t_send_server	pl;
	t_send_client	cli;

	memset(&cli, 0, sizeof(cli));
	ft_copy_data_before_pong(&cli.player);
	if (_player()->is_start == 1)
		cli.start = 1;
	else
		cli.start = 0;
	if (send(_var()->socket, &cli, sizeof(cli), 0) < 0)
		exit (1); //TODO
	memset(&pl.player, 0, sizeof(pl.player));
	if (recv(_var()->socket, &pl, sizeof(pl), 0) < 0)
		exit (1); //TODO
	_var()->linked_players = pl.linked_pl;
	memset(&_var()->o_player, 0, sizeof(_var()->o_player));
	ft_cpy_tab(pl.player);
	i = 0;
	while (i < _var()->linked_players && !_var()->started)
	{
		if (!(_image()->pseudo_img[i].img))
		{
			printf("pseudo : %s\n", _var()->o_player[i].pseudo);
			_image()->pseudo_img[i] = create_text_img(_var()->o_player[i].pseudo);
		}
		i++;
	}
	if (pl.start == 1)
	{
		_var()->mode = GAME;
		_var()->started = 1;
	}
}

void	menu_pong(void)
{
	get_pseudos();
}
