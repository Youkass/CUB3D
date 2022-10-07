/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:45:15 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/07 14:47:10 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

int	ft_init_client(void)
{
	t_server	client;
	int			ret;

	client.socket = socket(AF_INET, SOCK_STREAM, 0);
	client.addr.sin_addr.s_addr = inet_addr("10.11.6.21");
	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(30000);
	ret = connect(client.socket,
		(const struct sockaddr *)&(client.addr), sizeof(client.addr));
	if (ret < 0)
		return (FAILURE);
	printf("connecté\n");
	_img()->socket = client.socket;
	return (SUCCESS);
}

void	ft_pong_client()
{
	t_obj	player;

	recv(_img()->socket, &player, sizeof(player), 0);
	printf("other player.x : %f other player.y : %f\n", player.x, player.y);
	_player2()->x = player.x;
	_player2()->y = player.y;
	printf("test\n");
	player = ft_get_data(_player());
	send(_img()->socket, &player, sizeof(player), 0);
	printf("my player.x : %f my player.y : %f\n", player.x, player.y);
}
