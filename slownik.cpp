//UWAGA: na koncu kazdego ostatniego slowa w pliku slownik.txt musi byc enter(bez zadnych spacji itp)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char data;
    struct Node *next;
};
struct Node *start=NULL;
struct Node *second=NULL;
void create_new_cell_start(char znak)//dla podanego znaku dodaje go na koniec listy start
{
    struct Node *temp,*helper;
    temp=(struct Node *)malloc(sizeof(struct Node));

    temp->data=znak;
    temp->next=NULL;

    if(start==NULL)start=temp;
    else
    {
        helper=start;
        while(helper->next!=NULL)helper=helper->next;
        helper->next=temp;
    }
}
void create_new_cell_second(char znak)//dla podanego znaku dodaje go na koniec listy second
{

    struct Node *temp,*helper;
    temp=(struct Node *)malloc(sizeof(struct Node));

    temp->data=znak;
    temp->next=NULL;

    if(second==NULL)second=temp;
    else
    {
        helper=second;
        while(helper->next!=NULL)helper=helper->next;
        helper->next=temp;
    }
}
void display_start()//wyświetla wszystkie elementy listy start
{
    struct Node *helper;
    if(start==NULL)
    {
        printf("Lista jest pusta:\n");
        return;
    }
    else
    {
        helper=start;
        while(helper!=NULL)
        {
            printf("%c",helper->data );
            helper=helper->next ;
        }
    }
}
void display_second()//wyświetla wszystkie elementy listy second
{
    struct Node *helper;
    if(second==NULL)
    {
        printf("Lista jest pusta:\n");
        return;
    }
    else
    {
        helper=second;
        while(helper!=NULL)
        {
            printf("%c",helper->data );
            helper=helper->next ;
        }
    }
}
void display_start_without_numbers()//wyświetla elementy listy start bez liczby
{
    struct Node *helper;
    FILE *plik;
    plik = fopen("a.txt","w");
    int x=0;
    if(start==NULL)
    {
        printf("Lista jest pusta:\n");
        return;
    }
    else
    {
        helper=start;
        while(helper!=NULL)
        {
            if((helper->data)==' ')x++;
            if(x!=1)
            {
            fprintf(plik,"%c",helper->data );
            printf("%c",helper->data );
            }
            if((helper->data)=='\n')x=0;
            helper=helper->next ;
        }
    }
  fclose(plik);
}
void move_from_txt_to_list_start()//przenosi zawartość pliku tekstowego slownik.txt do listy start
{
    char znak='0';
    int i=0;
    char linia[200];
    FILE *plik;
    plik = fopen("slownik.txt","r");
    while(!feof(plik))
    {
        fgets(linia,200,plik);
        while(znak!='\n')
        {
            if(znak=feof(plik))break;
            znak=linia[i];
            i++;
            create_new_cell_start(znak);
        }
        i=0;
        znak='0';
    }
    fclose(plik);
}
void move_from_txt_to_list_second()//przenosi zawartość pliku tekstowego juz_bylo.txt do listy second
{
    char znak='0';
    int i=0;
    char linia[200];
    FILE *plik;
    plik = fopen("juz_bylo.txt","r");
    while(!feof(plik))
    {
        fgets(linia,200,plik);
        while(znak!='\n')
        {
            if(znak=feof(plik))break;
            znak=linia[i];
            i++;
            create_new_cell_second(znak);
        }
        i=0;
        znak='0';
    }
    fclose(plik);
}
void find_english_word()//dla podanego słowa angielskiego wypisze jego odpowiedniki w polskim
{
    char word[40],list_word[40];
    int j=0,i=0,check=0,comparison=0,there_is_word=0;

    struct Node *helper;

    helper=start;

    FILE *plik;
    plik = fopen("b.txt","w");

    printf("Podaj anglieskie slowo: ");
    scanf("%s",&word);

    while(helper!=NULL)
    {
        if(helper->data==' ')check++;
        if (check==0) //wstawia znaki do tablicy "list_word" do pierwszej spacji
        {
            list_word[i]=helper->data;
            i++;
        }
        if(check>0) //To się dzieje po 1szej spacj, sprawdza czy slowo podane przez urzytkownika znajduje sie w słowniku
        {
            i=0;
            check=0;
            for(j=0; j<strlen(word); j++)if (word[j]!=list_word[j])comparison=1;

            if (comparison==0)there_is_word=1;

            if(there_is_word==1)
            {
                helper=helper->next;
                while(helper->data!=' ')helper=helper->next;
                helper=helper->next;
                while (helper->data!='\n')
                {
                    printf("%c",helper->data);
                    fprintf(plik,"%c",helper->data );
                    helper=helper->next;
                }
                break;
            }
            while (helper->data!='\n')helper=helper->next;
        }
        comparison = 0;
        helper=helper->next;
    }
    if(there_is_word==0)
    {
    fprintf(plik,"%c",helper->data );
    printf("Nie ma takiego slowa w slowniku");
    }
    printf("\n");
    fclose(plik);
}
void find_polish_word()//dla podanego słowa polskiego wypisze jego odpowiedniki w angieskim
{
    char user_word[40],eng_word[40];
    int q=0,j=0,i=0,len_user_word=0,comparison=0,boop=0;

    struct Node *helper;

    helper=start;

    FILE *plik;
    plik = fopen("c.txt","w");

    printf("Podaj polskie slowo: ");
    scanf("%s",&user_word);

    len_user_word=strlen(user_word);

    while(helper!=NULL)
    {
            while(helper->data!=' ')// zapisuje angielskie slowo do eng_word
            {
                eng_word[i]=helper->data;
                helper=helper->next;
                i++;
            }
            //pominiecie liczby
            helper=helper->next;
            while(helper->data!=' ')helper=helper->next;
            helper=helper->next;

            while(helper->data!='\n')
            {
                if(helper->data==' ')//jezeli dojdzie do spacji porownuje poruwnuje z soba slowa powtarza sie do znaleziania znaku konca lini
                {
                    if(comparison==len_user_word)
                    {
                        for(q=0; q<i; q++)
                        {
                          fprintf(plik,"%c",eng_word[q]);
                          printf("%c",eng_word[q]);
                      }
                        boop++;
                        printf("\n");
                    }
                    j=0;
                    comparison=0;
                    helper=helper->next;
                }
                if(helper->data==user_word[j])comparison++;
                j++;
                helper=helper->next;
            }
            if(comparison==len_user_word)// porownuje poruwnuje z soba ostanie slowo w wierszu
            {
                for(q=0; q<i; q++)
                {
                  printf("%c",eng_word[q]);
                  fprintf(plik,"%c",eng_word[q]);
              }
                boop++;
                printf("\n");
            }
            comparison=0;
            helper=helper->next;
            j=0;
            i=0;
    }
    if(boop==0)// nie znalazlo zadnego podobnego slowa
    {
      fprintf(plik,"%c",eng_word[q]);
    printf("Nie ma takiego slowa w slowniku.\n" );
  }
  fclose(plik);
}
int maximum()//zwraca długosc najdluzszego wyrazu+1 z pliku tekstowego slownik.txt
{
    struct Node *helper;
    helper=start;
    int i=0,max=0;
    while(helper!=NULL)
    {
      //przejsicie do polskich wyrazów
        while(helper->data!=' ')helper=helper->next;
        helper=helper->next;
        while(helper->data!=' ')helper=helper->next;
        helper=helper->next;
        while(helper->data!='\n')
        {
            while(helper->data!=' ')
            {
                if(helper->data=='\n')break;
                helper=helper->next;
                i++;
            }
            if (i>max)max=i;
            i=0;
            if(helper->data!='\n')helper=helper->next;
        }
        helper=helper->next;
    }
    return max+1;
}
void raport()//wypisuje słowa ze słownika w kolejosci od najkrótszego do najdluzeszgo
{
    int max=0,i=0,j=0,q=0,len_word=0;
    char word[30];

    struct Node *helper;
    helper=start;

    FILE *plik;
    plik = fopen("d.txt","w");

    max=maximum();

    for(i=2; i<max; i++)
    {
        while(helper!=NULL)
        {
            while(helper->data!=' ')helper=helper->next;
            helper=helper->next;
            while(helper->data!=' ')helper=helper->next;
            helper=helper->next;
            while(helper->data!='\n')
            {
                while(helper->data!=' ')
                {
                    if(helper->data=='\n')break;
                    word[len_word]=helper->data;
                    len_word++;
                    helper=helper->next;
                }
                if (len_word==i)
                {
                    for(q=0; q<len_word; q++)
                    {
                    printf("%c",word[q]);
                    fprintf(plik,"%c",word[q]);
                  }
                  fprintf(plik,"\n");
                    printf("\n");
                }
                len_word=0;
                if(helper->data!='\n')helper=helper->next;
            }
            helper=helper->next;
        }
        helper=start;
    }
fclose(plik);
}
void display_with_no_repetitions()
{
    FILE *plik,*plik2,*plik3;
    plik3 = fopen("e.txt","w");

    struct Node *helper;
    helper=start;

    struct Node *dodatek;

    char word[30],znak='0',linia[150];

    int len_word=0,q,i=0,comparison=0,boop=1,test=0,j=0;

    plik = fopen("juz_bylo.txt","w");

    fclose(plik);

    while(helper!=NULL)
    {
        while(helper->data!=' ')helper=helper->next;
        helper=helper->next;
        while(helper->data!=' ')helper=helper->next;
        helper=helper->next;

        while(helper->data!='\n')
        {
            while(helper->data!=' ')
            {
                if(helper->data=='\n')break;
                word[len_word]=helper->data;
                len_word++;
                helper=helper->next;
            }
            if(second==NULL)
            {
              for(q=0; q<len_word; q++)
              {
                printf("%c",word[q]);
                fprintf(plik3,"%c",word[q]);
              }
              printf("\n");
              fprintf(plik3,"\n");
            }
            else
            {
              dodatek=second;
                while(dodatek!=NULL)
                {
                    while(dodatek->data!='\n')
                    {
                        if(dodatek==NULL)break;
                        if(word[j]==dodatek->data)comparison++;
                        dodatek=dodatek->next ;
                        j++;
                    }
                    j=0;
                    if(comparison==len_word)boop=0;
                    comparison=0;
                    dodatek=dodatek->next ;
                }
                if(boop==1)
                {
                  for(q=0; q<len_word; q++)
                  {
                    printf("%c",word[q]);
                    fprintf(plik3,"%c",word[q]);
                  }
                  fprintf(plik3,"\n");
                    printf("\n");
                }
                boop=1;
            }
            plik = fopen("juz_bylo.txt","a");
            second=NULL;
            for(q=0; q<len_word; q++)fprintf(plik,"%c",word[q]);
            fprintf(plik,"\n");
            fclose(plik);
            move_from_txt_to_list_second();
            len_word=0;
            if(helper->data!='\n')helper=helper->next;
        }
        helper=helper->next;
    }
    fclose(plik3);
}

