CC = gcc
Lib = 
file = erickbaca_assigment1
Exe = erick_demo 
$(Exe):	$(file).o
	$(CC) $(file).o -o $(Exe) $(Lib)
$(file).o:	$(file).c 
	$(CC) -c $(file).c 
clean:
	rm *.o $(Exe)
