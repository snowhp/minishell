/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:50 by tde-sous          #+#    #+#             */
/*   Updated: 2023/06/07 12:26:344 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_addenv(char **env, t_data **info)//needs fixing on order
{
	t_data	*new;
	char	**temp;
	int	i;

	i = 0;
	while(env[i])
	{
		new = malloc(sizeof(t_data));
		temp = ft_split(env[i], '=');
		new->key = temp[0];
		new->value = temp[1];
		new->next = *info;
		*info = new;
		i++;
	}
}

void	ft_printenv(t_data **info)
{
	t_data *current;

	current = *info;
	while (current->next != NULL)
	{
		printf("%s=",current->key);
		printf("%s\n",current->value);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data *info;

	info = NULL;
	(void) argc;
	(void) argv;
	(void) env;
	ft_addenv(env, &info);
	ft_loop(env, &info);
	return (0);
}

void	ft_printcwd()
{
	char cwd[200];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
	printf("getcwd() error\n");
	return ;
	}
}

void	ft_changedir(char *path)
{
	char	currentdir[200];

	getcwd(currentdir ,sizeof(currentdir));
	ft_strlcat(currentdir, "/",ft_strlen(currentdir) + 2);
	ft_strlcat(currentdir,path,(ft_strlen(currentdir) + ft_strlen(path)) + 1);
	chdir(currentdir);
}

void	ft_check_test(char **args, char **env, t_data **info)
{
	int	pid;

	if(!ft_strncmp(args[0], "echo", ft_strlen(args[0])) && args[1] == 0)// -n option
		printf("echo\n");
	else if(!ft_strncmp(args[0], "cd", ft_strlen(args[0])))//relative/absolute paths
		ft_changedir(args[1]);
	else if(!ft_strncmp(args[0], "pwd", ft_strlen(args[0])) && args[1] == 0)
		ft_printcwd();
	else if(!ft_strncmp(args[0], "export", ft_strlen(args[0])) && args[1] == 0)
		printf("export\n");
	else if(!ft_strncmp(args[0], "unset", ft_strlen(args[0])) && args[1] == 0)
		printf("unset\n");
	else if(!ft_strncmp(args[0], "env", ft_strlen(args[0])) && args[1] == 0)
		ft_printenv(info);
	else
	{
		pid = fork();
		if (pid == -1)
			printf("Error");
		else if (pid == 0)
			ft_execute(args, env);
		else
			wait(NULL);
	}
}

void	ft_loop(char **env, t_data **info)
{
	char	*line;
	char	**args;
	int		i = 0;

	ft_signals();
	line = ft_strdup("");
	while (line)
	{
		free(line);
		printf("> ");
		line = readline(NULL);
		if (!line[0])
		{
			printf("\n");
			continue ;
		}
		add_history(line);
		args = ft_split(line, ' ');
		while(args[i])
		{
			printf("|%s|\n",args[i]);
			i++;
		}
		//args = ft_args(line, env);
		if(!ft_strncmp(args[0], "exit", ft_strlen(args[0])) && !args[1])
		{
			free(line);
			ft_freearray(args);
			exit(0);
		}
		ft_check_test(args, env, info);
		ft_freearray(args);
	}
	free(line);
	rl_clear_history();
}
