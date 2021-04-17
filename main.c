#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BTREE/inc/btree.h"
#include <time.h>


BTA *dict;
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *p_mn4;
GtkWidget *stack;
GtkWidget *lt,*ok,*text_1,*p_mn1,*p_mn2,*p_mn,*p_mn4,*x1,*x2,*x3,*ets,*eta,*el_p,*stk1,*n1,*lb1,*lb2,*etry,*g[4];
GtkTreeIter Iter;
GtkListStore *list;
GtkEntryCompletion *comple;

int r=0;
int v=0;

int k=0;
char tmpfl[]="../data/dltd";
char s[20][100];
char tu[100][60];
char nghia[100][100];
int val;

void check(GtkButton *button){
  for(int i=0;i<4;i++)if(button==g[i]){
    if(i==v)gtk_button_set_label(button,"chính xác");
    else gtk_button_set_label(button,"chưa chính xác ");
  }
}

int sinhtu(){
  srand((int)time(0));
  r=rand()%100;
  gtk_button_set_label(lt,tu[r]);
  v=rand()%4;  
  gtk_button_set_label(g[v],nghia[r]);
  int a[3];
  for(int i=0;i<3;i++)a[i]=rand()%100;
  int j=0;
  for(int i=0;j<3;i++&&j++){
    if(i==v)i++;
    gtk_button_set_label(g[i],nghia[a[j]]);
  }
   gtk_button_set_label(p_mn1,"tử điển anh việt");
}

int data_luyentap(){
  int size;
  memset(tu,0,6000);
  memset(nghia,0,10000);
  btpos(dict,ZSTART);
  char s1[100];
  char s2[100];
  for(int j=0;j<1000;j++)btseln(dict,s1,s2,59,&size);
  for(int i=0;i<100;i++){
    for(int j=0;j<500;j++)btseln(dict,s1,s2,59,&size);
      {
        btseln(dict,tu+i,nghia+i,100,&size);
        int j=0;
        for( j=0;j<strlen(nghia+i);j++)if(nghia[i][j]=='\n')break;
        strcpy(nghia[i],nghia[i]+j);
      }
  }
}

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

char* space(char *s){
  if(s==NULL)return 0;

  for(int i=0;i<strlen(s);i++)if(s[i]=='_')s[i]=' ';
    return s;
}

void to_page(GtkButton *button,GtkStack *stack){
     gtk_stack_set_visible_child_name(stk1,"page3");
     if(button==p_mn1)gtk_stack_set_visible_child_name(stack,"page1");
     if(button==p_mn)gtk_stack_set_visible_child_name(stack,"page3");
     if(button==p_mn4)gtk_stack_set_visible_child_name(stack,"page2");
     if(button==x2&&kiemtra()==0){
      gtk_stack_set_visible_child_name(stack,"page1");
      char s[1000];
      int sz;
      strcpy(s,gtk_entry_get_text(text_1));
      chuanhoa(s);
      char s1[1000];
      btsel(dict,s,s1,500,&sz);
      s1[150]=0;
      gtk_button_set_label(n1,s1);
      }
     if(button==x3&&kiemtra()==0)gtk_stack_set_visible_child_name(stack,"page2");
     if(button==x1&&kiemtra()==1)gtk_stack_set_visible_child_name(stack,"page0");
}
int kiemtra(){
    char s1[1000];
    char s[1000];
    strcpy(s,gtk_entry_get_text(text_1));
    chuanhoa(s);
    if(strlen(s)>1){
    if(btsel(dict,s,s1,1000,&val)!=0){
       gtk_button_set_label(ok,"chưa có");
       return 1;
    }
    gtk_button_set_label(ok,"đã có");
    return 0;}
    return -1;
}
void back_menu(GtkButton *button,GtkStack *stack){
     gtk_stack_set_visible_child_name(stack,"page0"); 
}
void bt_upd(){
  char s[1000],s1[1000];
     strcpy(s,gtk_entry_get_text(text_1));
     strcpy(s1,gtk_entry_get_text(lb1));
     chuanhoa(s);
     btupd(dict,s,s1,200);
     kiemtra();
     gtk_stack_set_visible_child_name(stk1,"page3");
}
void bt_del(){
     char s[1000];
     strcpy(s,gtk_entry_get_text(text_1));
     chuanhoa(s);
     btdel(dict,s);
     kiemtra();
     gtk_stack_set_visible_child_name(stk1,"page3");
}
void add(){
  char s[1000],s1[1000];
     strcpy(s,gtk_entry_get_text(text_1));
     chuanhoa(s);
     strcpy(s1,gtk_entry_get_text(lb2));
     btins(dict,s,s1,strlen(s1)+1);
     kiemtra();
     gtk_stack_set_visible_child_name(stk1,"page3");
}
void find_word(char *wd){
    
    gtk_list_store_clear(list);
    
    memset(s,0,2000);
    int a;
    int k=0;
    bfndky(dict,wd,&a);
    while(k<20&&bnxtky(dict,s+k,&a)==0){
     if(k<16){
      gtk_list_store_append(list, &Iter);
      gtk_list_store_set(list, &Iter, 0, s+k, -1 );
    }
      k++;}
}
void seach(){
  char word[100];  
    int sz;
    char s2[1000];
    char s1[100];
    memset(s2,0,1000);
    memset(s1,0,100);
      strcpy(word, gtk_entry_get_text(GTK_ENTRY(etry)));
      chuanhoa(word) ;
      if(btsel(dict,word,s2,1000,&sz)==0)
           gtk_label_set_text(GTK_LABEL(eta),s2);
      else gtk_label_set_text(GTK_LABEL(eta),"nghĩa chưa được cập nhât !");
}
void complete(GtkWidget *widget,GdkEventKey *event, gpointer user_data){
    char w[100];
    char word[100];  
    int sz;
    char s2[1000];
    char s1[100];
  {
    if(event->keyval==GDK_KEY_Tab){
        strcpy(s1,s[k]);
        chuanhoa(s1);
        btsel(dict,s1,s2,200,&sz);

        gtk_entry_set_text(GTK_ENTRY(etry),s[k++]);

        gtk_label_set_text(GTK_LABEL(eta),s2);
        if(k>19)k=0;

    }
    else 
      {
        memset(word,0,100);
        strcpy(word, gtk_entry_get_text(GTK_ENTRY(etry)));
        word[strlen(word)]=event->keyval;
        chuanhoa(word); 
        find_word(word);
      }
  }
      
}

