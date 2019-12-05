#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = fragColor * texture(texSampler, fragTexCoord);
    //vec4 texColor = texture(texSampler, fragTexCoord);
    //outColor = vec4(fragColor.rgba * texColor.rbga);

    //float blendFactor = step(3.0f, dot(texColor.rgba, fragColor.rgba));
    //outColor = vec4(mix(fragColor, texColor, step(3.0, dot(fragColor.rgb, fragColor.rgb))).rgb, fragColor.rgba * texColor.rbga);
}
