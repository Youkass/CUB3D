/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:53:00 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/19 18:16:50 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	ft_is(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (0);
	return (1);
}

int	end_of_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_is(s[i]))
		++i;
	return (i);
}

char	*ft_get_host_ip(void)
{
	int		fd;
	char	*buf;
	int		r;

	if (system(CMD_PRINT_IP) < 0)
		exit(127); //TODO
	buf = NULL;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	fd = open(TMP_FILE, O_RDONLY);
	if (fd < 0)
		exit(127); //TODO
	r = read(fd, buf, BUFFER_SIZE);
	if (r < 0)
		exit(127); //TODO
	buf[r] = 0;
	unlink(TMP_FILE);
	printf("partager cette ip avec vos amis 42 : %s\n", buf);
	return (buf);
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
