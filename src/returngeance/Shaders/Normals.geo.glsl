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

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
} Input[3];

out VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
} Output;

void main()
{
	for (int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = MVP * vec4(Input[i].Position, 1.0);
		EmitVertex();
		gl_Position = MVP * vec4(Input[i].Position + Input[i].Normal, 1.0);
		EmitVertex();
		EndPrimitive();

		Output.Position = Input[i].Position;
		Output.Normal = Input[i].Normal;
		Output.TextureCoord = Input[i].TextureCoord;
	}
}