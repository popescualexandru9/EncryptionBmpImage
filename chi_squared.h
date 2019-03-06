#ifndef CHI_SQUARED_H_INCLUDED
#define CHI_SQUARED_H_INCLUDED

/// Function used to verify the values


void chi_squared(char *imaginein)
{
    unsigned int i,w,h,**canal,j;
    double fprim,chi[2],x;
    FILE *f=fopen(imaginein,"rb");

    fseek(f,18,SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    fprim=(float)(h*w)/256;
    pixel *arr;
    arr=load(imaginein);
    fclose(f);

    canal=malloc(3*sizeof(unsigned int*));
    for(i=0;i<3;i++)
        canal[i]=malloc(256*sizeof(unsigned int));

    for(i=0;i<3;i++)
    {for(j=0;j<256;j++)
         canal[i][j]=0;}

    for(i=0;i<w*h;i++)
    {
        canal[0][arr[i].b]++;
        canal[1][arr[i].g]++;
        canal[2][arr[i].r]++;
    }

  chi[0]=chi[1]=chi[2]=0;

  for(i=0;i<3;i++)
    for(j=0;j<=255;j++)
       chi[i]+=(((canal[i][j]-fprim)*(canal[i][j]-fprim))/fprim);

      printf("%.2f \n%.2f \n%.2f \n",chi[2],chi[1],chi[0]);

      free(arr);
      for(i=0;i<3;i++)
        free(canal[i]);
      free(canal);
}


#endif // CHI_SQUARED_H_INCLUDED
