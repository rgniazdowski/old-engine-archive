precision highp float;

// Matrices
uniform mat4 u_mvMatrix;
uniform mat4 u_mvpMatrix;

// Attributes
attribute vec4 a_position; 
attribute vec3 a_normal;
attribute vec2 a_texCoord;

varying mediump vec3 v_position;
varying mediump vec3 v_normal;
varying mediump vec2 v_texCoord;

void main()
{
    // Define position and normal in model coordinates. he?
    vec4 mcPosition = a_position;
	//mcPosition.xyz = a_position;
	//mcPosition.w = 0.0;
    
	  gl_Position = u_mvpMatrix * mcPosition;    
	
	v_position = a_position.xyz;
	v_texCoord = a_texCoord;
	v_normal = a_normal;
}