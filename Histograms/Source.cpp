#include<iostream>
#include"BmpReader.h"
using namespace std;

int main()

{
	BmpReader bmpReader("assets\\image.bmp");
	if (!bmpReader.file_opened()) {
		cout << "File does not exist" << endl;
		return -1;
	}
	bmpReader.read_pixels();
	int f;
	cout << "Press 1 to display brightness histogram" << endl;
	cout << "Press 2 to display color red histogram" << endl;
	cout << "Press 3 to display color green histogram" << endl;
	cout << "Press 4 to display color blue histogram" << endl << endl;
	cout << "Input query number (1-4): " << endl;
	cin >> f;
	system("CLS");
	if (f == 1)
	{
		bmpReader.print_brightness_histogram();
	}
	else if (f == 2)
	{
		bmpReader.print_r_histogram();
	}
	else if (f == 3)
	{
		bmpReader.print_g_histogram();
	}
	else if (f == 4)
	{
		bmpReader.print_b_histogram();
	}
	else
	{
		cout << "Invalid input";
		exit(0);
	}

	system("pause");
	return 0;
}
