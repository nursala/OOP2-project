// GaussianBlur.frag
uniform sampler2D texture;
uniform float radius; // مدى التنعيم
uniform vec2 direction; // (1,0)=أفقي (0,1)=رأسي

void main()
{
    vec2 size = vec2(textureSize(texture, 0));
    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = vec4(0.0);
    float sum = 0.0;

    // 9 عينات كافية (يمكنك زيادتها لنعومة أعلى)
    for (int i = -4; i <= 4; ++i)
    {
        float weight = exp(-float(i*i) / (2.0 * radius * radius));
        color += texture2D(texture, uv + direction * i * radius / size) * weight;
        sum += weight;
    }
    gl_FragColor = color / sum;
}
