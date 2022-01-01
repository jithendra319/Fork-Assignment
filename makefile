createchilds.out: aosmain.o inorder.o create.h
	gcc aosmain.o create.h -o createchilds.out
	
aosmain.o:aosmain.c create.h
	gcc -c aosmain.c 

createchilds.o: createchilds.c create.h
	gcc -c createchilds.c

inorder.o: inorder.c 
	gcc -c inorder.c	 
	
clean:
	rm -f *.o *.out



