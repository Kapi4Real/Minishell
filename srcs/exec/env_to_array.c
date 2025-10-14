/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <your-login> <your-email>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/xx/xx xx:xx:xx by your-login        #+#    #+#             */
/*   Updated: 2023/xx/xx xx:xx:xx by your-login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**fill_env_array(t_env *env, char **arr)
{
	int	i;

	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin3(env->name, "=", env->val);
		if (!arr[i])
		{
			free_array(arr);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		count;

	count = count_env_vars(env);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (fill_env_array(env, arr));
}
