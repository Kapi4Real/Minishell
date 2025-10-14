/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_external.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

static char	*find_in_path(char *cmd)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	*full_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = getenv("PATH");
	if (!path)
		path = "/bin:/usr/bin:/usr/local/bin";
	path_copy = ft_strdup(path);
	full_path = NULL;
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = build_full_path(dir, cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (full_path);
}

int	exec_external(t_cmd *cmd, char **envp)
{
	char	**args;
	char	*path;
	pid_t	pid;
	int		status;

	args = list_to_str_array(cmd->arguments);
	if (!args || !args[0])
		return (free_str_array(args), 1);
	path = find_in_path(args[0]);
	if (!path)
	{
		cmd_not_found(args[0]);
		free_str_array(args);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		exec_child(path, args, envp);
	else if (pid < 0)
		return (fork_error(path, args));
	waitpid(pid, &status, 0);
	free(path);
	free_str_array(args);
	return (WEXITSTATUS(status));
}