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


layout (binding=0) uniform sampler2D DiffuseTexture;

in VertexData
{
	vec3 Position;
	vec2 TextureCoord;
} Input;

out vec4 FragmentColor;

void main()
{
	vec4 DiffuseTexel = texture(DiffuseTexture, Input.TextureCoord);

	//FragmentColor = LightingTexel + vec4(LightingTexel.a, LightingTexel.a, LightingTexel.a, 0.0);
	//FragmentColor = DiffuseTexel;

	FragmentColor = DiffuseTexel;
	//FragmentColor = DiffuseTexel * (vec4(La, 0.0) + vec4(LightingTexel.rgb, 0.0)) + vec4(LightingTexel.a, LightingTexel.a, LightingTexel.a, 0.0);
	//FragmentColor = vec4(pow(_FragmentColor.rgb, vec3(1.0 / Gamma)), _FragmentColor.a);
}