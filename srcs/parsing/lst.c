/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:56:51 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:03 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*lstnew(char *val)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = val;
	new->next = NULL;
	return (new);
}

t_list	*lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	free(lst);
}

void	lstclear(t_list **lst)
{
	if (!lst && !(*lst))
		return ;
	if (*lst && (*lst)->next)
		lstclear(&(*lst)->next);
	lstdelone(*lst);
	*lst = NULL;
}
