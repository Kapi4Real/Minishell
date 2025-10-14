/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:11:47 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 08:16:22 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sep_on_equal(char *env_var)
{
	char	**result;
	char	*equal_sign;
	int		len;

	if (!env_var)
		return (NULL);
	result = malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
	{
		result[0] = ft_strdup(env_var);
		result[1] = NULL;
		result[2] = NULL;
		return (result);
	}
	len = equal_sign - env_var;
	result[0] = ft_substr(env_var, 0, len);
	result[1] = ft_strdup(equal_sign + 1);
	result[2] = NULL;
	return (result);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static t_env	*create_env_node(char **current_var)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free_split(current_var);
		return (NULL);
	}
	new_node->name = current_var[0];
	new_node->val = current_var[1];
	new_node->next = NULL;
	free(current_var);
	return (new_node);
}

t_env	*envp_to_lst(char **env_var)
{
	t_env	*env_lst;
	t_env	*new_node;
	char	**current_var;
	int		i;

	env_lst = NULL;
	i = 0;
	while (env_var && env_var[i])
	{
		current_var = sep_on_equal(env_var[i]);
		if (!current_var)
			continue ;
		new_node = create_env_node(current_var);
		if (!new_node)
			continue ;
		new_node->next = env_lst;
		env_lst = new_node;
		i++;
	}
	return (env_lst);
}
