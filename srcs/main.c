#include "parsing.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <string.h>

char	**g_env = NULL;
int		g_exit_status = 0;

static void	init_env(t_env **env, char **envp)
{
	char	**env_copy;
	char	*eq;

	env_copy = envp;
	while (*env_copy)
	{
		eq = strchr(*env_copy, '=');
		if (eq)
		{
			*eq = '\0';
			env_add_back(env, env_new(strdup(*env_copy), strdup(eq + 1)));
			*eq = '=';
		}
		env_copy++;
	}
}

static void	handle_input(char *input, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmds;
	t_token	*tmp;
	char	**env_array;

	if (!check_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (strchr(input, '=') && !strchr(input, ' ') && !strchr(input, '\t'))
	{
		handle_var_assignment(input, &env);
		return ;
	}
	tokens = tokenizer(input);
	if (!tokens)
		return ;
	if (!parsing(&tokens))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		token_clear(tokens);
		g_exit_status = 2;
		return ;
	}
	expand_tokens(&tokens, env);
	tmp = tokens;
	cmds = create_cmd(&tmp, env);
	token_clear(tokens);
	if (cmds)
	{
		env_array = env_to_array(env);
		exec_commands(cmds, env_array);
		free_array(env_array);
		cmd_clear(&cmds);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*env;

	env = NULL;
	(void)ac;
	(void)av;
	init_env(&env, envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (strlen(input) > 0)
		{
			add_history(input);
			handle_input(input, env);
		}
		free(input);
	}
	env_clear(env);
	return (g_exit_status);
}