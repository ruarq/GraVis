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

float Modify(in float x)
{
	return 1.0 - exp(-x);
}

void main()
{
	float force = log(Force(gl_FragCoord.xy));
	float a, b = 5.0;
	
	while (force > b)
	{
		force /= b;
	}

	a = fract(force);

	gl_FragColor = vec4(a, a, a, 1.0);
}