int main(){
  memset(s,0,1000);
  dict=btopn(tmpfl,0,1);
  
  data_luyentap();
  
  gtk_init(0, NULL);  
  builder=gtk_builder_new_from_file("../gui1.glade");
  gtk_builder_connect_signals(builder,NULL);
  window=GTK_WIDGET(gtk_builder_get_object(builder,"window_main"));
    

    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    p_mn1=GTK_WIDGET(gtk_builder_get_object(builder,"p_mn1"));
    p_mn=GTK_WIDGET(gtk_builder_get_object(builder,"p_mn"));
    p_mn4=GTK_WIDGET(gtk_builder_get_object(builder,"p_mn4"));
    lt=GTK_WIDGET(gtk_builder_get_object(builder,"lt"));
    x1=GTK_WIDGET(gtk_builder_get_object(builder,"x1"));
    x2=GTK_WIDGET(gtk_builder_get_object(builder,"x2"));
    x3=GTK_WIDGET(gtk_builder_get_object(builder,"x3"));
    ets=GTK_WIDGET(gtk_builder_get_object(builder,"ets"));
    eta=GTK_WIDGET(gtk_builder_get_object(builder,"eta"));
    el_p=GTK_WIDGET(gtk_builder_get_object(builder,"el_p"));
    stk1=GTK_WIDGET(gtk_builder_get_object(builder,"stk1"));
    text_1=GTK_WIDGET(gtk_builder_get_object(builder,"text_1"));
    ok=GTK_WIDGET(gtk_builder_get_object(builder,"ok"));
    n1=GTK_WIDGET(gtk_builder_get_object(builder,"n1"));
    lb1=GTK_WIDGET(gtk_builder_get_object(builder,"lb1"));
    lb2=GTK_WIDGET(gtk_builder_get_object(builder,"lb2"));
    etry=GTK_WIDGET(gtk_builder_get_object(builder,"etrysearch"));
    g[0]=GTK_WIDGET(gtk_builder_get_object(builder,"g0"));
    g[1]=GTK_WIDGET(gtk_builder_get_object(builder,"g1"));
    g[2]=GTK_WIDGET(gtk_builder_get_object(builder,"g2"));
    g[3]=GTK_WIDGET(gtk_builder_get_object(builder,"g3"));
    
    comple = gtk_entry_completion_new();
    gtk_entry_completion_set_text_column(comple, 0);
    list = gtk_list_store_new(1, G_TYPE_STRING);
    gtk_entry_completion_set_model(comple, GTK_TREE_MODEL(list));
    gtk_entry_set_completion(GTK_ENTRY(etry), comple);


    g_signal_connect(etry,"key_press_event",G_CALLBACK(complete),NULL);
    gtk_stack_set_visible_child_name(stk1,"page3");
    gtk_widget_show_all (window);
    
    gtk_main();
    g_object_unref(builder);
    btcls(dict);
    return 0;
}
