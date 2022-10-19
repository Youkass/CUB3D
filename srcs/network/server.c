/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:00:34 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/19 17:31:05 by denissereno      ###   ########.fr       */
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
	data->socket = socket(AF_INET, SOCK_STREAM, 0);
	data->server.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	data->server.sin_family = AF_INET;
	data->server.sin_port = htons(30000);
	if (bind(data->socket,
		(const struct sockaddr *)&(data->server), 
			sizeof(data->server)) < 0)
		return (perror(""), EXIT_FAILURE);
	printf("je passe ici\n");
	if (listen(data->socket, 5) < 0)
		return (EXIT_FAILURE);
	printf("listen\n");
	return (EXIT_SUCCESS);
}

static void	ft_exit(int signal)
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
	
	_server()->clock = start_clock();
	(void)ac;
	signal(SIGPIPE, &ft_exit);
	data.nb_players = atoi(av[1]);
	if (ft_init_server(&data) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (ft_init_client_thread(&data))
		exit(EXIT_FAILURE);
	if (ft_connect_clients(&data))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}