#include "minishell.h"

char *get_key(char *env)
{
    int		i;
    char	*set_key;

    i = 0;
    while (env[i] && env[i] != '=')
		i++;
	set_key = malloc(i + 1);
	if (!set_key)
		return (NULL);
	ft_strlcpy(set_key, env, i + 1);
    return(set_key);
}

char *get_value(char *env)
{
	int		i;
	char	*set_value;

	i = 0;
	while(env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (NULL);
	set_value = ft_strdup(env + i + 1);
	return (set_value);
}

void	new_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*temporal;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!(*env))
		*env = new;
	else
	{
		temporal = *env;
		while (temporal->next)
			temporal = temporal->next;
		temporal->next = new;
	}
}

void    get_variables(t_env **env, char **envp)
{
    int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (key && value)
			new_env(env, key, value);
		else
		{
			free(key);
			free(value);
		}
		i++;
	}
}

char	*get_env(char **env, char *arg)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg) == 0)
		{
			free(split);
			break ;
		}
		else
			i++;
		free(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}
