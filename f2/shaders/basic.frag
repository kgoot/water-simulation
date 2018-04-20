#version 330 core

in vec3 fPos;

out vec4 FragColor;

uniform float radius;
uniform vec3 eye;
uniform mat4 view;
uniform mat4 proj;

void main() {
    vec3 n;
    n.xy = 2 * gl_PointCoord.st - vec2(1.f);
    n.y = -n.y;
    float r2 = dot(n.xy, n.xy);
    if (r2 > 1.f)
        discard;
    n.z = sqrt(1.f - r2);

    vec3 view_space_pos = (view * vec4(fPos, 1.f)).xyz;
    vec4 pos = vec4(view_space_pos + n * radius, 1.f);
    vec4 clip_pos = proj * pos;
    float depth = (1.f + clip_pos.z / clip_pos.w) / 2.f;
    gl_FragDepth = gl_DepthRange.near + gl_DepthRange.diff * depth;

    vec3 ldir = normalize(-pos.xyz);
    vec3 color = vec3(0.f, 0.5f, 0.8f);
    float diffuse = clamp(dot(n, ldir), 0.f, 1.f);
    FragColor = vec4(diffuse * color, 1.0);
}
