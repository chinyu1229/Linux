# exercise
Write a program that opens an existing file for writing with the O_APPEND flag, and
then seeks to the beginning of the file before writing some data. Where does the
data appear in the file? Why?

# answer
Always written at the end of the file.
* See open() documentation of the O_APPEND 


O_APPEND
The file is opened in append mode. Before each write(2), the file offset is positioned at the end of the file, as if with lseek(2).
