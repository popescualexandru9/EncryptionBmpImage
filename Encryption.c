#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bmp.h"
#include "encrypt.h"
#include "decrypt.h"
#include "chi_squared.h"

int main()
{
    char initial_image[101], encrypted_image[101], secret_key[20],option[2];

    /// Encryption.
/*
    printf("The name of the image which needs to be encrypted : ");
    fgets(initial_image, 101, stdin);
    initial_image[strlen(initial_image) - 1] = '\0';
    FILE *a = fopen(initial_image, "rb");
    if(a == NULL)
    {
        printf("\nDid not find the image (%s)!\n", initial_image);
        return 0;
    }
    printf("\n");

    printf("The name of the resulted image: ");
    fgets(encrypted_image, 101, stdin);
    encrypted_image[strlen(encrypted_image) - 1] = '\0';
    printf("\n");

    printf("The name of the secret key: ");
    fgets(secret_key, 101, stdin);
    secret_key[strlen(secret_key) - 1] = '\0';
    FILE *b = fopen(secret_key, "rb");
    if(b == NULL)
    {
        printf("\Did not find the image (%s)!\n", secret_key);
        return 0;
    }
    encryption(initial_image,encrypted_image,secret_key);
*/
    /// Decryption
/*
    printf("The name of the encrypted image: ");
    fgets(initial_image, 101, stdin);
    initial_image[strlen(initial_image) - 1] = '\0';
    FILE *c = fopen(initial_image, "rb");
    if(c == NULL)
    {
        printf("\nDid not find the image (%s)!\n", initial_image);
        return 0;
    }
    printf("\n");

    printf("The name of the resulted image: ");
    fgets(encrypted_image, 101, stdin);
    encrypted_image[strlen(encrypted_image) - 1] = '\0';
    printf("\n");

    printf("The name of the secret key: ");
    fgets(secret_key, 101, stdin);
    secret_key[strlen(secret_key) - 1] = '\0';
    FILE *b = fopen(secret_key, "rb");
    if(b == NULL)
    {
        printf("\nDid not find the image (%s)!\n", secret_key);
        return 0;
    }
    decryption(initial_image,encrypted_image,secret_key);
*/
    /// Chi squared value
/*
    printf("The name of the image which needs to be tested: ");
    fgets(initial_image, 101, stdin);
    initial_image[strlen(initial_image) - 1] = '\0';
    FILE *d = fopen(initial_image, "rb");
    if(d == NULL)
    {
        printf("\nDid not find the image (%s)!\n", initial_image);
        return 0;
    }
    printf("\n");

    printf("The name of the encrypted image which needs to be tested: ");
    fgets(initial_image, 101, stdin);
    initial_image[strlen(initial_image) - 1] = '\0';
    FILE *e= fopen(initial_image, "rb");
    if(e == NULL)
    {
        printf("\nDid not find the image (%s)!\n", initial_image);
        return 0;
    }

    printf("\nInitial image :\n");
    chi_squared(initial_image);
    printf("\nEncrypted image :\n");
    chi_squared(initial_image);

*/
return 0;
}
