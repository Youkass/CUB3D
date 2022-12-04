/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:09:39 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/04 20:39:46 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			if ((*lst)->content != NULL)
				(del)((*lst)->content);
			free(*lst);
			*lst = tmp;
		}
	}
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (tmp == NULL)
	{
		*alst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*_lst(void)
{
	static t_list	*lst = NULL;

	if (!lst)
	{
		lst = malloc(sizeof(t_list));
		if (!lst)
			ft_black_hole(1);
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
		ft_black_hole(139);
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
	memset(&output, 0, sizeof(output));
	if (!output)
		ft_black_hole(139);
	ft_lstadd_back(&tmp, ft_new_node(output));
	return (output);
}
