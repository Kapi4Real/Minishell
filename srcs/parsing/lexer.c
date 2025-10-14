/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_token	*lexer(char *input)
{
	t_token	*tokens;
	char	*token;
	t_arg	type;

	tokens = NULL;
	token = strtok(input, " \t\n");
	while (token)
	{
		type = WORD;
		if (strcmp(token, ">") == 0)
			type = OUTPUT;
		else if (strcmp(token, ">>") == 0)
			type = APPEND;
		else if (strcmp(token, "<") == 0)
			type = INPUT;
		else if (strcmp(token, "|") == 0)
			type = PIPE;
		token_add_back(&tokens, create_token(strdup(token), type));
		token = strtok(NULL, " \t\n");
	}
	return (tokens);
}