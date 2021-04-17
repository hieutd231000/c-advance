#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTREE/inc/btree.h"

int chuanhoa(char *s){
  for(int i=0;i<strlen(s);i++){
    if(s[i]>=65&&s[i]<=90)s[i]+=32;
    if(s[i]<97||s[i]>122)s[i]=' ';
  }
    char s1[100];
    memset(s1,0,100);
    int i=0;
    for(i=0;i<strlen(s);i++)if(s[i]!=' ')break;
    for(int j=0;i<strlen(s);i++){
      s1[j]=s[i];
      if(s1[j]==' '&&s1[j-1]==' ');
      else j++;
    }
    strcpy(s,s1);
    while(s[strlen(s)-1]==' ')s[strlen(s)-1]=0;
}
int main()
{
  char s[10000];
  char s1[1000];
  char s2[100];
  char s3[100];
  char s4[1000];
  char tmpfile[]="../data/dltd";

    char key[ZKYLEN];
    int  val;
    btinit();
    BTA *dict,*dict1;
    FILE* fp;

    fp=fopen("../anhviet109K.dict","r");
    dict = btcrt(tmpfile,0,1);

  while(!feof(fp)){
    memset(s,0,10000);
    memset(s2,0,100);

    while(!feof(fp)){
    strcat(s,s1);
    fgets(s1,1000,fp);
    if(s1[0]=='@')break;
    }

    if(s[0]!=0){
      s[999]=0;
      int i=0;
      for(i;i<100;i++)if(s[i]=='/'||s[i]=='\n')break;
      strncpy(s2,s,i+1);
      chuanhoa(s2);
     // printf("%s\n",s2);
      if(btsel(dict,s2,s4,1000,&val)!=0)btins(dict,s2,s,strlen(s)+1);         
    }
  }  
    btcls(dict);
  fclose(fp);
  return 0;
}