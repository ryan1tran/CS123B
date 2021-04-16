# RAT                                  
Welcome to Ryan’s (Bioinformatics Data) Analysis Tool, or RAT for short!   
   
Built entirely in C++, RAT's main purpose is to take in FASTA files and   
split it into two files, with 80% and 20% of the sequences in each file,   
respectively.   

It has additional functionality to adjust distance matrixes for UPGMA   
phylogenetric tree generation. That functionality is incomplete, but   
you can read more about it in the paper below if you are interested.   

[Here is the link to the paper that utilizes this program.](https://docs.google.com/document/d/1H_-oNjrvgFyuNgf0J52cLmy3mNMDlgFJHlLY949bgA8/edit?usp=sharing "Bioinformatics Paper")

## Information
This project contains three directories:   
	- source   
	- application   
	- data   

Within the 'source' directory is all the code used in this project. If you wish to   
compile it yourself, you may do so using either an IDE or through the command line.   

However, to save you time, the compiled '.exe' product is in the 'application' folder,   
along with a sample FASTA file and sample distance matrix to try the program with.   

The 'data' directory contains all data files used for this project. It is provided if   
you would like to run tests using the same data as used in the project.
   
   
## Running the Application
To run the application, first copy the 'application' folder somewhere onto your device.   
Once done, open up a command line (CMD for Windows and Terminal for Unix systems) and   
change directories to the application folder. Once inside, you will start the application   
by running the appropriate command:   
	- For Windows:	`.\RAT.exe`   
	- For Unix:	`./RAT.exe`   
   
Once the application is running and you see a logo appear on the command line window (as
seen below), you are all set. From there, read and follow the instructions provided to you.   
   
![Main View](main-view.PNG?raw=true "Title")   
