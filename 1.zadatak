#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE (1024)
#define MAX_SIZE (128)

typedef struct _student{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}student;

int procitajBrojRedaka(char* imeDatoteke);
student* alocirajMemoriju(int brStudenata,char* imeDatoteke);
int ispis(int brStudenata,student* student,double max);
int maxBrBodova(int brStudenta,student*student);

int main()
{
    int brstudenata=0;
    double maxbodovi=0;
    
    student* studenti=NULL;
    
    char* datoteka="studenti.txt";
    brstudenata=procitajBrojRedaka(datoteka);
    studenti=alocirajMemoriju(brstudenata,datoteka);
    maxbodovi=studenti[maxBrBodova(brstudenata,studenti)].bodovi;
    ispis(brstudenata,studenti,maxbodovi);
    
    return 0;
}
int procitajBrojRedaka(char* imeDatoteke)
{
    int brojac=0;
    FILE* datoteka=NULL;
    char buffer[MAX_LINE]={0};

    datoteka=fopen(imeDatoteke,"r");

    if(!datoteka){
        printf("Greska otvaranja datoteke");
        return -1;
    }

    while(!feof(datoteka)){
        fgets(buffer,MAX_LINE,datoteka);
        brojac++;
    }

    fclose(datoteka);
    return brojac;
}


student* alocirajMemoriju(int brStudenata,char* imeDatoteke){
    int brojac=0;
    FILE* datoteka=NULL;
    student* studenti=NULL;

    studenti=(student*)malloc(brStudenata * sizeof( student ));
    datoteka=fopen(imeDatoteke,"r");
    if(!datoteka){
        printf("Greska alokacije");
        return NULL;
    }
    while(!feof(datoteka)){
        fscanf(datoteka," %s %s %lf",studenti[brojac].ime,studenti[brojac].prezime,&studenti[brojac].bodovi);
        brojac++;
    }

    fclose(datoteka);
    return studenti;
}

int maxBrBodova(int brStudenata,student* student){
    int i=0;
    int poz=0;
    int max=student[0].bodovi;
    for(i=0;i<brStudenata;i++)
    {
        if(max<student[i].bodovi)
        {
            max=student[i].bodovi;
            poz=i;
        }
    return poz;
    }
}
int ispis(int brStudenata,student* student,double max){
    int i;
    double rel=0;
    for(i=0;i<brStudenata;i++){
        rel=student[i].bodovi/max * 100;
        printf("Student %d Ime: %s, Prezime: %s, Apsolutni broj bodova: %.2lf, Relativni broj bodova %.2lf \n",i+1,student[i].ime,student[i].prezime,student[i].bodovi,rel);
    }
    
    return 0;
}
