
#include "Liste/liste_Objet3D.hpp"


using namespace glimac;


List createNode(Objet3D value)
{   
    //List n = (List) malloc(sizeof(Node));
    List n = new Node;
    if (NULL == n)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
    n->value = value;
    n->next = NULL;
    return n;
}


int lengthList(List tete)
{
    /* Empty list */
    if (tete == NULL)
    {
        return 0;
    }

    int length = 1;
    while (tete->next != NULL)
    {
        length++;
        tete = tete->next;
    }
    return length;
}


/* ATTENTION il faut remettre le pointeur de la liste à NULL
*   donc passage de l'adresse du pointeur
*/
void freeList(List* tete)
{
    /* Empty list */
    if (*tete == NULL)
    {
        return;
    }

    List temp= *tete;
    while (*tete != NULL)
    {
        temp = (*tete)->next;
        free(*tete);
        *tete = temp;
    }
}

List insertHead(List tete, Objet3D value)
{ 
    List newN = createNode(value);
    newN->next = tete;
    return newN;
}

List insertToList(List tete, int index, Objet3D value)
{
    /* Empty list */
    if (tete == NULL)
    {
        if (index == 1)
        {
            return createNode(value);
        }
        fprintf(stderr,"Insertion impossible: Empty list!\n");
        exit(1);
    }

    if (index < 1)
    {
        fprintf(stderr,"Insertion impossible: index too small!\n");
        exit(1);
    }

    /* Head insertion */
    if (index == 1)
    {
        return insertHead(tete,value);
    }

    List prev = tete;
    List temp = tete->next;
    while ((index > 2) && (temp != NULL))
    {
        index--;
        prev = temp;
        temp = temp->next;
    }

    if (index == 2)
    {
        prev->next = insertHead(temp,value);
    }
    else
    {
        fprintf(stderr,"Insertion impossible: index too large!\n");
        exit(1);
    }

    return tete;
}


List removeHead(List tete)
{
    /* Empty list */
    if (tete == NULL)
    {
        fprintf(stderr,"Removalue impossible: Empty list!\n");
        exit(1);
    }

    List next = tete->next;
    free(tete);
    return next;
}
