#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include "Group.h"
#include "Hit.h"
#include "Ray.h"
#include <string.h>

using namespace std;

//float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  // Fill in your implementation here.
  char* in;
  char* out;
  int width;
  int height;
  bool depth_ON = false;
  float depthMin;
  float depthMax;
  char* depthOut;
  char* normalsOut;
  bool normals_ON = false;

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  for( int argNum = 1; argNum < argc; ++argNum )
    {
      std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }
	
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  for( int ind = 1; ind < argc; ind++ ){
        if (strcmp(argv[ind], "-input") == 0){
            in = argv[ind+1];
	    ind+=1;
        }
	else if (strcmp(argv[ind], "-size") == 0){
            width = atoi(argv[ind+1]);
	    height = atoi(argv[ind+2]);
	    ind+=2;
        }
	else if (strcmp(argv[ind], "-output") == 0){
            out = argv[ind+1];
	    ind+=1;
        }
	else if (strcmp(argv[ind], "-depth") == 0){
            depth_ON = true;
	    depthMin = atof(argv[ind+1]);
	    depthMax = atof(argv[ind+2]);
	    depthOut = argv[ind+3];
	    ind+=3;
        }
	else if (strcmp(argv[ind], "-normals") == 0){
            normals_ON = true;
	    normalsOut = argv[ind+1];
	    ind+=1;
        }
	else{
	    return -1;
	}
  }

  //Analyze the scene
  SceneParser scene = SceneParser(in);

  Image myIMG = Image(width, height);
  myIMG.SetAllPixels(scene.getBackgroundColor());

  for (int i = 0; i<width; i++){
  	for (int j = 0; j<height; j++){
	    Vector2f coord = Vector2f( (2*float(i) / (width-1)) -1 , (2*float(j) / (height-1)) -1 );
	    Ray r = scene.getCamera()->generateRay(coord);
	    Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));

	    if (scene.getGroup()->intersect(r, h, scene.getCamera()->getTMin())){
		Vector3f pixCol = Vector3f(0.0f, 0.0f, 0.0f);
		
		//Diffuse color
		for (int indL = 0; indL < scene.getNumLights(); indL++){
		    Light* lit = scene.getLight(indL);
		    Vector3f litDir;
		    Vector3f litCol;
		    float distToLit;

		    lit->getIllumination(r.pointAtParameter(h.getT()), litDir, litCol, distToLit);

		    Vector3f shadingCol = h.getMaterial()->Shade(r, h, litDir, litCol);
		    pixCol = pixCol + shadingCol;
		}
		//Ambient color
		pixCol = pixCol + h.getMaterial()->getDiffuseColor()*scene.getAmbientLight();

		//Set pixel
		myIMG.SetPixel(j, i, pixCol);
	    }
	}
  }

  myIMG.SaveTGA(out);

  //Depth Implementation
  if (depth_ON){
	Image imgDepth = Image(width, height);
	imgDepth.SetAllPixels(Vector3f(0.0f, 0.0f, 0.0f));
	for (int i = 0; i<width; i++){
  	    for (int j = 0; j<height; j++){
	        Vector2f coord = Vector2f( (2*float(i) / (width-1)) -1 , (2*float(j) / (height-1)) -1 );
	        Ray r = scene.getCamera()->generateRay(coord);
	        Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));

		if(scene.getGroup()->intersect(r, h, scene.getCamera()->getTMin())){
		    if (depthOut != NULL){
		        if (h.getT() < depthMin){
			    imgDepth.SetPixel(j, i, Vector3f(1.0f, 1.0f, 1.0f));
			}
			else if (h.getT() > depthMax) {
			    imgDepth.SetPixel(j, i, Vector3f(0.0f, 0.0f, 0.0f));
			}
			else{
			    float grayScale = (depthMax - h.getT()) / (depthMax - depthMin);
			    imgDepth.SetPixel(j, i, Vector3f(grayScale, grayScale, grayScale));
			}
		    }
		}
	    }
	}
	imgDepth.SaveTGA(depthOut);  
  }

  //Normal Implementation
  if (normals_ON){
	Image imgNormals = Image(width, height);
	imgNormals.SetAllPixels(Vector3f(0.0f, 0.0f, 0.0f));
	for (int i = 0; i<width; i++){
  	    for (int j = 0; j<height; j++){
	        Vector2f coord = Vector2f( (2*float(i) / (width-1)) -1 , (2*float(j) / (height-1)) -1 );
	        Ray r = scene.getCamera()->generateRay(coord);
	        Hit h = Hit(FLT_MAX, NULL, Vector3f(0.0f, 0.0f, 0.0f));

		if(scene.getGroup()->intersect(r, h, 0.0f)){
		    Vector3f pixColNorm = h.getNormal().normalized();
		    for (int x = 0; x < 3; x++){
			if (pixColNorm[x] < 0){
			    pixColNorm[x] = pixColNorm[x] * -1.0f;
			}
		    }
		    imgNormals.SetPixel(j, i, pixColNorm);
		}
	    }
	}
	imgNormals.SaveTGA(normalsOut);
  }
  
 /*
  ///TODO: below demonstrates how to use the provided Image class
  ///Should be removed when you start
  Vector3f pixelColor (1.0f,0,0);
  //width and height
  Image image( 10 , 15 );
  image.SetPixel( 5,5, pixelColor );
  image.SaveImage("demo.bmp");
 */

  return 0;
}

