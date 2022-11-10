/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:11:08 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/10 14:51:05 by yobougre         ###   ########.fr       */
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
			exit (1); //TODO this gotta be the first exit 
		lst->next = NULL;
		lst->content = NULL;
	}
	return (lst);
}

t_list	*ft_new_node(void *content)
{
	t_list	*node;
	t_list	*tmp;

	node = malloc(sizeof(t_list));
	tmp = _lst();
	if (!node)
	{
		ft_lstclear(&tmp, free);
		exit(139); //TODO
	}
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
	{
		ft_lstclear(&tmp, free);
		exit(139); //TODO
	}
	ft_lstadd_back(&tmp, ft_new_node(output));
	return (output);
}

void	ft_black_hole(int exit_code)
{
	t_list	*tmp;

	tmp = _lst();
	ft_lstclear(&tmp, free);
	exit(exit_code);
}
