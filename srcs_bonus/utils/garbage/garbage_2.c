/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:10:38 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 20:44:00 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

t_list	*_lstimg(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(42);
		lst->next = NULL;
		lst->content = NULL;
	}
	return (lst);
}

t_list	*_lstmedia(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(42);
		lst->next = NULL;
		lst->content = NULL;
	}
	return (lst);
}

t_list	*ft_new_node(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		ft_black_hole(42);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	*ft_malloc(int size)
{
	void	*output;
	t_list	*tmp;

	output = malloc(size);
	tmp = _lst();
	if (!output)
		ft_black_hole(42);
	ft_lstadd_back(&tmp, ft_new_node(output));
	return (output);
}
