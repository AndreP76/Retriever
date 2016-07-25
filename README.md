# Retriever
A very simple C program I made for myself to help with fs operations. It searches for a filename in a directory specified and copies it to the current directory, keeping the same name.

#Usage
  retrieve <DirectoryToSearch> <FileName> [-c | -m]
  -c = copy the file, leaving the original in place
  -m = move the file. Copies the original to the new place, and deletes the original after.
  Use only one of these. Only the first one that appears will be considered. 
  Parameter order is *NOT* optional at the moment. 
  If neither -c or -m are specified, -c is used as a default-
  
#TODO
  An install script
  Possibility to change the copied file name
