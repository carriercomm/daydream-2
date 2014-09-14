#version 440

uniform vec3 La;

layout (binding=0) uniform sampler2D DiffuseTexture;
layout (binding=1) uniform sampler2D LightingTexture;

in VertexData
{
	vec3 Position;
	vec2 TextureCoord;
} Input;

out vec4 frag_Diffuse;

void main()
{
	vec4 DiffuseTexel = texture(DiffuseTexture, Input.TextureCoord);
	vec4 LightingTexel = texture(LightingTexture, Input.TextureCoord);

	//frag_Diffuse = DiffuseTexel * (vec4(La, 0.0) * (vec4(LightingTexel.rgb, 0.0) + vec4(LightingTexel.a, LightingTexel.a, LightingTexel.a, 0.0)));
	frag_Diffuse = DiffuseTexel * (vec4(La, 0.0) + LightingTexel);
	//frag_Diffuse = vec4(LightingTexel.r, LightingTexel.g, LightingTexel.b, 1.0);
}