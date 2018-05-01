#version 330 core

in vec3 fPos;
in vec4 particleColor;

out vec4 color;

uniform float radius;
uniform vec3 eye;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 lightDir;

float Ns = 250;
vec4 mat_specular=vec4(1);
vec4 light_specular=vec4(1);


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

    float diffuse = max(0.0, dot(vec3(0,0,1), n));

    vec3 eye = vec3 (0.0, 0.0, 1.0);
    vec3 halfVector = normalize( eye + vec3(0,0,1));
    float spec = max(pow(dot(n,halfVector), Ns), 0.);
    vec4 S = light_specular*mat_specular* spec;

    color = vec4(0.1686f, 0.73333f, 1.0f, 1.0f) + (particleColor - 0.1) * diffuse + S;
}
