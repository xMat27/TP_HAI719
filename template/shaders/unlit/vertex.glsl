#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 mvp;
//uniform mat4 modelView;
//uniform mat4 normalMatrix;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;


out vec3 o_positionWorld;
out vec3 o_normalWorld;
out vec2 o_uv0;

out vec3 TangentFragPos;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out mat3 TBN;

out vec3 Position;
out vec3 Normal;

uniform samplerCube skybox;

void main()
{
    Normal = mat3(transpose(inverse(model))) * normal;
    Position = vec3(model * vec4(position, 1.0));
    gl_Position = projection * view * vec4(position, 1.0);
}  


// void main() {
//   mat3 normalMatrix = mat3(transpose(inverse(model)));
//   o_uv0 = vec2(uv0.x, -uv0.y);
//   vec4 positionWorld = model * vec4(position, 1.0);
//   o_positionWorld = positionWorld.xyz;
//   o_normalWorld = normalMatrix * normal;

//   vec3 T = normalize(normalMatrix * tangent);
//   vec3 N = normalize(normalMatrix * normal);
//   T = normalize(T - dot(T, N) * N);
//   vec3 B = cross(N, T);
  
//   TBN = transpose(mat3(T, B, N));    
//   // TangentLightPos = TBN * lightPos;
//   // TangentViewPos  = TBN * viewPos;
//   // TangentFragPos  = TBN * uv0;

//   gl_Position = projection * view * positionWorld;
// }
