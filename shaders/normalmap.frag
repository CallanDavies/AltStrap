// a normal map fragment shader
#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;

out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 Ka; // material ambient
uniform vec3 Kd; // material diffuse
uniform vec3 Ks; // material specular
uniform float specularPower;

uniform vec3 Ia; // light ambient
uniform vec3 Id; // light diffuse 
uniform vec3 Is; // light specular
uniform vec3 LightDirection;

// values for a second light
uniform vec3 Id2; // light diffuse 2
uniform vec3 Is2; // light specular 2
uniform vec3 LightDirection2;

uniform vec3 cameraPosition;

void main()
{
vec3 N = normalize(vNormal);
vec3 T = normalize(vTangent);
vec3 B = normalize(vBiTangent);
vec3 L = normalize(LightDirection);
vec3 L2 = normalize(LightDirection2);

mat3 TBN = mat3(T,B,N);

vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;
vec3 texNormal = texture( normalTexture, vTexCoord).rgb;

N = TBN * (texNormal * 2 - 1);

// calculate lambert term
float lambertTerm = max( 0, dot( N, -L ) );
float lambertTerm2 = max( 0, dot( N, -L2 ) );

// calculate view vector and reflection vector
vec3 V = normalize(cameraPosition - vPosition.xyz);
vec3 R = reflect( L, N );

// calculate specular term
float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );

// calculate each light property
vec3 ambient = Ia * Ka * texDiffuse;
vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
vec3 specular = Is * Ks * texSpecular * specularTerm;

// caluculate each light property 2
vec3 diffuse2 = Id2 * Kd * texDiffuse * lambertTerm2;
vec3 specular2 = Is2 * Ks * texSpecular * specularTerm;

FragColour = vec4(ambient + diffuse + diffuse2 + specular + specular2, 1);
}