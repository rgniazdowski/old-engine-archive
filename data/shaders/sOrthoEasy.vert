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

uniform mat4 u_mvpMatrix;

attribute vec4 a_position; 
attribute vec2 a_texCoord;
attribute vec4 a_color;

void main()
{
    // Define position and normal in model coordinates. 
    vec4 mcPosition = a_position;
    
    gl_Position = u_mvpMatrix * mcPosition;    
	
	v_position = a_position.xyz;
	v_texCoord = a_texCoord;
	v_color = vec4(a_color.x, a_color.y, a_color.z, 1.0);
}
