#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

typedef struct{
unsigned char r;
unsigned char g;
unsigned char b;
}pixel;

pixel* load(char *imaginein)
{
    FILE *f;
    f=fopen(imaginein,"rb");
    int i,j;
    unsigned int w,h;
    pixel* arr;

    fseek(f, 18, SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    fseek(f,54,SEEK_SET);
    int padding=(4-(w*3%4))%4;

    arr=malloc((w*h)*sizeof(pixel));


      for (i = h-1 ;  i >=0 ; i--)
        {
        for (j = 0; j < w; j++)
         {
           fread(&arr[i*w+j].b,1,1,f);
           fread(&arr[i*w+j].g,1,1,f);
           fread(&arr[i*w+j].r,1,1,f);

         }
         fseek(f,padding,SEEK_CUR);
        }
    fclose(f);
    return arr;
}

void save(char *imaginein,  char* encimage , pixel *arr)
{
    int i,j,l,header_oct;
    unsigned int w,h;
    char zero=0;

    FILE* fout ,*f;
    f=fopen(imaginein,"rb");
    fout=fopen(encimage,"wb");

    /// Copiaza header-ul primei imagini in imaginea noua
    for (i = 0; i < 54; ++i)
	{
		fread(&header_oct, 1, 1, f);
		fwrite(&header_oct, 1, 1, fout);
	}

    fseek(f, 18, SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);
    fclose(f);

    int padding=(4-(w*3%4))%4;

    for (i = h-1 ;  i >= 0; i--)
        {
        for(j = 0; j < w; j++)
        {
           fwrite(&arr[i*w+j].b,1,1,fout);
           fwrite(&arr[i*w+j].g,1,1,fout);
           fwrite(&arr[i*w+j].r,1,1,fout);
           fflush(fout);
        }
        for(l=0;l<padding;l++)
            fwrite(&zero,1,1,fout);
        }

        fclose(fout);
        free(arr);
}


#endif // BMP_H_INCLUDED
