#ifdef FG_GFX_ESSL_PRECISION_DEF
precision highp float;

varying highp vec3 v_position;
varying highp vec3 v_normal;
varying highp vec2 v_texCoord;
varying highp vec4 v_color;

uniform mediump float u_Phase;
uniform mediump vec4  u_CustomColor;
#else

varying vec3 v_position;
varying vec3 v_normal;
varying vec2 v_texCoord;
varying vec4 v_color;

uniform float u_Phase;
uniform vec4  u_CustomColor;
#endif

uniform sampler2D s_texture;
uniform samplerCube s_skybox;
uniform float u_drawSkyBox;
uniform float u_useTexture;

void main()
{
	vec4 texel;
	
	if(u_useTexture > 0.5) {
		if(u_drawSkyBox < 0.5) {

			texel = texture2D(s_texture, v_texCoord);
		} else {
			v_position.y = -1.0 * v_position.y;
			texel = textureCube(s_skybox, v_position);
		} 
	} else {
		texel = vec4(1.0, 1.0, 1.0, 1.0);
	}
    
	gl_FragColor = texel; 
}
