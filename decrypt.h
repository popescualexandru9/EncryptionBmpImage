#ifndef DECRYPT_H_INCLUDED
#define DECRYPT_H_INCLUDED

void decryption(char *imaginein , char* encimage , char* secret)
{
    unsigned int *random,i,key,*perm,w,h,poz,l,j,sv,*perminv;
    FILE *f=fopen(imaginein,"rb");
    FILE *fxt=fopen(secret,"r");
    fscanf(fxt,"%u",&key);
    fscanf(fxt,"%u",&sv);

    fseek(f,18,SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    /// Ci = cipherd image / Di = decipherd image
    pixel *ci ,*ci_permutat,*di;
    ci=load(imaginein);
    ci_permutat=malloc((w*h)*sizeof(pixel));
    di=malloc((w*h)*sizeof(pixel));

    fclose(f);
    fclose(fxt);


    /// Sequence of random numgbers
    random=malloc(2*(h*w)*sizeof(unsigned int));
    random[0]=key;
    for(i=1;i<=2*(h*w)-1;i++)
        random[i]=xorshift32(random[i-1]);

    /// Dusternfeld's permutation
    perm=malloc((h*w)*sizeof(unsigned int));
    for(i=0;i<w*h;i++)
       perm[i]=i;
    l=1;
    for(i=(w*h)-1;i>0;i--)
       {
        poz=random[l]%(i+1);
        swap(&perm[i],&perm[poz]);
        l++;
       }


    /// Dusternfeld's reversed permutation
    perminv=malloc((h*w)*sizeof(unsigned int));
    for(i=0;i<w*h;i++)
        perminv[perm[i]]=i;

    union crypt_help a,b,c;
    a.x=sv;
    b.x=random[w*h];
    ci_permutat[0].b=a.v[0]^ci[0].b^b.v[0];
    ci_permutat[0].g=a.v[1]^ci[0].g^b.v[1];
    ci_permutat[0].r=a.v[2]^ci[0].r^b.v[2];
    for(i=1;i<w*h;i++)
      {
          c.x=random[w*h+i];
          ci_permutat[i].b=ci[i-1].b^ci[i].b^c.v[0];
          ci_permutat[i].g=ci[i-1].g^ci[i].g^c.v[1];
          ci_permutat[i].r=ci[i-1].r^ci[i].r^c.v[2];
      }

   for(i=0;i<w*h;i++)
     {
     di[perminv[i]].b=ci_permutat[i].b;
     di[perminv[i]].g=ci_permutat[i].g;
     di[perminv[i]].r=ci_permutat[i].r;
     }

    save(imaginein,encimage,di);
    free(ci);
    free(di);
    free(ci_permutat);
    free(random);
    free(perm);
    free(perminv);
}

#endif // DECRYPT_H_INCLUDED
