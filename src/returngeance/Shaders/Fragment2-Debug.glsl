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
layout (binding=1) uniform sampler2D PositionTexture;
layout (binding=2) uniform sampler2D NormalTexture;

in VertexData
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
} Input;

out vec4 FragColor;

void DrawQuadrant(vec4 texel, vec2 quadrant)
{
	if (-quadrant.x * Input.Position.x < 0 && -quadrant.y * Input.Position.y < 0)
	{
		FragColor = texel;
	}
}

void main()
{
		vec4 DiffuseTexel = texture2D(DiffuseTexture, Input.TextureCoord);
		vec4 PositionTexel = texture2D(PositionTexture, Input.TextureCoord);
		vec4 NormalTexel = texture2D(NormalTexture, Input.TextureCoord);

		//FragColor = texture2D(DiffuseTexture, Input.TextureCoord * 2 + vec2(0, -1));
		DrawQuadrant(texture2D(DiffuseTexture, Input.TextureCoord * 2), vec2(-1, 1));
		DrawQuadrant(texture2D(PositionTexture, Input.TextureCoord * 2), vec2(1, 1));
		DrawQuadrant(texture2D(NormalTexture, Input.TextureCoord * 2), vec2(-1, -1));

		vec4 AllTexel = texture2D(DiffuseTexture, Input.TextureCoord*2)*texture2D(PositionTexture, Input.TextureCoord*2)*texture2D(NormalTexture, Input.TextureCoord*2);
		DrawQuadrant(AllTexel, vec2(1, -1));
}

