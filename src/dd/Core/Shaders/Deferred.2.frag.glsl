#version 440

layout (binding=0) uniform sampler2D PositionTexture;
layout (binding=1) uniform sampler2D NormalTexture;
layout (binding=2) uniform sampler2D SpecularTexture;

uniform vec2 ViewportSize;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 LightPosition;
uniform float LightRadius;
uniform vec3 LightSpecular;
uniform vec3 LightDiffuse;

out vec4 FragmentColor;

vec4 phong(vec3 position, vec3 normal, vec3 specular, float specularExponent)
{
	// Diffuse
	vec3 lightPos = vec3(V * vec4(LightPosition, 1.0));
	vec3 distanceToLight = lightPos - position;
	vec3 directionToLight = normalize(distanceToLight);
	float dotProd = dot(directionToLight, normal);
	dotProd = max(dotProd, 0.0);
	vec3 Idiffuse = LightDiffuse * dotProd;

	// Specular
	//vec3 reflection = reflect(-directionToLight, normal);
	vec3 surfaceToViewer = normalize(-position);
	vec3 halfWay = normalize(surfaceToViewer + directionToLight);
	float dotSpecular = max(dot(halfWay, normal), 0.0);
	float specularFactor = pow(dotSpecular, specularExponent);
	vec3 Ispecular = specular * LightSpecular * specularFactor;

	//Attenuation
	float dist = distance(lightPos, position);
	//float attenuation = 1.0 - pow(dist / LightRadius, 2);
	float attenuation = pow(max(0.0f, 1.0 - (dist / LightRadius)), 2);

	return vec4((Idiffuse + Ispecular) * attenuation, 1.0);
}

void main()
{
	vec2 TextureCoord = gl_FragCoord.xy / ViewportSize;
	vec4 PositionTexel = texture(PositionTexture, TextureCoord);
	vec4 NormalTexel = texture(NormalTexture, TextureCoord);
	vec4 SpecularTexel = texture(SpecularTexture, TextureCoord);

	FragmentColor = phong(PositionTexel.xyz, normalize(NormalTexel.xyz), SpecularTexel.rgb, SpecularTexel.a);
	//FragmentColor = vec4(1, 1, 1, 1);
}