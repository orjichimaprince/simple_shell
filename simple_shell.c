#include "simple_shell.h"

/**
 * main - The main function for simple shell
 *
 * @argc: Count of the arguments passes
 * @argv: Arguments value with the name of the executable
 *
 * Return: 0 if is a success
 */
int main(__attribute__((unused)) int argc, char *argv[])
{
	int i = 0;
	path_t *path;
	env_t *env;

	env = create_env_variable();
	path = create_path_variable(env);

	loop_asking(i, argv, env, path);

	return (0);
}

/**
 * loop_asking - Infinite loop with invoking some functions
 * for asking to user a command, and execute the command if is
 * possible
 *
 * @i: The count of error
 * @argv: The arguments values with the name of executable
 * @env: The linked list of env variable
 * @path: The linked list of path variable
 */
void loop_asking(int i, char *argv[], env_t *env, path_t *path)
{
	char *buffer = "", **sep;
	int path_exec, env_exec, size_test = 0, status = 0;
	struct stat st;

	do {
		i++;
		path_exec = 1;
		env_exec = 1;
		_prompt();
		signal(SIGINT, sigint_handle);
		buffer = _getline(path, env, status);
		sep = separate_av(buffer, " \t\n\v\r\f");
		if (sep != NULL && _strlen(sep[0]) > 255)
		{
			status = error_file(sep[0], i, argv, 1);
			size_test = 1;
		}
		if (buffer != NULL && sep != NULL && size_test == 0)
			if ((sep[0][0] == '.' && sep[0][1] != '\0') || sep[0][0] != '.')
			{
				if ((_strcmp(sep[0], "env") == 0 || _strcmp(sep[0], "printenv") == 0))
					env_exec = _printenv(env, sep);
				if (sep[0][0] != '.' && env_exec != 0)
					path_exec = test_with_path(path, sep, argv, i);
				if (_strcmp(sep[0], "exit") == 0)
				{
					free_separate_av(sep);
					exit_procedure(buffer, path, env, status);
				}
				if (buffer != NULL && path_exec == 1 && stat(sep[0], &st) == 0)
					status = _execute(sep[0], sep, argv, i);
				else if (buffer != NULL && path_exec == 1 && env_exec == 1)
					status = error_file(sep[0], i, argv, 0);
			}
		if (sep != NULL)
			free_separate_av(sep);
		free(buffer);
		size_test = 0;
	} while (1);
}

/**
 * _execute - Execute the command passes
 *
 * @cmd: The command passes by the user
 * @sep: Array of string with all arguments for the command
 * @argv: Argument value passes when the program is executed
 * @i: The count of loop
 *
 * Return: 1 if an error is occurs, 0 if is a success
 */
int _execute(char *cmd, char **sep, char **argv, int i)
{
	pid_t child_pid;
	int status;

	if ((cmd[0] == '.' && cmd[1] == '.' && cmd[3] == '\0') || access(cmd, X_OK))
		return (error_file(cmd, i, argv, 2));

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (2);
	}
	if (child_pid == 0)
	{
		if (execve(cmd, sep, environ) == -1)
		{
			return (2);
		}
	}
	else
	{
		wait(&status);
	}

	if (status > 0)
		status = 2;

	return (status);
}
