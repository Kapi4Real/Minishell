/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <your-login> <your-email>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/xx/xx xx:xx:xx by your-login        #+#    #+#             */
/*   Updated: 2023/xx/xx xx:xx:xx by your-login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "minishell.h"
#include "parsing.h"

static void	child_process(t_cmd *cmds, int prev_pipe, int pipe_fd[2], char **envp)
{
	struct rlimit	rl;
	int				fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (cmds->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	getrlimit(RLIMIT_NOFILE, &rl);
	fd = 3;
	while (fd < (int)rl.rlim_cur)
	{
		if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
			close(fd);
		fd++;
	}
	exit(exec_single_command(cmds, envp));
}

static int	process_command(t_cmd *cmds, int *prev_pipe, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (cmds->next && pipe(pipe_fd) < 0)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (cmds->next)
			close(pipe_fd[0]);
		child_process(cmds, *prev_pipe, pipe_fd, envp);
	}
	else if (pid < 0)
		return (1);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (cmds->next)
	{
		close(pipe_fd[1]);
		*prev_pipe = pipe_fd[0];
	}
	return (0);
}

int	exec_commands(t_cmd *cmds, char **envp)
{
	int		prev_pipe;
	int		status;

	prev_pipe = -1;
	status = 0;
	if (!cmds->next && is_builtin(cmds->arguments->content))
		return (exec_single_command(cmds, envp));
	while (cmds)
	{
		if (process_command(cmds, &prev_pipe, envp))
			return (1);
		cmds = cmds->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	return (WEXITSTATUS(status));
}