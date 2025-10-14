/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"
# include "parsing.h"
# include <stdbool.h>

/* Expansion functions */
void	expand_tokens(t_token **tokens, t_env *env);
char	*expand_var(char *str, t_env *env, int exit_status);
char	*supp_dollars(char *str);

/* Heredoc */
int		handle_heredoc(char *delimiter, int *input_fd, int first_exit_s,
			int n_line);
void	heredoc_treatment(t_minishell *minishell);

/* Environment utils */
t_env	*env_new(char *name, char *val);
void	env_add_back(t_env **lst, t_env *new);
bool	is_delimiter(char c);
bool	is_whitespace(char c);
t_list	*ft_lstnew_empty(void);
char	*ft_strjoin_char(char *s1, char c, bool free_data);
int		env_var_exists(char *var, int len, t_env *envi);

#endif