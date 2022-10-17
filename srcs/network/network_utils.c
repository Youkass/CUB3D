/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:53:00 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/17 17:30:16 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

static int	ft_is(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (0);
	return (1);
}

static int	end_of_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_is(s[i]))
		++i;
	return (i);
}

char	*ft_get_host_ip()
{
	int		fd;
	char	buf[30];

	if (system(CMD_PRINT_IP) < 0)
		exit(127); //TODO
	fd = open(TMP_FILE, O_RDONLY);
	if (fd < 0)
		exit(127); //TODO
	if (read(fd, &buf, BUFFER_SIZE) < 0)
		exit(127); //TODO
}

int	ft_network_type(char *argv)
{
	if (*argv == '1')
		_img()->network = CLIENT;
	else if (*argv == '2')
		_img()->network = SERVER;
	else
		return (FAILURE);
	/*=================================================*/
	/*THE NEXT PART NEED TO BE PUT IN THE UI LATER TODO*/
	/*=================================================*/
	if (_img()->network == CLIENT)
	{
		if (ft_init_client())
			return (FAILURE);
	}
	else if (_img()->network == SERVER)
	{
		if (ft_init_server())
			return (FAILURE);
	}
	return (SUCCESS);
}

t_obj	ft_get_data(t_obj *player)
{
	t_obj	data;

	data.id = player->id;
	data.x = player->x;
	data.y = player->y;
	data.c = player->c;
	data.dx = player->dx;
	data.dy = player->dy;
	data.old_dx = player->old_dx;
	data.old_dy = player->old_dy;
	data.angle = player->angle;
	data.move_speed = player->move_speed;
	data.rot_speed = player->rot_speed;
	data.hb = player->hb;
	return (data);
}
