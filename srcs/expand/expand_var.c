/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:24:11 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 06:43:10 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"

int	changes(t_list *lst, t_env *envi, int exit_status)
{
	char	*content;
	int		i;

	(void)exit_status;
	if (!lst)
		return (0);
	content = lst->content;
	if (!content || content[0] != '$')
		return (0);
	if (content[1] == '?')
		return (2);
	i = 1;
	while (content[i] && !is_delimiter(content[i]))
		i++;
	if (env_var_exists(content + 1, i - 1, envi))
		return (i);
	return (0);
}

char	*expand_var(char *str, t_env *env, int exit_status)
{
	char	*var_name;
	t_env	*tmp;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	if (str[1] == '?')
		return (ft_itoa(exit_status));
	var_name = str + 1;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (ft_strdup(tmp->val));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
