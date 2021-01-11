#version 440 core 
layout (location = 0) out vec4 rt0_hdr; 

layout (location = 0) in vec3 f3Normal;
layout (location = 1) in vec3 f3Tangent;
layout (location = 2) in vec3 f3Bitangent;
layout (location = 3) in vec2 f2UV;
layout (location = 4) in vec3 f3WorldPosition;

uniform sampler2D uDiffuseMap;
uniform sampler2D uSpecularMap;
uniform sampler2D uGlossnesMap;
uniform sampler2D uBumpMap;
uniform vec3 uEye;
uniform vec3 uLigthDir;

void main()
{
	vec3 diffuse = texture(uDiffuseMap, f2UV).xyz;
	vec3 specular = texture(uSpecularMap, f2UV).xyz;
	float glossnes = texture(uGlossnesMap, f2UV).x;
 
	vec2 invSize = 1.0 / textureSize(uBumpMap, 0).xy;
	float dX = texture(uBumpMap, f2UV - invSize.x).x - texture(uBumpMap, f2UV + invSize.x).x;
	float dY = texture(uBumpMap, f2UV - invSize.y).x - texture(uBumpMap, f2UV + invSize.y).x;

	vec3 n = normalize(f3Normal + dX * f3Tangent + dY * f3Bitangent);

	vec3 l = -uLigthDir;
	vec3 r = reflect(n, l);
	vec3 c = normalize(uEye - f3WorldPosition);

	rt0_hdr.xyz = diffuse * dot(n, l) + specular * pow(dot(r, c), 3000.0 * glossnes);
	rt0_hdr.a = 1.0;
}