/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	run_builtin(t_cmd *cmd)
{
	char	**args;
	int		status;

	args = list_to_str_array(cmd->arguments);
	if (!args)
		return (1);
	status = 0;
	if (!ft_strcmp(args[0], "echo"))
		status = ft_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		status = ft_cd(args);
	else if (!ft_strcmp(args[0], "pwd"))
		status = ft_pwd();
	else if (!ft_strcmp(args[0], "export"))
		status = ft_export(args);
	else if (!ft_strcmp(args[0], "unset"))
		status = ft_unset(args);
	else if (!ft_strcmp(args[0], "env"))
		status = ft_env(g_env);
	else if (!ft_strcmp(args[0], "exit"))
		status = ft_exit(args);
	free_str_array(args);
	return (status);
}
