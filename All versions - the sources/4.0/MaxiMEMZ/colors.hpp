#pragma once
#include "maximemz.hpp"

typedef struct {
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

HSL RGBQUADtoHSL(RGBQUAD rgb) {
	FLOAT r = rgb.rgbRed / 255.0f;
	FLOAT g = rgb.rgbGreen / 255.0f;
	FLOAT b = rgb.rgbBlue / 255.0f;

	FLOAT max = fmaxf(fmaxf(r, g), b);
	FLOAT min = fminf(fminf(r, g), b);

	FLOAT h, s, l = (max + min) / 2.0f;

	if (max == min) {
		h = s = 0.0f;
	}

	else {
		FLOAT d = max - min;
		s = l > 0.5f ? d / (2.0f - max - min) : d / (max + min);

		if (max == r) {
			h = (g - b) / d + (g < b ? 6.0f : 0.0f);
		}

		else if (max == g) {
			h = (b - r) / d + 2.0f;
		}

		else {
			h = (r - g) / d + 4.0f;
		}

		h *= 60.0f;
	}

	HSL result = { h, s, l };
	return result;
}

RGBQUAD HSLtoRGBQUAD(HSL hsl) {
	FLOAT c = (1.0f - fabsf(2.0f * hsl.l - 1.0f)) * hsl.s;
	FLOAT x = c * (1.0f - fabsf(fmodf(hsl.h / 60.0f, 2.0f) - 1.0f));
	FLOAT m = hsl.l - c / 2.0f;

	FLOAT r, g, b;
	if (hsl.h < 60) { r = c; g = x; b = 0; }

	else if (hsl.h < 120) { r = x; g = c; b = 0; }
	else if (hsl.h < 180) { r = 0; g = c; b = x; }

	else if (hsl.h < 240) { r = 0; g = x; b = c; }
	else if (hsl.h < 300) { r = x; g = 0; b = c; }
	else { r = c; g = 0; b = x; }

	RGBQUAD rgb;

	rgb.rgbRed = (BYTE)((r + m) * 255.0f);
	rgb.rgbGreen = (BYTE)((g + m) * 255.0f);

	rgb.rgbBlue = (BYTE)((b + m) * 255.0f);
	rgb.rgbReserved = 0;
	return rgb;
}