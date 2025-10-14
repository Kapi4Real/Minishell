/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 08:14:46 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:22:08 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->arguments = NULL;
	new->redirection = NULL;
	new->exit_s = 0;
	new->input_fd = -1;
	new->output_fd = -1;
	new->next = NULL;
	return (new);
}

t_cmd	*cmd_last(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = cmd_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	cmd_clear(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_token	*redir_tmp;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		ft_lstclear(&(*cmd)->arguments, free);
		while ((*cmd)->redirection)
		{
			redir_tmp = (*cmd)->redirection->next;
			free((*cmd)->redirection->val);
			free((*cmd)->redirection);
			(*cmd)->redirection = redir_tmp;
		}
		free(*cmd);
		*cmd = tmp;
	}
}