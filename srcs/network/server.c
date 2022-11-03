/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:00:34 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/03 15:21:44 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

t_server_data	*_server(void)
{
	static t_server_data	*server = NULL;

	if (!server)
		server = malloc(sizeof(t_server_data) * 1);
	return (server);
}

int	ft_init_server(t_server_data *data)
{
	int option;

	option = 1;
	data->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (data->socket < 0)
	{
		perror("Socket error\n");
		exit(1);
	}
	memset(&data->server, 0, sizeof(data->server));
	data->server.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	data->server.sin_family = AF_INET;
	data->server.sin_port = htons(30000);
	if (setsockopt(data->socket, SOL_SOCKET,
		(SO_REUSEADDR | SO_REUSEPORT), &option, sizeof(option)) < 0)
		exit(1);
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
	exit(1);
}

int main(int ac, char **av)
{
	t_server_data	data;
	int				i;
	
	i = 0;
	(void)ac;
	data.nb_players = atoi(av[1]);
	data.started = 0;
	if (ft_init_server(&data) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (ft_init_client_thread(&data))
		exit(EXIT_FAILURE);
	if (ft_connect_clients(&data))
	{
		while (i < data.nb_players)
		{
			close(data.clients[i].socket);
			++i;
		}
		close(data.socket);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
