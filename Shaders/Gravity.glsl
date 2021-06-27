#define MAX_CELESTIAL_BODIES 128
#define G 1.0
#define PIXEL_MASS 1.0

uniform vec2 positions[MAX_CELESTIAL_BODIES];
uniform float masses[MAX_CELESTIAL_BODIES];

uniform int numCelestialBodies;

float GravitationalForce(in vec2 coord)
{
	float totalForce = 0.0;

	for (int i = 0; i < numCelestialBodies; i++)
	{
		totalForce += G * (PIXEL_MASS * masses[i]) / pow(distance(positions[i], coord), 2.0);
	}

	return totalForce;
}

float Modify(in float x)
{
	return 1.0 - exp(-x);
}

void main()
{
	float color = Modify(GravitationalForce(gl_FragCoord.xy));
	gl_FragColor = vec4(color * (1.0 / 3.0), color, color * 2.0, 1.0);
}