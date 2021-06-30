#define MAX_CELESTIAL_BODIES 128

uniform vec2 positions[MAX_CELESTIAL_BODIES];
uniform float masses[MAX_CELESTIAL_BODIES];
uniform float radii[MAX_CELESTIAL_BODIES];

uniform int numCelestialBodies;
uniform float G;
uniform float pixelMass;

float Force(in vec2 coord)
{
	float totalForce = 0.0;

	for (int i = 0; i < numCelestialBodies; i++)
	{
		float d = distance(positions[i], coord) - radii[i];
		if (d > 0.0)
		{
			totalForce += G * (pixelMass * masses[i]) / (d * d);
		}
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
	float a, b = 5.0, c = force;
	
	while (c > b)
	{
		c /= b;
	}

	a = fract(log(c));

	gl_FragColor = vec4(a * 0.5, a, a * 0.5, 1.0);

	for (int i = 0; i < numCelestialBodies; i++)
	{
		float d = distance(gl_FragCoord.xy, positions[i]);

		if (d <= radii[i])
		{
			gl_FragColor = vec4(0.2, 0.4, 1.0, 1.0);
		}
	}
}