# systems-Prog 							PROJECT 1 
Readme
You must use
gcc -o sorter sorter.c mergeString.c
sorter –c columnname
to execute the code.
Main
Implements shared memory using mmap and memset to keep a place for all processes to be calculated in total and to keep track of the original PID.  It checks for 3 arguments as we only use the default behavior. It calls the listdir method and we create a variable to hold what column must be sorted.
ListDir
This method first goes about reading through a directory and creating new processes based on finding other directories or csvs. It uses the counter implemented in shared memory using mmap, in order to keep track of the total number of processes, it as well checks if such memory is available. It implements the printf method to output the number of PIDS, with fflush to clear the outputstream to make sure there are no replicas in output. There are two forks, one for csvs and one for directories. After the fork there is an increment to our shared memory space. We use a wait do-while loop to wait for any remaining processes. We as well use exit to terminate children and implement it in a conditional that checks for children using our original/first pid to see if we must exit. The program is done recursively as a multi-process program.

FORKING: 
Our program will fork the process after it hits the DIR or CSV file. After forking the CSV file, it the check if that CSV file has the corrent header. If the header matches then process continues to merge sort, if the header is invalid, it will display message.Thus, we do forking everytime but we restrict the sorting only to valid CSV file.
FOR EG:
If the total forking is of 4 process, it will show total process as 4. But if one of them is invalid CSV file out of 4 CSV files, then it print the output in current directory of only 3 CSV files which were valid.

MERGESORT: 
We use the same algorithm of merge sort from previous project0.

