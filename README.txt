README.txt
==========================================================================================
Author:		Andrew Moran	|
Date:		11/15/2012	|
6.837 Computer Graphics		|
Assignment 4			|
=================================
__________________________________________________________________________________________
Compiling Instructions
==========================================================================================
	When I completed the assignment, I managed to run Linux through my Macbook Pro laptop with a Virtual Machine called VirtualBox.  I also tested on the campus Athena computer to make sure that it worked correctly.  Here are instructions
	1.	Unzip submission on Stellar and extract all files to designated directory
	2.	In terminal, cd to directory containing "assn4" folder
	3.	command make
	4.	if images not already in folder:
		command sh test_cases.sh
		This should reproduce the images generated from this assignment ranging from names _1-13 corresponding 			to scene number.
	5.	"assn4" folder contains all necessary files including updated 
		files, classes, subclasses, etc.

__________________________________________________________________________________________
Collaboration
==========================================================================================
	I had no further assitance other than the help I received from Professor/TAs at office hours.

__________________________________________________________________________________________
References
==========================================================================================
	⁃	6.837 Lecture Notes (Very Helpful)
        -	http://www.cplusplus.com/reference/
	- 	(Ray Tracing Primitives) http://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html

__________________________________________________________________________________________
Problems
==========================================================================================
	Currently, my code is functioning properly.  It took some time debugging, but should be a good solution.  My main problem was normalizing the normals.  For whatever class whether it was an object, shape, camera, material, etc I kept forgeting to normalize directions/normals which threw me off for a bit.  However, finally found my problem.

__________________________________________________________________________________________
Extra Credit
==========================================================================================
	Here are some added features to the assignment:
	•	Depth output - added optional argument that allows you to view depth map of image (look at _1d.tga)
	•	Normals output - added optional argument that allows you to view normals map of image (look at _1n.tga)
	•	Orthogonal camera - different from Perspective Camera.  View looks slightly different.  (lookat at OrthoCamera.cpp & 11.tga)
	•	Pipe Ray Tracing Primitive - I originally was implemenmting a ray-cylinder intersection, than realized with added constraints and code, I could make a more interesting pipe.  Took a while and research, but finally got it done. (look at Pipe.cpp & 12.tga & 13.tga) 

__________________________________________________________________________________________
Comments
==========================================================================================
	I felt very guided on this assignment by the lecture notes.  By following the slides and implementing the correst formulas and constraints, I saw progress fast.  The only thing that threw me off was normalizign normals.  I am still confused when I should/should not normalize vectors (for both normals and directions).  This resulted in very small discepancies in lightibng on my pictures.  After realizing that I didn't normalize (or normalized when I shouldn't have), I was able to fix my mistakes.  At first, I was stuck trying top implement textures in both Trinagle.cpp and Material.cpp.  This made me realize that my overall normal and textCoord was a weighted sum of the barycentric coordinates I calculated.  Also, you can access texCoord from hit.texCoord.  At this point, I had everything figured out except one small mishap.  When a texture was valid, I forgot to set the Kd for the ambient light to the new texCoord in addition to calculating the diffuse lighting.  As a result, I was able to finish on time and accomplish some extra credit.  After research, I was able to implement a pipe.  Images show the proper lighting of object when viewed at different angles.  It was complicated with many formulas and 4 possible values for t (could intersect inside,outside, top, bottom of open cylinder).  As a result, I got far and enjoyed this assignement.  

 
