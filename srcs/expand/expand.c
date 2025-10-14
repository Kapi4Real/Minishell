/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:37:41 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 06:38:15 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

void	expand_tokens(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	char	*expanded;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == EXPAND_VAR)
		{
			expanded = expand_var(tmp->val, env, g_exit_status);
			free(tmp->val);
			tmp->val = expanded;
			tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}
