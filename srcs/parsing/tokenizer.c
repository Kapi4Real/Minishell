/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 08:08:08 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:06 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "libft.h"

void	skip(char *s, int *i)
{
	while (s[*i] != 0 && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
}

static int	handle_dollar_expansion(t_token **tok_lst, char *val, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (val[*i] && (ft_isalnum(val[*i]) || val[*i] == '_'))
		(*i)++;
	add_token(tok_lst, create_token(ft_substr(val, start, *i - start),
			EXPAND_VAR));
	return (1);
}

int	tokenize_word(t_token **tok_lst, char *val)
{
	int	i;
	int	start;

	i = 0;
	while (val[i] && !ft_isspace(val[i]))
	{
		if (val[i] == '$' && (val[i + 1] == '?' || ft_isalnum(val[i + 1])))
		{
			if (handle_dollar_expansion(tok_lst, val, &i))
				continue ;
		}
		i++;
	}
	if (i > 0)
	{
		start = 0;
		add_token(tok_lst, create_token(ft_substr(val, start, i), WORD));
	}
	return (i);
}

static void	add_symbol(t_token **tok_lst, char *symbol, int double_redirect)
{
	if (symbol[0] == '<')
	{
		if (double_redirect == 1)
			add_token(tok_lst, create_token(symbol, HEREDOC));
		else
			add_token(tok_lst, create_token(symbol, INPUT));
	}
	else if (symbol[0] == '>')
	{
		if (double_redirect == 1)
			add_token(tok_lst, create_token(symbol, APPEND));
		else
			add_token(tok_lst, create_token(symbol, OUTPUT));
	}
	else
		add_token(tok_lst, create_token(symbol, PIPE));
}

int	tokenize_symbol(t_token **tok_lst, char *val)
{
	char	*symbol;
	int		i;
	int		double_redirect;

	double_redirect = 0;
	if ((val[0] == '<' && val[1] == '<') || (val[0] == '>' && val[1] == '>'))
	{
		double_redirect = 1;
		i = 2;
	}
	else
		i = 1;
	symbol = ft_substr(val, 0, i);
	add_symbol(tok_lst, symbol, double_redirect);
	return (i);
}

t_token	*tokenizer(char *arg)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (arg[i] != 0)
	{
		skip(arg, &i);
		if (arg[i] == '<' || arg[i] == '>' || arg[i] == '|')
			i += tokenize_symbol(&token, arg + i);
		else if (arg[i] != 0)
			i += tokenize_word(&token, arg + i);
	}
	return (token);
}