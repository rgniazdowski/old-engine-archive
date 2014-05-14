/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_PARTICLE_H_
#define _FG_PARTICLE_H_

#include "../../Math/fgMathLib.h"
#include "../fgGFXTypes.h"

struct Particle
{
	// Aktualna pozycja
	Vector3f position;	
	// Predkosc (o ile czasteczka ma sie przesunac w ciagu jednej sekundy)
	Vector3f velocity;
	// Aktualny obrot w 3 osiach, podany w stopniach
	Vector3f rotation;
	// Predkosc katowa rowniez podana w stopniach (o ile stopni czasteczka ma sie obrocic w ciagu jednej sekundy)
	Vector3f angularVelocity;
	// Zakladamy ze kazdy particle jest kwadratowy wiec potrzebna jest tylko jedna zmienna do przechowania rozmiaru
	float size;
	// Zycie danej czasteczki (gdy <=0 czasteczka jest usuwana)
	float life;
	// Predkosc zamierania danej czasteczki
	float fade_speed;
	// Time to live (milisekundy), ustawianie wartosci TTL zmienia wartosc life i fade_speed - ustawiac przez funkcje setTTL
	int ttl;
	// Czas stworzenia danej czasteczki
	unsigned long int spawn_time;
	// ID textury z tablicy tekstur
	int texture_id;
	// Kolor zapisany za pomoca float dla wiekszej precyzji przy przejsciach
	fgColor color;
	// Wskaznik do dodatkowych danych
	void *data;

	Particle() : position(0.0f,0.0f,0.0f), velocity(0.0f,0.0f,0.0f), rotation(0.0f,0.0f,0.0f), angularVelocity(0.0f,0.0f,0.0f), size(0.0f), life(0.0f), fade_speed(0.0f), ttl(0), spawn_time(0), texture_id(0), data(NULL)
    {
    
	}

	void setColor(fgColor inColor)
	{
		color = inColor;
	}

	void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		color.r = (float)r/255.0f;
		color.g = (float)g/255.0f;
		color.b = (float)b/255.0f;
		color.a = (float)a/255.0f;
	}

	void setColor(float r, float g, float b, float a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setTTL(int ttl_value)
	{
		ttl = ttl_value;
		life = 1000.0f;
		fade_speed = life/ttl_value*1000.0f;
	}

	void setLife(float life_value, float fade_speed_value)
	{
		life = life_value;
		fade_speed = fade_speed_value;
		ttl = life/fade_speed;
	}
};

#endif
