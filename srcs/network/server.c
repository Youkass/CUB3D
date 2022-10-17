/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:00:34 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/17 17:30:16 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

void	ft_ping_server()
{
	t_obj	player;

	player = ft_get_data(_player());
	send(_img()->socket, &player, sizeof(player), 0);
	printf("my player.x : %f my player.y : %f\n", player.x, player.y);
	recv(_img()->socket, &player, sizeof(player), 0);
	printf("other player.x : %f other player.y : %f\n", player.x, player.y);
	_player2()->x = player.x;
	_player2()->y = player.y;
	draw_void_thread();
}

int	ft_init_server(void)
{
	socklen_t	csize;
	t_server	server;
	t_server	client;
	int			ret;

	server.socket = socket(AF_INET, SOCK_STREAM, 0);
	server.addr.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	server.addr.sin_family = AF_INET;
	server.addr.sin_port = htons(30000);
	ret = bind(server.socket,
		(const struct sockaddr *)&(server.addr), sizeof(server.addr));
	if (ret < 0)
		return (FAILURE);
	if (listen(server.socket, 5) < 0)
		return (FAILURE);
	printf("listen\n");
	csize = sizeof(client.addr);
	client.socket = accept(server.socket,
		(struct sockaddr *)&(client.addr), &csize);
	if (client.socket < 0)
		return (FAILURE);
	_img()->socket = client.socket;
	printf("accepted\n");
	return (SUCCESS);
}

int main(int ac, char **av)
{
}
