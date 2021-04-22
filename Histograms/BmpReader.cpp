#include "BmpReader.h"
#pragma warning(disable:4996)

BmpReader::BmpReader(const char* path)
{
	imgFile = new ifstream(path, ios::binary);

	if (!imgFile->fail()) {
		// initialize header structures
		char * temp = new char[sizeof(BITMAPFILEHEADER)];
		imgFile->read(temp, sizeof(BITMAPFILEHEADER));
		bmpHeader = (BITMAPFILEHEADER*)(temp);

		temp = new char[sizeof(BITMAPINFOHEADER)];
		imgFile->read(temp, sizeof(BITMAPINFOHEADER));
		bmpInfoHeader = (BITMAPINFOHEADER*)(temp);

		imgFile->seekg(bmpHeader->bfOffBits, ios::beg); // bfOffBits points to the beginning of bmp 

		imgWidth = bmpInfoHeader->biWidth;
		if (imgWidth % 4)
			imgWidth += 4 - (imgWidth % 4); // 4 bit equalization

		for (int i = 0; i < 256; i++) {
			histJ[i] = 0;
			histR[i] = 0;
			histG[i] = 0;
			histB[i] = 0;
		}
	}
}

bool BmpReader::file_opened()
{
	return !imgFile->fail();
}

void BmpReader::read_pixels()
{
	Pixel* pixels_row = new Pixel[imgWidth];
	for (int i = 0; i<bmpInfoHeader->biHeight; i++)
	{
		imgFile->read((char*)pixels_row, sizeof(Pixel) * imgWidth);
		for (int j = 0; j<imgWidth; j++) {
			histR[pixels_row[j].r] ++;
			histG[pixels_row[j].g] ++;
			histB[pixels_row[j].b] ++;
			int brightness = ((pixels_row[j].r) + (pixels_row[j].g) + (pixels_row[j].b)) / 3;
			histJ[brightness]++;
		}
	}
	delete[] pixels_row;
}

void BmpReader::print_brightness_histogram()
{
	char output_buffer[64][32];
	FILE *pf;
	pf = fopen("results.txt", "w");
	if (pf == NULL) {
		cout << "File cannot be opened" << endl;
		exit(0);
	}
	else
	{
		int max = -1;
		cout << "Histogram table:" << endl << endl;
		fprintf(pf, "Histogram table: \n");
		for (int i = 0; i < 256; i++) {
			if (histJ[i] > max) {
				max = histJ[i];
			}
			cout << histJ[i] << " ";
			fprintf(pf, "%d ", histJ[i]);
		}
		cout << endl << endl << "Histogram graph:" << endl;
		for (int column = 0; column < 64; column++) {
			//calculate avg
			float avg = 0;
			for (int i = 0; i < 4; i++) {
				avg += histJ[column * 4 + i];
			}
			avg /= 2;
			avg *= (32. / max);

			int row = 31;
			while (avg > 0) {
				output_buffer[column][row] = '*';
				avg -= 1;
				row -= 1;
			}
		}
		fprintf(pf, "\n Histogram graph: \n");
		for (int row = 0; row < 32; row++) {
			for (int column = 0; column < 64; column++) {
				if (output_buffer[column][row] == '*') {
					cout << '*';
					fprintf(pf, "%c", '*');
				}
				else
					cout << ' ';
				fprintf(pf, "%s", "");
			}
			cout << endl;
			fprintf(pf, "\n", "");
		}
		cout << "0 " << setw(64) << "255";
	}
	fclose(pf);
}

