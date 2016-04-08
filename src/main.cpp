#include <cstdio>
#include <Windows.h>
#include <vector>
#include "Vec3.h"
#include "Sphere.h"
#include "Plane.h"
#include "Object.h"
#include "Light.h"
#include "RayTracer.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void initializeScene();

std::vector<Object *> objects;
std::vector<Light> lights;

int main() {

	initializeScene();

	HWND hMainWnd;
	TCHAR szClassName[] = "RayTracer";
	MSG msg;
	WNDCLASSEX wc;

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}

	hMainWnd = CreateWindow(
		szClassName, "RayTracer", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1000, 1000,
		(HWND)NULL, (HMENU)NULL,
		(HINSTANCE)NULL, NULL
		);

	if (!hMainWnd) {
		MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
		return 0;
	}


	ShowWindow(hMainWnd, SHOW_OPENWINDOW);
	UpdateWindow(hMainWnd);

	while (GetMessage(&msg, NULL, 0, 0))  {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	int width, height;
	double x, y;
	Vec3 eye(0.5, 0.5, 0);

	switch (msg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		width = rect.right - 1;
		height = rect.bottom - 1;



		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				x = ((double)j + 0.5) / (double)width;
				y = ((double)(height - i) - 0.5) / (double)height;
				Vec3 color = 
					rayTrace(eye, (Vec3(x, y, 1) - eye).normalize(), objects, lights, 15);
				SetPixel(hDC, j, i, vectorToColor(color));
			}
		}

		EndPaint(hWnd, &ps);
		return 0;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}


void initializeScene() {
	// add objects
	// tranparent spheres
	objects.push_back(new Sphere(Vec3(0.75, 1, 2), 0.3, Vec3(0.1, 0.1, 0.1), 15, NOT_REFLECTIVE, 0.97));
	objects.push_back(new Sphere(Vec3(0.7, -0.5, 4.3), 0.5, Vec3(0.2, 0.2, 0.2), 15, NOT_REFLECTIVE, 0.5));

	// red sphere
	objects.push_back(new Sphere(Vec3(-0.5, 0, 7), 1, Vec3(1, 0, 0), 20, 0.5, NOT_REFRACTIVE));
	// green sphere
	objects.push_back(new Sphere(Vec3(1.5, 0, 7), 1, Vec3(0, 1, 0), 6, 0.5, NOT_REFRACTIVE));
	// blue sphere
	objects.push_back(new Sphere(Vec3(0.5, 1.75, 4), 0.5, Vec3(0, 0, 1), 15, NOT_REFLECTIVE, 0.15));
	// checkerboard
	objects.push_back(new Plane(Vec3(0.5, -1, 10), Vec3(0, 1, 0), 10, 0.5));
	//objects.push_back(new Plane(Vec3(0.5, 0.5, 10), Vec3(0, 0, -1), 10, 0.5));
	// lights
	lights.push_back(Light(Vec3(2, 3, 0), 0.5));
	lights.push_back(Light(Vec3(-5, 4, 2), 0.5));
	// lights.push_back(Light(Vec3(0.5,4, 2), 0.5));
}