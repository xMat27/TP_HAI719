#version 330 core

in vec3 o_positionWorld;
in vec3 o_normalWorld;
in vec2 o_uv0;
out vec4 FragColor;

uniform vec4 color;
uniform sampler2D colorTexture;
uniform sampler2D normalMap;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

in vec3 TangentFragPos;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in mat3 TBN;

in vec3 Position;
in vec3 Normal;

uniform samplerCube skybox;

void main()
{             
    vec3 I = normalize(Position - viewPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}

// void main() {
//     vec3 normal = texture(normalMap, o_uv0).rgb;
//     normal = normal *2.0 -1.0;
//     normal = TBN*normal;
//     normal = normalize(normal);
//     // ambient
//     float ambientStrength = 0.5;
//     vec3 ambient = ambientStrength * lightColor ;
//     // diffuse
//     vec3 norm = normalize ( normal ) ;
//     vec3 lightDir = normalize ( lightPos - o_positionWorld ) ;
//     float diff = max ( dot ( norm , lightDir ) , 0.0) ;
//     vec3 diffuse = diff * lightColor ;
//     // specular
//     float specularStrength = 0.5;
//     vec3 viewDir = normalize ( viewPos - o_positionWorld ) ;
//     vec3 reflectDir = reflect ( - lightDir , norm ) ;
//     float spec = pow ( max ( dot ( viewDir , reflectDir ) , 0.0) , 32) ;
//     vec3 specular = specularStrength * spec * lightColor ;
//     vec3 result = ( ambient + diffuse + specular ) ;
//     FragColor = vec4 ( result , 1.0) ;

//     //FragColor = color;
//     FragColor *= texture(colorTexture, o_uv0) * color;
//     // DEBUG: position
//     //FragColor = vec4(o_positionWorld, 1.0);
//     // DEBUG: normal
//     // FragColor = vec4(0.5 * o_normalWorld + vec3(0.5) , 1.0);
//     // DEBUG: uv0
//     // FragColor = vec4(o_uv0, 1.0);

// }


