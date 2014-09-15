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

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 DepthMVP;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TextureCoord;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 BiTangent;

out VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
	vec4 ShadowCoord;
	vec3 Tangent;
	vec3 BiTangent;
} Output;

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);

	Output.Position = vec3(V * M * vec4(Position, 1.0));
	Output.Normal = normalize(vec3(inverse(transpose(V * M)) * vec4(Normal, 0.0)));
	Output.TextureCoord = TextureCoord;
	Output.ShadowCoord = DepthMVP * vec4(Position, 1.0);
	Output.Tangent = normalize(vec3(inverse(transpose(V * M)) * vec4(Tangent, 0.0)));
	Output.BiTangent = normalize(vec3(inverse(transpose(V * M)) * vec4(BiTangent, 0.0)));
}