int main()
{
  move_from_txt_to_list_start();
  int number,x;
  printf("Tryb Renczny - nieskonczona pentla ktora wykonuje konkretne polecenie podane od urzytkownika\nWykonaie Polecen - wynonianie wszystkich polecen po koleji i zakoncznie programu\n");
  printf("0 - Wyjscie\n1 - Tryb Renczny\n2 - Wykonaie Polecen\n");
  printf("Podaj numer czynnosci ktora chesz wykonac: ");
  scanf("%d",&x);
  switch(x)
  {
  case 0:
    break;
     case 1:
         printf("-----------------------------------------------------------------\n");
  printf("|0 - wyjsice z porgramu \n|1 - wyswietlenie slownika bez liczb\n|2 - szukanie tlumaczenia angielskiego slowa\n|3 - szukanie tlumaczena polskiego slowa:\n|4 - wypisanie polskich slow rosnaco wzgledem dlugosci slowa\n|5 - wypisanie polskich slow bez powtorzen\n");
  printf("-----------------------------------------------------------------\n");
  printf("Podaj numer czynnosci ktora chesz wykonac: ");
  scanf("%d",&number);
  while (number!=0)
  {
      switch (number)
      {
      case 1:
          display_start_without_numbers();
          break;
      case 2:
          find_english_word();
          break;
      case 3:
          find_polish_word();
          break;
      case 4:
        raport();
        break;
      case 5:
      display_with_no_repetitions();
      break;
      default:
          printf("Podaj inna wartosc: \n");
          break;
      }
      printf("-----------------------------------------------------------------\n");
      printf("|0 - wyjsice z porgramu \n|1 - wyswietlenie slownika bez liczb\n|2 - szukanie tlumaczenia angielskiego slowa\n|3 - szukanie tlumaczena polskiego slowa:\n|4 - wypisanie polskich slow rosnaco wzgledem dlugosci slowa\n|5 - wypisanie polskich slow bez powtorzen\n");
      printf("-----------------------------------------------------------------\n");
      printf("Podaj numer czynnosci ktora chesz wykonac: ");
      scanf("%d",&number);
  }
    break;
     case 2:

         printf("Podpunkt a)\n\n");
    display_start_without_numbers();
    printf("\n");
    printf("Podpunkt b)\n\n");
    find_english_word();
    printf("\n");
    printf("Podpunkt c)\n\n");
    find_polish_word();
    printf("\n");
    printf("Podpunkt d)\n\n");
    raport();
    printf("\n");
    printf("Podpunkt e)\n\n");
    display_with_no_repetitions();
    break;
    default:
          printf("Podaj inna wartosc: \n");
          break;
  }

    return 0;
}
