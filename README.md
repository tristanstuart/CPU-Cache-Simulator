# CS3339HW3

## Compiling
The program can be compiled with the command ```g++ -o <program_name> main.cpp Cache.cpp``` where ```<program_name>``` is replaced with what you want to call the program.

## Running
The program can be run on Linux with this command:
```
./<program_name> <total_cache_entries> <num_cache_ways> <input_file_name>
```
or on Windows with this one:
```
.\<program_name> <total_cache_entries> <num_cache_ways> <input_file_name>
``` 
### program_name
```<program_name>``` is the program name specified during compilation.
### total_cache_entries
```<total_cache_entries>``` is the number of entries for the desired cache simulation. This value must be greater than 0.
### num_cache_ways
```<num_cache_ways>``` is the number of ways desired for cache simulation. This value must be a value > 0.
### input_file_name
```<input_file_name>``` is the name of the input file to be used with the program. It is recommended to put the input file in the same directory as the runnable file. The addresses in the input must all be greater than 0, this makes sense as a cache would not have negative memory addresses.

## Output
The program will output hits and misses to a file named ```cache_sim_output``` which will be created in the program directory.

## Known Bugs
At the time of uploading I have not seen bugs in the program. 

As far as limited functionality, the program exits when the number of arguments is incorrect, or the type of any argument is incorrect. Additionally, the program will exit when it encounters a negative value from the input file, however due to the functionality of the program some values will have already been processed and written to the output file.
