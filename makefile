cShell: cShell.h cShell.c read_command.c type_prompt.c buildin_command.c parsing.c
	gcc cShell.c read_command.c type_prompt.c buildin_command.c parsing.c -o cShell

clean:
	rm -f cShell
