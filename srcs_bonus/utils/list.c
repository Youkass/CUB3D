/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:55:39 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*li;

	li = ft_malloc(sizeof(*li));
	if (!li)
		return (NULL);
	li->content = content;
	li->next = NULL;
	return (li);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = (*alst);
		*alst = new;
	}
	else
	{
		*alst = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lst_dellast(t_list **lst)
{
	t_list	*prec;
	t_list	*tmp;

	if (!(*lst))
		return ;
	if (!(*lst)->next)
	{
		*lst = NULL;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		prec = tmp;
		tmp = tmp->next;
	}
	prec->next = NULL;
}
