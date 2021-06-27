#define MAX_CELESTIAL_BODIES 128

uniform vec2 positions[MAX_CELESTIAL_BODIES];
uniform float masses[MAX_CELESTIAL_BODIES];

uniform int numCelestialBodies;
uniform float G;
uniform float pixelMass;

uniform float time;

float Force(in vec2 coord)
{
	float totalForce = 0.0;

	for (int i = 0; i < numCelestialBodies; i++)
	{
		totalForce += G * (pixelMass * masses[i]) / pow(distance(positions[i], coord), 2.0);
	}

	return totalForce;
}

float Modify(in float x)
{
	return 1.0 - exp(-x);
}

void main()
{
	float force = Force(gl_FragCoord.xy);
	float c = mod(force, 0.1) / 0.1;

	if (force > 0.5)
	{
		c = Modify(force);
	}

	gl_FragColor = vec4(c * (sin(time) + 1.0) / 2.0, c * (cos(time) + 1.0) / 2.0, c, (sin(time * 0.25) + 2.5) / 2.0);
}