/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**copy_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_array(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

char	*get_env_var(char **envp, const char *name)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], name, name_len) == 0)
			&& envp[i][name_len] == '=')
			return (&envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

static char	*create_env_var(const char *key, const char *value)
{
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	new_var = ft_strjoin(temp, value);
	free(temp);
	return (new_var);
}

static int	find_env_index(char **env, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	set_env_var(char ***env, const char *key, const char *value)
{
	char	*new_var;
	int		index;
	int		count;
	char	**new_env;

	if (!key || !value)
		return ;
	new_var = create_env_var(key, value);
	if (!new_var)
		return ;
	index = find_env_index(*env, key);
	if (index != -1)
	{
		free((*env)[index]);
		(*env)[index] = new_var;
		return ;
	}
	count = count_env_vars(*env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	*env = new_env;
}

void	init_env(char **envp)
{
	int	count;
	int	i;

	count = count_env_vars(envp);
	g_env = malloc(sizeof(char *) * (count + 1));
	if (!g_env)
		return ;
	i = 0;
	while (envp[i])
	{
		g_env[i] = ft_strdup(envp[i]);
		if (!g_env[i])
		{
			while (i > 0)
				free(g_env[--i]);
			free(g_env);
			return ;
		}
		i++;
	}
	g_env[count] = NULL;
}
