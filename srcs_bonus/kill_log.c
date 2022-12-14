/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_log.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:07:03 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

t_elem	*new_log(int id1, int id2)
{
	t_elem	*log;

	log = ft_malloc(sizeof(*log));
	log->ids[0] = id1;
	log->ids[1] = id2;
	log->start = get_clock(_var()->clock);
	return (log);
}

void	print_log(t_list	*li)
{
	t_elem	*log;

	while (li)
	{
		log = (t_elem *)li->content;
		printf("%d killed %d\n", log->ids[0], log->ids[1]);
		li = li->next;
	}
}
