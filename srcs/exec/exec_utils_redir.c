/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int	handle_heredoc(char *delimiter, int *input_fd, int first_exit_s, int n_line)
{
	int		fd[2];
	char	*line;

	(void)n_line;
	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, SIG_DFL);
	while (first_exit_s == 0)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-doc delimited by EOF\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	*input_fd = fd[0];
	return (first_exit_s);
}

static int	handle_redir_input(t_token *token)
{
	int	fd;

	fd = open(token->next->val, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->val, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_output(t_token *token)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (token->type == OUTPUT)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd = open(token->next->val, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->val, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_syntax_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token->next)
		ft_putstr_fd(token->next->val, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int	handle_redirections(t_token *token)
{
	int	ret;
	int	fd;

	ret = 0;
	while (token && ret == 0)
	{
		if (!(token->type == INPUT || token->type == HEREDOC
				|| token->type == OUTPUT || token->type == APPEND))
		{
			token = token->next;
			continue ;
		}
		if (!token->next || token->next->type != WORD)
			return (handle_syntax_error(token));
		if (token->type == INPUT)
			ret = handle_redir_input(token);
		else if (token->type == HEREDOC)
		{
			if (handle_heredoc(token->next->val, &fd, 0, 0) == -1
				|| dup2(fd, STDIN_FILENO) == -1)
				ret = -1;
			close(fd);
		}
		else if (token->type == OUTPUT || token->type == APPEND)
			ret = handle_redir_output(token);
		token = token->next->next;
	}
	return (ret);
}
