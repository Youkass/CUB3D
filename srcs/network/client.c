/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:45:15 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/18 00:22:03 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

char	*ft_get_ip_input(void)
{
	char	buf[30];

	if (read(STDIN_FILENO, &buf, sizeof(buf)))
		return (NULL);
	buf[end_of_line(buf)] = 0;
	return (buf);

}

int	ft_init_client(void)
{
	int			ret;

	_img()->client.socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_img()->is_host == HOST)
		client.addr.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	else 
		_img()->client.addr.sin_addr.s_addr = inet_addr(ft_get_ip_input);
	client.addr.sin_family = AF_INET;
	client.addr.sin_port = htons(30000);
	ret = connect(client.socket,
		(const struct sockaddr *)&(client.addr), sizeof(client.addr));
	if (ret < 0)
		return (EXIT_FAILURE);
	printf("connecté\n");
	return (EXIT_SUCCESS);
}

void	ft_pong_client()
{
	t_obj	player;
	int		i;
	
	player = *_player();
	i = 0;
	send(_img()->socket, &player, sizeof(player), 0);
	while (i < _img()->)
	recv(_img()->socket, &player, sizeof(player), 0);
	_player2()->x = player.x;
	_player2()->y = player.y;
	player = ft_get_data(_player());
	send(_img()->socket, &player, sizeof(player), 0);
}
