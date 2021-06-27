#define MAX_CELESTIAL_BODIES 128

uniform vec2 positions[MAX_CELESTIAL_BODIES];
uniform float masses[MAX_CELESTIAL_BODIES];

uniform int numCelestialBodies;
uniform float G;
uniform float pixelMass;

float Force(in vec2 coord)
{
	float totalForce = 0.0;

	for (int i = 0; i < numCelestialBodies; i++)
	{
		totalForce += G * (pixelMass * masses[i]) / pow(distance(positions[i], coord), 2.0);
	}

	return totalForce;
}

void main()
{
	float c = mod(Force(gl_FragCoord.xy), 0.01) / 0.01;
	gl_FragColor = vec4(c * 0.4, c * 0.6, c, 1.0);
}