/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:26:46 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:04 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_redirection(t_token **token)
{
	if ((*token)->next == NULL || (*token)->next->type != WORD)
		return (0);
	return (1);
}

int	test_pipe(t_token **token)
{
	if ((*token)->next == NULL || (*token)->next->type == PIPE)
		return (0);
	return (1);
}

int	parsing(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE && !test_pipe(&tmp))
			return (0);
		else if (tmp->type != PIPE && tmp->type != WORD
			&& !test_redirection(&tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
