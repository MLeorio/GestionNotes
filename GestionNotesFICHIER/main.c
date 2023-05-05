/*
    Name : main.c
    Goal : Traitement de notes des etudiants
    Author : Fernand Afanou
    Date : 2023/04/21
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ETUDIANTS 50
#define MAX_NOTES 3

typedef struct
{
    char nom[20];
    char prenom[20];
    float notes[MAX_NOTES];
    float moyenne;
    float bonus;
    char resultat;
} Etudiant;

void saisir_identites(Etudiant *etudiants, int *n);
void saisir_notes(Etudiant *etudiants, int n,  int currentStudent);
void calculer_moyennes(Etudiant *etudiants, int n);
void afficher_informations(Etudiant *etudiants, int n);
void sauvegarder(Etudiant *etudiants, int n);
void recuperer(Etudiant *etudiants, int *n, int *currentStudent);

int main()
{
    int choix, n=0, currentStudent=0;
    Etudiant etudiants[MAX_ETUDIANTS];

    /*printf("Combien d'etudiants voulez-vous ajouter ? (maximum %d) : ", MAX_ETUDIANTS);
    scanf("%d", &n);
    if (n > MAX_ETUDIANTS)
    {
        printf("Erreur : Le nombre maximum d'etudiants est de %d\n", MAX_ETUDIANTS);
        return 0;
    }
    */
    do
    {
        system("cls");
        printf("\n\tProgramme de gestion de notes : \n");
        printf("\n\tAffichage du Menu : \n");
        printf("1. Saisir les identites des etudiants\n");
        printf("2. Saisir les notes des etudiants\n");
        printf("3. Calculer les moyennes\n");
        printf("4. Afficher les informations\n");
        printf("7. Savegarder\n");
        printf("8. Récupérer\n");
        printf("9. Quitter\n");


        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            saisir_identites(etudiants, &n);
            break;
        case 2:
            saisir_notes(etudiants, n, currentStudent);
            break;
        case 3:
            calculer_moyennes(etudiants, n);
            break;
        case 4:
            afficher_informations(etudiants, n);
            break;
        case 7:
            sauvegarder(etudiants, n);
            break;
        case 8:
            recuperer(etudiants, &n, &currentStudent);
            break;
        case 9:
            printf("\nAu revoir !\n");
            break;
        default:
            printf("\nErreur : choix invalide\n");
            break;
        }
    }
    while (choix != 9);

    return 0;
}

void saisir_identites(Etudiant *etudiants, int *n)
{
    system("cls");
    fflush(stdin);
    /*for (int i = 0; i < n; i++)
    {*/
        int nuEtud = (*n)++;
        printf("\n***Saisie d'un nouvel étudiant***");
        printf("\nEtudiant %d : \n", nuEtud+1);
        printf("Nom : ");
        scanf("%s", etudiants[nuEtud].nom);
        printf("Prenom : ");
        scanf("%s", etudiants[nuEtud].prenom);
        for (int j = 0; j < MAX_NOTES; j++)
        {
            etudiants[nuEtud].notes[j] = 0;
        }
        etudiants[nuEtud].moyenne = 0;
        etudiants[nuEtud].bonus = 0;
        etudiants[nuEtud].resultat = ' ';

    //}
}

void saisir_notes(Etudiant *etudiants, int n, int cs)
{
    system("cls");
    for (int i = cs; i < n; i++)
    {
        printf("\nNotes de %s %s : \n", etudiants[i].nom, etudiants[i].prenom);
        for (int j = 0; j < MAX_NOTES; j++)
        {
            printf("Note %d : ", j+1);
            scanf("%f", &etudiants[i].notes[j]);
        }
    }
}

void calculer_moyennes(Etudiant *etudiants, int n)
{
    system("cls");
    for (int i = 0; i < n; i++)
    {
        float somme = 0;
        for (int j = 0; j < MAX_NOTES; j++)
        {
            somme += etudiants[i].notes[j];
        }
        etudiants[i].moyenne = somme / MAX_NOTES;

        if (etudiants[i].moyenne >= 10)
        {
            etudiants[i].resultat = 'V';
        }
        else if (etudiants[i].moyenne > 9)
        {
            etudiants[i].bonus = 10 - etudiants[i].moyenne;
            etudiants[i].resultat = 'V';
        }
        else
        {
            etudiants[i].resultat = 'N';
        }
    }
}

void afficher_informations(Etudiant *etudiants, int n)
{
    system("cls");
    printf("\n\nListe des etudiants : \n");
    printf("\n\n+**********************************************************************************************+");
    printf("\n| %-5s | %-15s | %-15s | %-6s | %-6s | %-6s | %-8s | %-10s |", "ID", "Nom", "Prenoms", "Note 1", "Note 2", "Note 3", "Moyenne", "Verdict");
    printf("\n+*******+*****************+*****************+********+********+********+**********+************+\n");

    for (int cpt = 0; cpt < n; cpt++)
    {
        printf("| %-5d | %-15s | %-15s | %-6.2f | %-6.2f | %-6.2f | %-8.2f | %-10c |", cpt + 1, etudiants[cpt].nom, etudiants[cpt].prenom,
               etudiants[cpt].notes[0], etudiants[cpt].notes[1], etudiants[cpt].notes[2], etudiants[cpt].moyenne, etudiants[cpt].resultat);
        printf("\n+*******+*****************+*****************+********+********+********+**********+************+\n");
    }
    fflush(stdin);
    getchar();
}

void sauvegarder(Etudiant *etudiants, int n)
{
    unsigned int cpt, nbOctets;
    // But : Contrôler l'ouverture du fichier paramétré
    FILE *P_FICHIER = fopen("lstNotes.dat", "wb");
    if (!P_FICHIER)
    {
        printf("\aERREUR: Impossible d'ouvrir "
               "le fichier");
    }
    for(cpt=0; cpt < n; cpt++)
    {
        nbOctets = fwrite(&etudiants[cpt],sizeof(Etudiant), 1, P_FICHIER);
        //printf("\nRec %d Octets = %d sur %u", cpt+1, nbOctets, sizeof(etudiants[cpt]));
    }
    fclose(P_FICHIER);
    fflush(stdin);
    //getchar();
}

void recuperer(Etudiant *etudiants, int *n, int *cs)
{
    size_t nbOctets;
    Etudiant etd;

    // But : Contrôler l'ouverture du fichier paramétré
    FILE *P_FICHIER = fopen("lstNotes.dat", "rb");
    if (!P_FICHIER)
    {
        printf("\aERREUR: Impossible d'ouvrir "
               "le fichier");
    }
    *n = 0;
    while(!feof(P_FICHIER))
    {
        nbOctets = fread(&etd,sizeof(Etudiant), 1, P_FICHIER);
        //fread(&etd,sizeof(Etudiant), 1, P_FICHIER);
        //printf("\nRec %d Octets = %d sur %d", cpt+1, nbOctets, sizeof(etudiants[cpt]));
        if(nbOctets)
        {
            etudiants[(*n)++] = etd;
        }
        //printf("\n%s\t%s", etd.nom, etd.prenom);
    }
    fclose(P_FICHIER);
    *cs = *n;
    //printf("%d", *cs);
    fflush(stdin);
    getchar();
}
