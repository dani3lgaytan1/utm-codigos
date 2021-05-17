#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "../include/play.h"
/*Crear la lista ligada circular, head = NULL */
int contador=0;
CDlinked_list* create_clinked_list(){
    CDlinked_list *cdlinked_list = (CDlinked_list *) malloc (sizeof(CDlinked_list));
    cdlinked_list->head = NULL;
    return cdlinked_list;
}

/* Crear un nodo para ser agregado a la lista */
Node* create_node(int item, char *song1,char *artista){
    Node *new_node = (Node *) malloc (sizeof(Node));
    new_node->year = item;
    new_node->id=0;
    new_node->artist=artista;
    new_node->song=song1;
    new_node->next = new_node;
    new_node->prev = new_node;//hacer que apunten al mismo nodo
    return new_node;
}

void insert(Node **head, int item,char *song,char *artista2){
    Node *new_node = create_node(item,song,artista2);
    Node *aux = *head; 

    // Caso 1. Si lista esta vacías
    if (*head == NULL){
        *head = new_node;
        printf("\nDatos ingresados correctamente :)\n");
    } else {
        // Caso 2. si el valor es menor al head
        if (aux->year >= new_node->year){
            while (aux->next != *head)
                aux = aux->next;
            aux->next = new_node;
            new_node->prev=aux;
            new_node->next = *head;
            (*head)->prev=new_node;
            *head = new_node;
            printf("\nDatos ingresados correctamente :)");
            }else {
              // Caso 3. El valor es mayor y se necesita la posición correcta
            while((aux->next != *head) && (aux->next->year < new_node->year))
                aux = aux->next;
            new_node->next = aux->next;
            aux->next->prev=new_node;
            aux->next = new_node;
            new_node->prev=aux;
            printf("\nDatos ingresados correctamente :)");
        }
    }
    
 }

int delete_node(Node **head, int item){
    Node *aux;
    int data = INT_MIN;
    char *song;
    char *artis;
    int id=0;
    // verficar que la lista no esta vacia
    if ( *head == NULL) {
        data = INT_MIN;
    } else {
        //caso 1 se desea eliminar el nodo que esta en head
        if( (*head)->id == item){
            // vericar si head esta apuntado hacia si mismo
            if( ((*head)->next == *head) && ((*head)->prev == *head)){
                data = (*head)->year;
                song= (*head)->song;
                artis=(*head)->artist;
                id=(*head)->id;
                free(*head);
                *head = NULL;
            } else{
                // Donde hay mas de  un nodo y tambien saber cual es que apunta a head
                aux = *head;    
                while((aux->next != *head)&&(aux->next->id!=item)) 
                    aux = aux->next;
                
                aux->next = (*head)->next;
                (*head)->next->prev=aux;
                Node *temp = *head;
                *head = (*head)->next;
                data = temp->year;
                song=temp->song;
                artis=temp->artist;
                id=temp->id;
                free(temp);
            }
        } else {
            //caso 2 se desea eliminar un nodo intermedio
            //buscar el nodo previo
            Node *antes = *head;
            while((antes->next != *head) && (antes->next->id != item)){
                antes = antes->next;
            }
            if (antes->next->id == item){
                Node *ax = antes->next;//nodo para borrar
                antes->next = ax->next;
                ax->next->prev=antes;
                data = ax->year;
                artis=ax->artist;
                song=ax->song;
                data=ax->year;
                id=ax->id;
                free(ax);
            } else {
                data = INT_MAX;
            }
        }
    }
    if (id!=0)
    {  
    printf("\n\nCancion eliminada  %i: ",id);
    printf("\nNombre : %s",song);
    printf("\nArtista: %s",artis);
    printf("\nAño : %i",data);
    }
    return data;
}

void display(CDlinked_list *dlinked_list){
    Node *temp;

    if(dlinked_list->head != NULL){
        temp = dlinked_list->head;
        printf("\nEsta es tu lista de reproducion : ");
       do{  printf("\n▂ ▃ ▅ ▆ █");
            printf("N. %i  ",temp->id);
            printf("cancion : %s  ",temp->song);
            printf("Artista: %s ",temp->artist);
            printf("año: %d ", temp->year);
              printf("█ ▆ ▅ ▃ ▂ \n");
            temp = temp->next;
        }  while ((temp != dlinked_list->head)&&(temp->year!=0));
    }else
    {
        printf("\nMejor ingresa algunas canciones :)\n"); 
           }
    
}
//asignar un numero a las canciones en la lista
int asignarid(CDlinked_list *dlinked_list){
Node *temp;
contador=0;
    if(dlinked_list->head != NULL){
        temp = dlinked_list->head;
        do {
            contador++;
            temp->id=contador;
            temp = temp->next;
        } while (temp != dlinked_list->head);
    }
return contador;

}


void atras(CDlinked_list *dlinked_list, int item){
Node *temp;
if (dlinked_list->head != NULL)
{
    temp=dlinked_list->head;
    while (temp->id<item){
        temp=temp->next;//saber cual es el nodo que contiene el id
    }
    temp=temp->prev;//ir hacia atras
    if (temp->year!=0)
    {
    printf("\n\t♫ ♪ Cancion: %s♫ ♪",temp->song);
    printf("\n▂ ▃ ▅ ▆ █");
    printf("Artista : %s",temp->artist);
    printf(" : %i",temp->year);
    printf("█ ▆ ▅ ▃ ▂ \n");
    printf("\n▄ █ ▄ █ ▄ ▄ █ ▄ █ ▄ █ ▄ ▄ █ ▄ █ ▄ █ ▄ █ ▄\n");   
}    
  
}else{
    printf("\n\n la lista de reproduccion esta vacia.Ingresa algunas canciones!!");
}

}

void siguiente(CDlinked_list *cdlinked_list,int item){
Node *temp;
if (cdlinked_list->head != NULL)
{
    temp=cdlinked_list->head;
    while (temp->id<item){
        temp=temp->next;//saber cual es el nodo que contiene el id
    }
     printf("\n\t♫ ♪ Cancion: %s♫ ♪",temp->song);//imprimir hacia adelnate
    printf("\n▂ ▃ ▅ ▆ █"); 
    printf("artista : %s",temp->artist);
    printf(" : %i",temp->year);
    printf("█ ▆ ▅ ▃ ▂ \n");
    printf("\n▄ █ ▄ █ ▄ ▄ █ ▄ █ ▄ █ ▄ ▄ █ ▄ █ ▄ █ ▄ █ ▄ \n");
}else{
    printf("\n\nla lista de reproduccion esta vacia.Ingresa algunas canciones");
}
}

int eliminar(CDlinked_list *cdlinked_list,int num){//buscar y preguntar si se quiere elimnar el nodo

Node *temp;
int opcion;
if (cdlinked_list->head !=NULL)
{
    temp=cdlinked_list->head;
    while ((temp->id!=num) &&(temp->next != cdlinked_list->head)){
       temp=temp->next;
    }

    if (temp->id==num){
    printf("******************************\n");
    printf("Cancion %i",temp->id);
    printf("\nCancion: %s",temp->song);
    printf("\nartista : %s",temp->artist);
    printf("\nAño : %i\n",temp->year);
    printf("\n⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠⚠");
    printf("\n Desea eliminar la cancion? (Si=1/No=0)");
    scanf("%i",&opcion);

    printf("******************************");
    }else{
      printf("\nLo sentimos no encontramos la cancion :/\n");   
    }
}
return opcion;
}
