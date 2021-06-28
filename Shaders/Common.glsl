// All available variables when writing a shader for GraVis
// All of these are defined by the application and read only

#define MAX_CELESTIAL_BODIES 128

uniform vec2 positions[MAX_CELESTIAL_BODIES];
uniform float masses[MAX_CELESTIAL_BODIES];
uniform float radii[MAX_CELESTIAL_BODIES];

uniform int numCelestialBodies;
uniform float G;
uniform float pixelMass;

// Some other common functions you can c/p to write your own shader
float Force(in vec2 coord)
{
	float totalForce = 0.0;

	for (int i = 0; i < numCelestialBodies; i++)
	{
		totalForce += G * (pixelMass * masses[i]) / pow(distance(positions[i], coord), 2.0);
	}

	return totalForce;
}

int ClosestBody(in vec2 coord)
{
	float minDistance;
	int closestBody = 0;

	if (numCelestialBodies == 0)
	{
		minDistance = 0.0;
	}
	else
	{
		minDistance = distance(coord, positions[0]);
	}

	for (int i = 1; i < numCelestialBodies; i++)
	{
		float d = distance(coord, positions[i]);
		if (d < minDistance)
		{
			minDistance = d;
			closestBody = i;
		}
	}

	return closestBody;
}

float Modify(in float x)
{
	return 1.0 - exp(-x);
}