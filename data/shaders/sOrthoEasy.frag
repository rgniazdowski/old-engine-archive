#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;

varying highp vec3 v_position;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;

uniform mediump vec4  u_CustomColor;
#else
varying vec3 v_position;
varying vec2 v_texCoord;
varying vec4 v_color;

uniform vec4  u_CustomColor;
#endif
uniform sampler2D s_texture;
uniform float u_useTexture;

void main()
{
    vec4 texel;
	if(u_useTexture > 0.5)
		texel = texture2D(s_texture, v_texCoord);
	else
		texel = u_CustomColor;
    gl_FragColor = texel * v_color * u_CustomColor;
}

