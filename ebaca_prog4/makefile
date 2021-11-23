CC = gcc
Lib = 
file = bankClient
Exe = ebaca
$(Exe):	$(file).o
	$(CC) $(file).o -o $(Exe) $(Lib)
$(file).o:	$(file).c 
	$(CC) -c $(file).c 
clean:
	rm *.o $(Exe) *.dat 