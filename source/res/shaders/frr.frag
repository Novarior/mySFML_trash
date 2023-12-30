//#version 320 core
#ifdef GL_ES
precision mediump float;
#endif

uniform vec3 location;
uniform vec3 inPosition;
uniform mat4 modelViewProjection;

void main()
{
    modelViewProjection*vec4(inPosition,1.)+vec4(location,0.);
    gl_FragColor=vec4(modelViewProjection);
}
