/*
	This file is part of Daydream Engine.
	Copyright 2014 Adam Byléhn, Tobias Dahl, Simon Holmberg, Viktor Ljung
	
	Daydream Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Daydream Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Daydream Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#version 430

uniform vec4 Color;
uniform vec3 La;
uniform vec3 directionToSun;
uniform mat4 V;

layout(binding=0) uniform sampler2D texture0;
layout(binding=1) uniform sampler2D PositionTexture;
layout(binding=2) uniform sampler2D NormalsTexture;
layout(binding=3) uniform sampler2D SpecularTexture;

const vec3 ks = vec3(1.0, 1.0, 1.0);
const vec3 kd = vec3(1.0, 1.0, 1.0);
const vec3 ka = vec3(1.0, 1.0, 1.0);
const float kshine = 1.0;
const vec3 SunDiffuseLight = vec3(1.0, 1.0, 1.0);
const vec3 SunSpecularLight = vec3(1.0, 1.0, 1.0);
const vec3 SunPos = directionToSun*vec3(100);
const float specularExponent = 100;

in VertexData {
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
} Input;
 
out vec4 frag_Diffuse;

vec4 phong(vec3 position, vec3 normal, vec3 specular)
{
	
	//Diffuse Sunlight
	vec3 directionToLight = normalize(vec3(V * vec4(directionToSun, 0.0)));
	float dotProdLight = dot(directionToLight, normal);
	dotProdLight = max(dotProdLight, 0.0);
	vec3 sId = kd * SunDiffuseLight * dotProdLight;

	//Specular Sunlight
	vec3 surfaceToViewer = normalize(-position);
	vec3 halfWay = normalize(surfaceToViewer + directionToLight);
	float dotSpecular = max(dot(halfWay, normal), 0.0);
	float specularFactorSun = pow(dotSpecular, specularExponent);
	vec3 sIs = specular.r * SunSpecularLight * specularFactorSun;

	return vec4((sId), sIs.r);
}

void main() {
	vec4 texel = texture(texture0, Input.TextureCoord);
	vec4 PositionTexel = texture(PositionTexture, Input.TextureCoord);
	vec4 NormalTexel = texture(NormalsTexture, Input.TextureCoord);
	vec4 SpecularTexel = texture(SpecularTexture, Input.TextureCoord);


	frag_Diffuse = texel * Color;
	//frag_Diffuse = texel * Color * (vec4(La, 0.0) * phong(vec3(PositionTexel), vec3(NormalTexel), vec3(SpecularTexel)));
	//frag_Diffuse = DiffuseTexel * (vec4(La, 0.0) * (vec4(LightingTexel.rgb, 0.0) + vec4(LightingTexel.a, LightingTexel.a, LightingTexel.a, 0.0)));

}