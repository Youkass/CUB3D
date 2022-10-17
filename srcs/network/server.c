/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:00:34 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/17 23:13:10 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

t_server_data	*_server(void)
{
	static t_server_data	*server = NULL;

	if (!server)
		server = malloc(sizeof(t_server_data) * 1);
	return (server);
}

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

int	ft_init_server(t_server	*data)
{
	data->server.socket = socket(AF_INET, SOCK_STREAM, 0);
	data->server.addr.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	data->server.addr.sin_family = AF_INET;
	data->server.addr.sin_port = htons(30000);
	if (bind(server.socket,
		(const struct sockaddr *)&(data->server.addr), 
			sizeof(data->server.addr)) < 0)
		return (EXIT_FAILURE);
	if (listen(data->server.socket, 5) < 0)
		return (EXIT_FAILURE);
	printf("listen\n");
	csize = sizeof(client.addr);
	client.socket = accept(server.socket,
		(struct sockaddr *)&(client.addr), &csize);
	if (client.socket < 0)
		return (EXIT_FAILURE);
	_img()->socket = client.socket;
	printf("accepted\n");
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_server	data;

	data.nb_players = atoi(av[1]);
	if (init_server(&data))
		exit(EXIT_FAILURE);
}
