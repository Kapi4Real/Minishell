/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:52:50 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:22:20 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_arg type)
{
	return (type == INPUT || type == OUTPUT || type == APPEND || type == HEREDOC);
}

char    *get_env_value(char *var, t_env *env);

char	*expand_vars_in_string(char *str, t_env *env)
{
	char	*result;
	int		i;
	int		in_quote;
	int		start;
	char	*var;
	char	*value;
	char	*new_result;
	char	c[2];

	result = ft_strdup("");
	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_quote)
			in_quote = 1;
		else if (str[i] == '\'' && in_quote)
			in_quote = 0;
		if (str[i] == '$' && !in_quote && (str[i + 1] == '?'
				|| ft_isalnum(str[i + 1])))
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var = ft_substr(str, start, i - start);
			value = get_env_value(var, env);
			new_result = ft_strjoin(result, value);
			free(result);
			free(var);
			free(value);
			result = new_result;
			continue ;
		}
		else
		{
			c[0] = str[i++];
			c[1] = 0;
			new_result = ft_strjoin(result, c);
			free(result);
			result = new_result;
		}
	}
	return (result);
}

char	*get_env_value(char *var, t_env *env)
{
	t_env	*tmp;

	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(g_exit_status));
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			return (ft_strdup(tmp->val));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

static void	process_token(t_token *token, t_cmd **commands,
	t_cmd **current, t_env *env)
{
	char	*expanded;
	char	*without_quotes;
	char	*expanded_redir;
	char	*without_quotes_redir;
	char	*expanded_file;
	char	*without_quotes_file;
	t_token	*new_redir;
	t_token	*file;

	if (token->type == WORD)
	{
		expanded = expand_vars_in_string(token->val, env);
		without_quotes = remove_quotes(expanded, env);
		free(expanded);
		ft_lstadd_back(&(*current)->arguments, ft_lstnew(without_quotes));
	}
	else if (token->type == PIPE)
	{
		*current = cmd_new();
		cmd_add_back(commands, *current);
	}
	else if (is_redirection(token->type))
	{
		expanded_redir = expand_vars_in_string(token->val, env);
		without_quotes_redir = remove_quotes(expanded_redir, env);
		free(expanded_redir);
		new_redir = token_new(without_quotes_redir, token->type);
		token_add_back(&(*current)->redirection, new_redir);
		if (token->next && token->next->type == WORD)
		{
			expanded_file = expand_vars_in_string(token->next->val, env);
			without_quotes_file = remove_quotes(expanded_file, env);
			free(expanded_file);
			file = token_new(without_quotes_file, WORD);
			token_add_back(&(*current)->redirection, file);
			token = token->next;
		}
	}
}

t_cmd	*create_cmd(t_token **tokens, t_env *env)
{
	t_cmd	*cmd;
	char	*expanded;
	char	*file;
	t_token	*redir;
	t_token	*file_token;

	cmd = cmd_new();
	if (!cmd || !tokens || !*tokens)
		return (NULL);
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
		{
			expanded = expand_vars_in_string((*tokens)->val, env);
			ft_lstadd_back(&cmd->arguments, ft_lstnew(expanded));
		}
		else if (is_redirection((*tokens)->type))
		{
			redir = token_new(ft_strdup((*tokens)->val), (*tokens)->type);
			token_add_back(&cmd->redirection, redir);
			*tokens = (*tokens)->next;
			if (*tokens && (*tokens)->type == WORD)
			{
				file = expand_vars_in_string((*tokens)->val, env);
				file_token = token_new(file, WORD);
				token_add_back(&cmd->redirection, file_token);
				*tokens = (*tokens)->next;
				continue ;
			}
		}
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_cmd	*cmd(t_token *token, t_env *env)
{
	t_cmd	*commands;
	t_cmd	*current;
	t_token	*tmp;

	if (!token)
		return (NULL);
	current = cmd_new();
	commands = current;
	tmp = token;
	while (tmp)
	{
		process_token(tmp, &commands, &current, env);
		tmp = tmp->next;
	}
	return (commands);
}

bool	is_valid_var_name(const char *name)
{
	if (!name || !*name)
		return (false);
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	while (*++name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
	}
	return (true);
}

t_env	*find_env_var(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, (char *)name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	handle_var_assignment(char *input, t_env **env)
{
	char	*eq_pos;
	char	*var_name;
	char	*var_value;
	t_env	*existing_var;

	eq_pos = ft_strchr(input, '=');
	if (!eq_pos)
		return ;
	*eq_pos = '\0';
	var_name = input;
	var_value = eq_pos + 1;
	if (!is_valid_var_name(var_name))
	{
		ft_putstr_fd("minishell: invalid variable name\n", STDERR_FILENO);
		g_exit_status = 1;
		*eq_pos = '=';
		return ;
	}
	existing_var = find_env_var(*env, var_name);
	if (existing_var)
	{
		free(existing_var->val);
		existing_var->val = ft_strdup(var_value);
	}
	else
		env_add_back(env, env_new(ft_strdup(var_name), ft_strdup(var_value)));
	*eq_pos = '=';
	g_exit_status = 0;
}
