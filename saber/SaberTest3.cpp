#include "SaberTest3.h"

void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
	vec3 trinagleNormal;
	int i;

	for (i = 0; i < nverts; i++)
	{
		normals[i] = vec3(0.0f);
	}

	for (i = 0; i < nfaces; i++)
	{
		int iIndexStartId = i * 3;
		int a = faces[iIndexStartId];
		int b = faces[iIndexStartId + 1];
		int c = faces[iIndexStartId + 2];

		//if traingle is ccw
		//trinagleNormal = cross(verts[c] - verts[a], verts[b] - verts[a]);
		trinagleNormal = cross(verts[b] - verts[a], verts[c] - verts[a]);

		//if no area-weight
		//trinagleNormal = normalize(trinagleNormal);

		normals[a] += trinagleNormal;
		normals[b] += trinagleNormal;
		normals[c] += trinagleNormal;
	}

	for (i = 0; i < nverts; i++)
	{
		normals[i] = normalize(normals[i]);
	}
}
