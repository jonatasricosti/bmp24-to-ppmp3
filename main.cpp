#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main()
{
    cout << "Conversor de imagem bmp24 para ppm p3" << endl;
    cout << "Digite o nome do arquivo bmp: ";
    string filename;
    getline(cin,filename);
    
	FILE *file = fopen(filename.c_str(), "rb");
    if(!file)
        return 0;
	
	ofstream escreva;
    escreva.open("arquivo.ppm");
    int blue,green,red;
	int width, height, padding, bitcount, size;
    unsigned char *data = 0;
    unsigned char info[54] = {0};

    fread(info, 1, 54, file);
    width = *(int*)(info + 18);
    height = *(int*)(info + 22);
    
    escreva << "P3" << endl;
    escreva << width << endl;
    escreva << height << endl;
    escreva << 255 << endl;
    
    bitcount = *(int*)(info + 28);
    size = ((width * bitcount + 31) / 32) * 4 * height;
    padding = width % 4;
    if(bitcount != 24) // este código funciona apenas para bitmap de 24 bits
    {
    	cout << "não é um bmp valido" << endl;
	}

    data = (unsigned char *)malloc(size);
    fread(data, 1, size, file);
    for(int row = height - 1; row >= 0; row--)
    {
        for(int col = 0; col < width; col++)
        {
            int p = (row * width + col) * 3 + row * padding;
            blue = (int)data[p + 0];
            green = (int)data[p + 1];
            red  = (int)data[p + 2];
            escreva << red << " " << green << " " << blue << endl;
            
        }
        
        printf("\n");
    }
	fclose(file);
    free(data);
    escreva.close();
    cout << "terminado" << endl;
    system("pause");
    return 0;
}
