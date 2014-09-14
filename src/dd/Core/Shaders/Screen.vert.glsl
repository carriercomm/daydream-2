#version 440

layout (location = 0) in vec3 Position;

out vec2 TextureCoord;

void main()
{
	gl_Position = vec4(Position, 1.0);
	TextureCoord = (vec2(Position) + 1.0) / 2.0;
}