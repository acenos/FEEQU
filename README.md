# FEEQU

## Requirements
* To compile the code is it necesary to install the sfml library, this depends
 on the OS you are using.
* Right now the program expects to find the sprites in the folder img. I am 
not adding the images to the repository because it is a bad practice.
Instead I have added a file with the urls of the images that the program needs

## Map file
* The map will be read from the file map.txt
* This file will be composed of integers and commas
* The first two integers will be the size of the map [W,H]
* The following two integers the initial position of the hero [X,Y]
* The rest of the integers will be the tiles of the map. 
If there are less tiles that there should be, ther rest will be Water

