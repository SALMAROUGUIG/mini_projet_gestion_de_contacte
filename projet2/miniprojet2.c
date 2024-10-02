#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"


struct Contact {
    int id;
    char name[20];
    char phone[15];
    char email[25];
};
struct Contact table[100];
int ind = 0;

void ajouter_contacts_defaut() {
    const char noms[10][20] = {
        "salma", "hiba", "yasmina", "rita", "bilal",
        "mehdi", "ghazal", "rida", "walid", "rose"
    };
    const char telephones[10][15] = {
        "0617818778", "06156345671", "0671819054",
        "07890654", "063325679", "0614557899",
        "5678901234", "066729836", "0671889007", "067121098"
    };
    const char emails[10][30] = {
        "salmarg67@gmail.com", "hiba@gmail.com", "yasmina@gmail.com",
        "rita@gmail.com", "bilal@gmail.com", "mehdi@gmail.com",
        "ghazal@gmail.com", "rida@gmail.com", "walid@gmail.com",
        "rose@gmail.com"
    };
    for (int i = 0; i < 10 && ind < 100; i++) {
        table[ind].id = ind + 1;
        strcpy(table[ind].name, noms[i]);
        strcpy(table[ind].phone, telephones[i]);
        strcpy(table[ind].email, emails[i]);
        ind++;
    }

    printf("deja 10 contact sont ajouter par default.\n" );
}

void ajout_contact() {
    if (ind >= 100) {
        printf(YELLOW "le Carnet est plein!!\n" RESET);
        return;
    }

    struct Contact nvcontact;
    nvcontact.id = ind + 1;
    printf("entrer le nom: ");
    scanf("%s", nvcontact.name);

    printf("entrer telephone: ");
    scanf("%s", nvcontact.phone);

    for (int i = 0; i < ind; i++) {
        if (strcmp(table[i].phone, nvcontact.phone) == 0) {
            printf( RED"ce numero est deja existe!!\n" RESET );
            return;
        }
    }

    printf("entrer l\'email: ");
    scanf("%s", nvcontact.email);

    for (int i = 0; i < ind; i++) {
        if (strcmp(table[i].email, nvcontact.email) == 0) {
            printf( "l\'email que tu as saisit deja existe !!\n" );
            return;
        }
    }

    table[ind++] = nvcontact;
    printf( "bien ajouté.\n" );
}
void afficher_contacts() {
    if (ind== 0) {
        printf( "pas de contact!!\n" );
        return;
    }

    printf("+-----+----------------+-------------+--------------------------+\n");
    printf("| ID |      NOM    |  TELEPHPNE      |           EMAIL          |\n");
    printf("+-----+----------------+-------------+--------------------------+\n");

    for (int i = 0; i < ind; i++) {
        printf("| %3d | %-14s | %-11s | %-24s |\n",
               table[i].id, table[i].name, table[i].phone, table[i].email);
    }

    printf("+-----+----------------+--------------+--------------------------+\n");
}
void rechercher_contact() {
    char search[15];
    printf("entrer le telephone du contact a chercher: ");
    scanf("%s", search);

    for (int i = 0; i < ind; i++) {
        if (strcmp(table[i].phone, search) == 0) {
            printf("ID: %d, Nom: %s, Téléphone: %s, Email: %s\n" ,
                   table[i].id, table[i].name, table[i].phone, table[i].email);
            return;
        }
    }
    printf("Contact non trouvé.\n" );
}

void modifier_contact() {
    char search[15];
    printf(YELLOW"Pour modifier les infos de contact, merci de saisir son numéro de téléphone: "RESET);
    scanf("%s", search);

    for (int i = 0; i < ind; i++) {
        if (strcmp(table[i].phone, search) == 0) {
            printf("Nouveau nom: ");
            char nvname[20];
            scanf("%s", nvname);
            strcpy(table[i].name, nvname);

            printf("Nouveau téléphone: ");
            char nvtelephone[15];
            scanf("%s", nvtelephone);

            for (int j = 0; j < ind; j++) {
                if (strcmp(table[j].phone, nvtelephone) == 0 && j != i) {
                    printf(GREEN"le numero est deja utilisé!!\n" RESET);
                    return;
                }
            }
            strcpy(table[i].phone, nvtelephone);

            printf("Nouveau email: ");
            char nvemail[30];
            scanf("%s", nvemail);
            strcpy(table[i].email, nvemail);
            printf( "Contact bien modifié.\n" );
            return;
        }
    }
    printf( "Contact non trouvé.\n" );
}
void supprimer_contact() {
    char search[15];
    printf("Entrer le numéro de téléphone du contact à supprimer: ");
    scanf("%s", search);

    for (int i = 0; i < ind; i++) {
        if (strcmp(table[i].phone, search) == 0) {
            for (int j = i; j < ind - 1; j++) {
                table[j] = table[j + 1];
            }
            ind--;
            printf(RED "Contact supprimé avec succès.\n"RESET );
            return;
        }
    }
    printf( "Contact non trouvé.\n" );
}
int main() {
    ajouter_contacts_defaut();
    int choix;
    do {
        printf("1. Ajouter un contact\n" );
        printf( "2. Afficher les contacts\n" );
        printf( "3. Rechercher un contact\n" );
        printf( "4. Modifier un contact\n" );
        printf( "5. Quitter\n" );
        printf("Choisissez une option: " );
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajout_contact();
                break;
            case 2:
                afficher_contacts();
                break;
            case 3:
                rechercher_contact();
                break;
            case 4:
                modifier_contact();
                break;
            case 5:
                printf( "Au revoir!\n" );
                break;
            default:
                printf( "Option invalide.\n" );
        }

    } while (choix != 5);

    return 0;
}