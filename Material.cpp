#include "Material.h"
#include "iostream"

using namespace std;

Vector3f Material::Shade(const Ray& ray, const Hit& hit,
			 const Vector3f& dirToLight, const Vector3f& lightColor){

	Vector3f n = hit.getNormal().normalized();
	Vector3f mydiffuseColor;
	Vector3f myspecularColor;

	//Diffuse Shading w/ clamping
	float nDotl = Vector3f::dot(n, dirToLight);
	if (nDotl < 0){
	    nDotl = 0;
	}
	
	if (t.valid()){
	    Vector3f texColor = t(hit.texCoord[0], hit.texCoord[1]);
	    mydiffuseColor = nDotl*texColor*lightColor;
	    diffuseColor = texColor;
	}
	else{
	    mydiffuseColor = nDotl*diffuseColor*lightColor;
	}

	//Phong Shading w/ clamping
	Vector3f v = ray.getDirection()*-1.0f;
	Vector3f r = (dirToLight*-1.0f) + 2.0f*n*(nDotl);
	r.normalized();

	float vDotr = Vector3f::dot(v, r);
	if (vDotr < 0){
	    vDotr = 0;
	}

	myspecularColor = specularColor*pow(vDotr, shininess)*lightColor;

	return mydiffuseColor + myspecularColor;
}
