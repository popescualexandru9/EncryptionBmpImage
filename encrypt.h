#ifndef ENCRYPT_H_INCLUDED
#define ENCRYPT_H_INCLUDED

union crypt_help{
    unsigned int x;
    char v[3] ;
};

unsigned int xorshift32(unsigned int n)  // Xorshift32
{
    unsigned int x = n;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

void swap(int *a ,int *b)  // Functie de interschimbare elemente
{
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}


void encryption(char *imaginein , char* encimage , char* secret)
{
    unsigned int *ran,i,key,*perm,w,h,poz,l,j,sv;
    FILE *f=fopen(imaginein,"rb");
    FILE *fxt=fopen(secret,"r");
    fscanf(fxt,"%u",&key);
    fscanf(fxt,"%u",&sv);

    fseek(f,18,SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    pixel* arr ,*arr_permutat, *ci;  /// Ci = cipherd image
    arr=load(imaginein);
    arr_permutat=malloc((w*h)*sizeof(pixel));
    ci=malloc((w*h)*sizeof(pixel));

    fclose(f);
    fclose(fxt);

    /// Sequence of random numbers
    ran=malloc(2*(h*w)*sizeof(unsigned int));
    ran[0]=key;
    for(i=1;i<=2*(h*w)-1;i++)
        ran[i]=xorshift32(ran[i-1]);

    /// Dusternfeld's permutation
    perm=malloc((h*w)*sizeof(unsigned int));
    for(i=0;i<w*h;i++)
       perm[i]=i;
    l=1;
    for(i=(w*h)-1;i>0;i--)
       {
        poz=ran[l]%(i+1);
        swap(&perm[i],&perm[poz]);
        l++;
       }

    for (i = 0 ;  i < w*h ; i++)
       {
        arr_permutat[perm[i]].b=arr[i].b;
        arr_permutat[perm[i]].g=arr[i].g;
        arr_permutat[perm[i]].r=arr[i].r;
       }

    union crypt_help a,b,c;
    a.x=sv;
    b.x=ran[w*h];
    ci[0].b=a.v[0]^arr_permutat[0].b^b.v[0];
    ci[0].g=a.v[1]^arr_permutat[0].g^b.v[1];
    ci[0].r=a.v[2]^arr_permutat[0].r^b.v[2];
    for(i=1;i<w*h;i++)
      {
          c.x=ran[w*h+i];
          ci[i].b=ci[i-1].b^arr_permutat[i].b^c.v[0];
          ci[i].g=ci[i-1].g^arr_permutat[i].g^c.v[1];
          ci[i].r=ci[i-1].r^arr_permutat[i].r^c.v[2];
      }



    save(imaginein,encimage,ci);
    free(ci);
    free(arr);
    free(arr_permutat);
    free(ran);
    free(perm);

}

#endif // ENCRYPT_H_INCLUDED
