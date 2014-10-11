#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;

varying highp vec3 v_position;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;
#else
varying vec3 v_position;
varying vec2 v_texCoord;
varying vec4 v_color;
#endif
uniform sampler2D s_texture;
uniform float u_useTexture;

void main()
{
    vec4 texel;
	if(u_useTexture > 0.5)
		texel = texture2D(s_texture, v_texCoord);
	else
		texel = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragColor = texel * v_color;
}