void BmpReader::print_r_histogram()
{
	char output_buffer[64][32];
	FILE *pf;
	pf = fopen("results.txt", "w");
	if (pf == NULL) {
		cout << "File cannot be opened" << endl;
		exit(0);
	}
	else
	{
		int max = -1;
		cout << "Histogram table:" << endl << endl;
		fprintf(pf, "Histogram table: \n");
		for (int i = 0; i < 256; i++) {
			if (histR[i] > max) {
				max = histR[i];
			}
			cout << histR[i] << " ";
			fprintf(pf, "%d ", histR[i]);
		}
		cout << endl << endl << "Histogram graph:" << endl;
		for (int column = 0; column < 64; column++) {
			//calculate avg
			float avg = 0;
			for (int i = 0; i < 4; i++) {
				avg += histR[column * 4 + i];
			}
			avg /= 2;
			avg *= (32. / max);

			int row = 31;
			while (avg > 0) {
				output_buffer[column][row] = '*';
				avg -= 1;
				row -= 1;
			}
		}
		fprintf(pf, "\n Histogram graph: \n");
		for (int row = 0; row < 32; row++) {
			for (int column = 0; column < 64; column++) {
				if (output_buffer[column][row] == '*') {
					cout << '*';
					fprintf(pf, "%c", '*');
				}
				else
					cout << ' ';
				fprintf(pf, "%s", "");
			}
			cout << endl;
			fprintf(pf, "\n", "");
		}
		cout << "0 " << setw(64) << "255";
	}
	fclose(pf);
}

void BmpReader::print_g_histogram()
{
	char output_buffer[64][32];
	FILE *pf;
	pf = fopen("results.txt", "w");
	if (pf == NULL) {
		cout << "File cannot be opened" << endl;
		exit(0);
	}
	else
	{
		int max = -1;
		cout << "Histogram table:" << endl << endl;
		fprintf(pf, "Histogram table: \n");
		for (int i = 0; i < 256; i++) {
			if (histG[i] > max) {
				max = histG[i];
			}
			cout << histG[i] << " ";
			fprintf(pf, "%d ", histG[i]);
		}
		cout << endl << endl << "Histogram graph:" << endl;
		for (int column = 0; column < 64; column++) {
			//calculate avg
			float avg = 0;
			for (int i = 0; i < 4; i++) {
				avg += histG[column * 4 + i];
			}
			avg /= 2;
			avg *= (32. / max);

			int row = 31;
			while (avg > 0) {
				output_buffer[column][row] = '*';
				avg -= 1;
				row -= 1;
			}
		}
		fprintf(pf, "\n Histogram graph: \n");
		for (int row = 0; row < 32; row++) {
			for (int column = 0; column < 64; column++) {
				if (output_buffer[column][row] == '*') {
					cout << '*';
					fprintf(pf, "%c", '*');
				}
				else
					cout << ' ';
				fprintf(pf, "%s", "");
			}
			cout << endl;
			fprintf(pf, "\n", "");
		}
		cout << "0 " << setw(64) << "255";
	}
	fclose(pf);
}

void BmpReader::print_b_histogram()
{
	char output_buffer[64][32];
	FILE *pf;
	pf = fopen("results.txt", "w");
	if (pf == NULL) {
		cout << "File cannot be opened" << endl;
		exit(0);
	}
	else
	{
		int max = -1;
		cout << "Histogram table:" << endl << endl;
		fprintf(pf, "Histogram table: \n");
		for (int i = 0; i < 256; i++) {
			if (histB[i] > max) {
				max = histB[i];
			}
			cout << histB[i] << " ";
			fprintf(pf, "%d ", histB[i]);
		}
		cout << endl << endl << "Histogram graph:" << endl;
		for (int column = 0; column < 64; column++) {
			//calculate avg
			float avg = 0;
			for (int i = 0; i < 4; i++) {
				avg += histB[column * 4 + i];
			}
			avg /= 2;
			avg *= (32. / max);

			int row = 31;
			while (avg > 0) {
				output_buffer[column][row] = '*';
				avg -= 1;
				row -= 1;
			}
		}
		fprintf(pf, "\n Histogram graph: \n");
		for (int row = 0; row < 32; row++) {
			for (int column = 0; column < 64; column++) {
				if (output_buffer[column][row] == '*') {
					cout << '*';
					fprintf(pf, "%c", '*');
				}
				else
					cout << ' ';
				fprintf(pf, "%s", "");
			}
			cout << endl;
			fprintf(pf, "\n", "");
		}
		cout << "0 " << setw(64) << "255";
	}
	fclose(pf);
}

BmpReader::~BmpReader()
{
	this->imgFile->close();
	delete this->imgFile;
	delete[] bmpHeader;
	delete[] bmpInfoHeader;
}