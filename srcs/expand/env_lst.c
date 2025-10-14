/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:22:35 by togomez           #+#    #+#             */
/*   Updated: 2025/04/28 09:31:24 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *var_name, char *var_val)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->name = var_name;
	new->val = var_val;
	new->next = NULL;
	return (new);
}

t_env	*env_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = env_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	env_clear(t_env *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		env_clear(lst->next);
	free(lst->name);
	free(lst->val);
	free(lst);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
