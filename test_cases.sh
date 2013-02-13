#!/bin/sh
rm *.tga
rm *.bmp

./a4 -input scene01_plane.txt  -size 200 200 -output 1.tga -depth 8 12 _1d.tga -normals _1n.tga
./a4 -input scene02_cube.txt  -size 200 200 -output 2.tga
./a4 -input scene03_sphere.txt  -size 200 200 -output 3.tga
./a4 -input scene04_axes.txt  -size 200 200 -output 4.tga
./a4 -input scene05_bunny_200.txt  -size 200 200 -output 5.tga
./a4 -input scene06_bunny_1k.txt  -size 200 200 -output 6.tga
./a4 -input scene07_shine.txt  -size 200 200 -output 7.tga
./a4 -input scene08_c.txt -size 200 200 -output 8.tga
./a4 -input scene09_s.txt -size 200 200 -output 9.tga
./a4 -input scene10_cube_perspect.txt  -size 200 200 -output 10.tga
./a4 -input scene11_cube_ortho.txt  -size 200 200 -output 11.tga
./a4 -input scene12_pipe.txt  -size 200 200 -output 12.tga
./a4 -input scene13_pipe_top.txt  -size 200 200 -output 13.tga

./a4soln -input scene01_plane.txt  -size 200 200 -output 1soln.tga
./a4soln -input scene02_cube.txt  -size 200 200 -output 2soln.tga
./a4soln -input scene03_sphere.txt  -size 200 200 -output 3soln.tga
./a4soln -input scene04_axes.txt  -size 200 200 -output 4soln.tga
./a4soln -input scene05_bunny_200.txt  -size 200 200 -output 5soln.tga
./a4soln -input scene06_bunny_1k.txt  -size 200 200 -output 6soln.tga
./a4soln -input scene07_shine.txt  -size 200 200 -output 7soln.tga 
./a4soln -input scene08_c.txt -size 200 200 -output 8soln.tga
./a4soln -input scene09_s.txt -size 200 200 -output 9soln.tga
