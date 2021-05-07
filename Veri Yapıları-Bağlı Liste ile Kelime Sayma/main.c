#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
struct node{
char data[50];
int veri;
struct node *next;
};
struct node *ilk=NULL,*son=NULL,*gecici,*yeni;
void listele()
{
      struct node *liste=ilk;

      while(liste!=NULL)
      {
       printf("%s:%d\n",liste->data,liste->veri);
       liste=liste->next;
      }

}
void sil(char x[50])
{
      struct node *sil=ilk, *once=NULL;

      while(sil!=NULL)
      {
    if(strcmp(sil->data,x)==0)
    break;
    once=sil;
    sil=sil->next;
      }

    if(sil!=NULL)
      {
          if(sil==ilk)
          {
          ilk=ilk->next;
          }
         else if(sil==son)
         {
             son=once;
             son->next=NULL;
         }
         else{

            once->next=sil->next;
         }
         free(sil);
      }
}

void ekle(char kelime[50],int sayi) {

  sil(kelime);

    //Liste bos ise ilk ekleme kismi
    if (ilk == NULL) {
        ilk = (struct node*) malloc(sizeof (struct node));
        ilk->veri = sayi;
        strcpy(ilk->data,kelime);
        ilk->next = NULL;
    }
    else {
        //Girilen sayi ilk sayidan büyük ise basa ekle
        if ((ilk->veri) <(sayi)) {
            yeni = (struct node*) malloc(sizeof (struct node));
            yeni->veri = sayi;
            strcpy(yeni->data,kelime);
            yeni->next = ilk;
            ilk = yeni;
        } else {
            gecici = ilk;
            yeni = (struct node*) malloc(sizeof (struct node));
            yeni->veri = sayi;
            strcpy(yeni->data,kelime);
            while (gecici != NULL) {
                //gecici elemaninin sonraki null ise ve son elemandan küçükse sona ekle
                if (gecici->next == NULL && (gecici->veri) >= (sayi)) {
                    yeni->next = NULL;
                    gecici->next = yeni;
                    break;
                }
                //Araya Ekleme
                if ((gecici->next->veri) < (sayi)) {
                    yeni->next = gecici->next;
                    gecici->next = yeni;
                    break;
                }
                gecici = gecici->next;
            }
        }
    }
}

int kelimeSay(char aranacak[20])
{
    FILE *dosya;
    char kelime[50];
    dosya=fopen("veri.dat","r");
    int sayac=0;
     while(!feof(dosya))
 {
   fscanf(dosya,"%s",kelime);
   if(strcmp(aranacak,kelime)==0)
   sayac++;

 }
 return sayac;
}

int main()
{
    setlocale(LC_ALL,"Turkish");

    char aranacak[20];

    FILE *dosya;

    dosya=fopen("veri.dat","r");

     while(!feof(dosya))
    {
fscanf(dosya,"%s",aranacak);

ekle(aranacak,kelimeSay(aranacak));

    }

 listele();
 fclose(dosya);
}
