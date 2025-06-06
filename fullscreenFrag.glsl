#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform float time;


void main() {
    vec2 uv = TexCoords;
    
    vec3 color = mix(vec3(1.0, 0.5, 0.0), vec3(0.5, 0.0, 0.5), uv.y);

    float wave = sin((uv.y + time * 0.5) * 10.0) * 0.03;
    uv.x += wave;

    color = mix(vec3(1.0, 0.5, 0.0), vec3(0.5, 0.0, 0.5), uv.y) + wave;

    FragColor = vec4(color, 1.0);
}