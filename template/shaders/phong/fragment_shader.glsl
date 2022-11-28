#version 330 core

out vec4 FragColor;
in vec3 o_color;
in vec2 o_uv;

uniform sampler2D tex;

void main() {
    FragColor = texture(tex, o_uv) * vec4(o_color, 1.0);
}
