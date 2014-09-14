#version 440

uniform mat4 MVP;

layout (location = 0) in vec3 Position;

out VertexData
{
	vec3 Position;
	vec2 TextureCoord;
} Output;

void main()
{
	gl_Position = MVP * vec4(Position, 1.0);
	Output.Position = Position;
	Output.TextureCoord = (vec2(Position) + 1.0) / 2.0;
}