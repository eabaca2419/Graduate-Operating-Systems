CC = gcc
Lib = 
file = bankClient
Exe = bankClient
$(Exe):	$(file).o
	$(CC) $(file).o -o $(Exe) $(Lib)
$(file).o:	$(file).c 
	$(CC) -c $(file).c 
clean:
	rm *.o $(Exe) *.dat 