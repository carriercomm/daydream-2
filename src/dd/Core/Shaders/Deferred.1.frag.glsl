#version 440

layout (binding = 0) uniform sampler2D DiffuseTexture;
layout (binding = 1) uniform sampler2D NormalMap;
layout (binding = 2) uniform sampler2D SpecularMap;

uniform mat4 V;
uniform float MaterialShininess;

in VertexData
{
	vec3 Position;
	vec3 Normal;
	vec3 Tangent;
	vec3 BiTangent;
	vec2 TextureCoord;
	vec4 DiffuseColor;
	vec4 SpecularColor;
	vec4 BoneIndices1;
	vec4 BoneIndices2;
	vec4 BoneWeights1;
	vec4 BoneWeights2;
} Input;

out vec4 GDiffuse;
out vec4 GPosition;
out vec4 GNormal;
out vec4 GSpecular;

void main()
{
	// Diffuse Texture
	GDiffuse = texture(DiffuseTexture, Input.TextureCoord) * Input.DiffuseColor;

	// G-buffer Position
	GPosition = vec4(Input.Position.xyz, 1.0);

	// G-buffer Normal
	mat3 TBN = mat3(Input.Tangent, Input.BiTangent, Input.Normal);
	GNormal = normalize(vec4(TBN * vec3(texture(NormalMap, Input.TextureCoord)), 0.0));

	// G-buffer Specular
	vec4 specularGloss = texture(SpecularMap, Input.TextureCoord);
	float specularExponent = MaterialShininess;
	GSpecular = vec4(specularGloss.rgb, specularExponent);

}