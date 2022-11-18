/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:00:34 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/18 23:41:22 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_server_data	*_server(void)
{
	static t_server_data	*server = NULL;

	if (!server)
		server = ft_malloc(sizeof(t_server_data) * 1);
	return (server);
}

void	restart_state(t_client_thread	*c)
{
	int	i;

	i = 0;
	while (i < N_RSTATE)
	{
		c->serv->round_state[i] = 0;
		c->round_state_send[i] = 0;
		i++;
	}
}

int	ft_init_server(t_server_data *data)
{
	int option;

	option = 1;
	data->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (data->socket < 0)
	{
		perror("Socket error\n");
		ft_black_hole(1);
	}
	memset(&data->server, 0, sizeof(data->server));
	memset(&data->round_state, 0, sizeof(data->round_state));
	printf("%d\n", data->nb_players);
	data->round_state[ROUND_PLAY] = data->nb_players;
	init_array(&data->teams[0], data->nb_players / 2);
	init_array(&data->teams[1], data->nb_players / 2);
	data->clock = start_clock();
	data->player_alive = data->nb_players;
	data->blue_alive = data->nb_players / 2;
	data->red_alive = data->nb_players / 2;
	data->start = get_clock(data->clock);
	data->server.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	data->server.sin_family = AF_INET;
	data->server.sin_port = htons(30000);
	data->clock_started = 0;
	data->restart = 0;
	data->round_end = 0;
	if (setsockopt(data->socket, SOL_SOCKET, (SO_REUSEADDR), &option, sizeof(option)) < 0)
	{
		printf("Socket error\n");
		ft_black_hole(1);
	}
	if (bind(data->socket,
		(const struct sockaddr *)&(data->server), 
			sizeof(data->server)) < 0)
		return (perror(""), EXIT_FAILURE);
	if (listen(data->socket, data->nb_players) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_exit(int signal)
{
	(void)signal;
	pthread_mutex_unlock(&_server()->mutex);
	printf("server fermé\n");
	free(_server());
	ft_black_hole(1);
}

int main(int ac, char **av)
{
	t_server_data	data;
	int				i;
	
	i = 0;
	(void)ac;
	data.nb_players = atoi(av[1]);
	data.started = 0;
	init_weapons();
	if (ft_init_server(&data) == EXIT_FAILURE)
		ft_black_hole(EXIT_FAILURE);
	if (ft_init_client_thread(&data))
		ft_black_hole(EXIT_FAILURE);
	if (ft_connect_clients(&data))
	{
		while (i < data.nb_players)
		{
			close(data.clients[i].socket);
			++i;
		}
		close(data.socket);
		ft_black_hole(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
