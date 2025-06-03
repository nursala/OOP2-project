uniform vec2 lightPos;
uniform float lightRadius;
uniform float directionAngle;
uniform float fov;
uniform vec2 resolution;

const vec4 lightColor = vec4(1.0, 1.0, 0.6, 1.0);

void main() {
    vec2 fragPos = gl_FragCoord.xy;
    vec2 uv = fragPos / resolution; // ← الآن يتم استخدام resolution
    vec2 toFrag = fragPos - lightPos;

    float dist = length(toFrag);
    if (dist > lightRadius)
        discard;

    float angle = atan(toFrag.y, toFrag.x);
    float halfFOV = fov / 2.0;

    float angleDiff = mod(angle - directionAngle + 3.14159265, 6.2831853) - 3.14159265;
    if (abs(angleDiff) > halfFOV)
        discard;

    float attenuation = 1.0 - (dist / lightRadius);
    gl_FragColor = vec4(lightColor.rgb, lightColor.a * attenuation * 0.9);
}
