1)Name- N.Jithendra Chowdary , BITS ID - 2021H1030032G

2) CONTENTS IN THE DIRECTORY ARE:
    aosmain.c create.h inorder.c createchilds.c README makefile out.ogv

    i)createchilds.c is the file which contains structure for the CreateChilds method defined in the create.h
    ii)Here I put the file createchilds.c in the header of aosmain.c file because createchilds.c and aosmain.c both share some common variables.So I created the variables in createchilds.c and imported into aosmain.c
    iii)create.h contains the declaration of CreateChilds function which i need to extend in another program.
    iv)inorder.c contains the code for inorder traversal of the PIDS.
    v)makefile for compiling
    v)README contains description about how to do and what to do.
    vi)out.ogv is the ouput video file of the my terminainl in kali linux

3) makefile is used to compile my program easily.Using this we need not re compile program every time entering long commands.

4) After opening the terminal

    0) Enter "make" in the terminal then files get compiled and a new object called "createchilds.out" will be created .

    i) Enter ./createchilds.out with command line arguments..
        -->1st argument represents No of childs to be created if PID is ODD..
        -->2nd argument represents No of childs to be created if PID is even..
        -->3rd argument represents the Depth of the level upto which processes needs to be created.

    ii) Ex: run ./createchilds.out 1 2 3  (./createchilds.out oddchilds evenchilds level)
        --> It creates 1 child if pid is odd and creates 2 childs if pid is even and creates this same upto level 3

5) createchilds.c contains the structure for the createchilds function which creates no of childs upto given level based on the PID(Odd or Even) .
   create.h declares the structure for the createchilds function which needs to be implemented in aosmain.c
   inorder.c contains the code for running inorder traversal of the PIDS.
   aosmain.c contains the driver code for all the above implemented programs.
   README Is about description of the files and how to do .

6) Everything in my program is working well.
    SUCCESSFULLY DONE :
        i) Program Creates the simultaneously Executing in the same level before Child starts Execution
        ii)It Prints the PID and PPID for every Process created.
        iii) It Prints the exit Status of every Process.( Order of Exiting of processes is what I printed for exit status rather than 0 because every successful exitting process will defenitely print 0 on exit.So Instead I put Order of 		Exitting Of processes )
        iV) Inorder Traversal Printing of PIDS....

7) NOTE:

i)When I run in Kali Linux( with architecture of KDE PLASMA ) Everything is fine and execution seems perfect.(Please Watch the attached video called out.ogv )

ii)But When I run my program in Ubuntu(Which is GNOME Architecture) Everything is Executed i.e level order creation,inorder traversal,Exit statuses and childs are exitted too. But Main Process is not getting exitted. Even Memory unmapping does succesffull.I am unmapping the shared memory at last i.e memory unmapping is done only if it is the last executing process and even it is succesfull which indicates main process is the one that is running last.

But I am Sure that every Child exitted and only main process remains unexitted .I checked Using "ps" command .SO After Running the program, Only Main process remains without exitting.So To exit Main Program use control + C to exit the main process. (Happens Only in UBUNTU)
