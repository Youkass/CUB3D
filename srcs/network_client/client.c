/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:45:15 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/18 00:22:03 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_get_ip_input(void)
{
	char	*buf;

	printf("Enter Host Ip on the next line : \n");
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	if (read(STDIN_FILENO, &buf, sizeof(buf)))
		return (NULL);
	buf[end_of_line(buf)] = 0;
	return (buf);

}

int	ft_init_client(void)
{
	int			ret;

	_img()->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_img()->is_host == SERVER)
		_img()->client.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	else if (_img()->is_host == CLIENT) 
		_img()->client.sin_addr.s_addr = inet_addr(ft_get_ip_input());
	_img()->client.sin_family = AF_INET;
	_img()->client.sin_port = htons(30000);
	ret = connect(_img()->socket,
		(const struct sockaddr *)&(_img()->client), sizeof(_img()->client));
	if (ret < 0)
		return (EXIT_FAILURE);
	printf("connecté\n");
	return (EXIT_SUCCESS);
}

void	ft_pong_client()
{
	t_obj	player;
	int		i;
	int		id;
	
	player = *_player();
	id = -1;
	i = 0;
	send(_img()->socket, &player, sizeof(player), 0);
	recv(_img()->socket, &id, sizeof(id), 0);
	if (id < 0)
		exit(EXIT_FAILURE);//TODO
	while (i < _img()->nb_player)
	{
		if (i != id)
		{
			recv(_img()->socket, &player, sizeof(player), 0);
			++i;
		}
		else
			++i;
		_var()->o_player[player.id] = player;
	}
	_img()->id = id;
}
