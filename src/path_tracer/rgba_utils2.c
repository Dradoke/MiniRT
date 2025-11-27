#include "minirt.h"

/// @brief Adds two RGBA colors component-wise and clamps the result
/// @param c1 First color
/// @param c2 Second color
/// @return The sum of the colors
t_rgba	ft_rgba_add(t_rgba c1, t_rgba c2)
{
	float	r;
	float	g;
	float	b;
	t_rgba	out;

	r = (c1.r / 255.0f) + (c2.r / 255.0f);
	g = (c1.g / 255.0f) + (c2.g / 255.0f);
	b = (c1.b / 255.0f) + (c2.b / 255.0f);
	out.r = (uint8_t)(fminf(r, 1.0f) * 255.0f);
	out.g = (uint8_t)(fminf(g, 1.0f) * 255.0f);
	out.b = (uint8_t)(fminf(b, 1.0f) * 255.0f);
	out.a = 255;
	return (out);
}

static int	is_normalized(float rf, float gf, float bf, float af)
{
	if (rf > 1.5f || gf > 1.5f || bf > 1.5f || af > 1.5f)
		return (0);
	return (1);
}

static uint8_t	clamp_to_byte(float value)
{
	return ((uint8_t)(fminf(fmaxf(value, 0.0f), 1.0f) * 255.0f));
}

static uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | ((uint32_t)a));
}

/// @brief Converts an RGBA structure to a packed 32-bit integer
/// @brief Handles normalization and clamping if necessary
/// @param c The RGBA color structure
/// @return The packed 32-bit integer (0xRRGGBBAA)
uint32_t	ft_rgba_to_uint(t_rgba c)
{
	float	rf;
	float	gf;
	float	bf;
	float	af;

	rf = (float)c.r;
	gf = (float)c.g;
	bf = (float)c.b;
	af = (float)c.a;
	if (is_normalized(rf, gf, bf, af))
		return (pack_rgba(clamp_to_byte(rf), clamp_to_byte(gf),
				clamp_to_byte(bf), clamp_to_byte(af)));
	return (pack_rgba((uint8_t)rf, (uint8_t)gf,
			(uint8_t)bf, (uint8_t)af));
}
