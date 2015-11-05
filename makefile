cShell: cShell.h cShell.c read_command.c type_prompt.c buildin_command.c
	gcc cShell.c read_command.c type_prompt.c buildin_command.c -o cShell

clean:
	rm -f cShell
