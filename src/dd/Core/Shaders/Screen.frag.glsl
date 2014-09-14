#version 440

layout (binding=0) uniform sampler2D DiffuseTexture;

in vec2 TextureCoord;

out vec4 FragmentColor;

void main()
{
	FragmentColor = texture(DiffuseTexture, TextureCoord);
}