#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

using namespace std;

void CalculatePoints(double* x, double* y, const double* a, const double* b, const double* c, const double* d);

const int SCREEN_W = 1280;
const int SCREEN_H = 1024;
const double FPS = 30;
const double SCALE = 300;

int main()
{
	ALLEGRO_DISPLAY* display = 0;
	bool quit = false;
	double x = -0.1, y = 0;

	double a = -2.966918;
	double b = 2.879879;
	double c = -0.365145;
	double d = -0.344728;

	ALLEGRO_COLOR clearColor;
	ALLEGRO_COLOR pointColor;

	// Initialze Allegro and her pluggins
	if (!al_init())
	{
		cout << "Allegro failed to initiate\n";
		system("pause");
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		cout << "Allegro primitives addon failed to initiate\n";
		system("pause");
		return -1;
	}

	if (!al_install_keyboard())
	{
		cout << "Allegro install keyboard\n";
		system("pause");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display)
	{
		cout << "Failed to initiate display \n";
		system("pause");
		return -1;
	}

	clearColor = al_map_rgb(0, 0, 0);
	pointColor = al_map_rgba(255, 255, 255, 127);

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_ALPHA);

	while (!quit)
	{
		al_clear_to_color(clearColor);

		for (int i = 0; i < 30000; ++i)
		{
			al_draw_pixel(x * SCALE + SCREEN_W / 2, y * SCALE + SCREEN_H / 2, pointColor);
			CalculatePoints(&x, &y, &a, &b, &c, &d);
		}

		al_flip_display();
	}

	return 0;
}

void CalculatePoints(double* x, double* y, const double* a, const double* b, const double* c, const double* d)
{
	// Kings
	double newx = sin((*y)*(*b)) + (*c)*sin((*x)*(*b));
	*y = sin((*x)*(*a)) + (*d)*sin((*y)*(*a));
	*x = newx;
	//	// a = -2.966918;  // Between -3.0 and 3.0
	//	// b = 2.879879;   // Between -3.0 and 3.0
	//	// c = 0.765145;   // Between -0.5 and 1
	//	// d = 0.744728;   // Between -0.5 and 1
		
	// Gingerbread man or creapy as fuck face
	//double newx = 1 - *y + abs(*x);
	//*y = *x;
	//*x = newx;

	// Duffing map
	//double newx = *y;
	//*y = -((*b)*(*x)) + ((*a)*(*y)) - pow(*y, 3);
	//*x = newx;
	//	// a = 2.75;
	//	// b = 0.15;


}