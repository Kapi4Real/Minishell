/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

extern int	g_sig;

void	heredoc_treatment(t_minishell *minishell)
{
	t_token	*redir;
	t_cmd	*cmd;
	int		first_exit_s;

	first_exit_s = 0;
	if (!minishell)
		return ;
	cmd = minishell->commands;
	while (cmd && first_exit_s == 0)
	{
		redir = cmd->redirection;
		while (redir && first_exit_s == 0)
		{
			if (redir->type == HEREDOC && g_sig != SIGINT)
			{
				first_exit_s = handle_heredoc(redir->val, &cmd->input_fd,
						first_exit_s, minishell->n_line);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
