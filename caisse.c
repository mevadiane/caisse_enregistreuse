#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Structure pour les billets/pièces
typedef struct {
    int valeur;     // Valeur en cents (pour éviter les problèmes de float)
    char *nom;      // Description
    int quantite;   // Quantité disponible
} Monnaie;

// Initialisation des billets/pièces disponibles
void initialiser_stock(Monnaie *stock) {
    int valeurs[] = {200000, 100000, 50000, 20000, 10000, 5000, 2000, 1000, 500, 250};
    char *noms[] = {"Billet Rs2000", "Billet Rs1000", "Billet Rs500", "Billet Rs200", 
                   "Billet Rs100", "Billet Rs50", "Billet Rs20", "Billet Rs10", 
                   "Pièce Rs5", "Pièce Rs2.50"};
    
    for (int i = 0; i < 10; i++) {
        stock[i].valeur = valeurs[i];
        stock[i].nom = noms[i];
        stock[i].quantite = 10; // Quantité initiale
    }
}

// Fonction pour calculer et rendre la monnaie
void calcule_monnaie(double montant, Monnaie *stock) {
    printf("\nMonnaie à rendre: Rs%.2f\n", montant);
    
    // Conversion en cents pour éviter les erreurs d'arrondi
    int reste = (int)round(montant * 100);
    
    for (int i = 0; i < 10; i++) {
        if (reste <= 0) break;
        
        int nb_pieces = reste / stock[i].valeur;
        if (nb_pieces > 0 && stock[i].quantite > 0) {
            int a_rendre = (nb_pieces <= stock[i].quantite) ? nb_pieces : stock[i].quantite;
            printf("%d x %s\n", a_rendre, stock[i].nom);
            reste -= a_rendre * stock[i].valeur;
            stock[i].quantite -= a_rendre;
        }
    }
    
    if (reste > 0) {
        printf("Impossible de rendre Rs%.2f (manque de billets/pièces)\n", reste/100.0);
    }
}

// Afficher l'état du stock
void afficher_stock(Monnaie *stock) {
    printf("\nStock disponible:\n");
    for (int i = 0; i < 10; i++) {
        printf("%-15s: %d\n", stock[i].nom, stock[i].quantite);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Monnaie stock[10];
    initialiser_stock(stock);
    char continuer = 'o';
    
    while (continuer == 'o' || continuer == 'O') {
        // Génération du montant à payer
        double vPayer = ((double)rand()/RAND_MAX)*(10000.00-10.00)+10.00;
        vPayer = round(vPayer*100)/100; // Arrondi à 2 décimales
        printf("\nVous devez payer Rs%.2f\n", vPayer);

        double vPaiement = 0;
        double totalPaye = 0;
        
        while (totalPaye < vPayer) {
            printf("\nMontant restant à payer: Rs%.2f\n", vPayer - totalPaye);
            printf("Entrez votre paiement: ");
            scanf("%lf", &vPaiement);
            
            if (vPaiement <= 0) {
                printf("Montant invalide!\n");
                continue;
            }
            
            totalPaye += vPaiement;
            
            if (totalPaye < vPayer) {
                printf("Il vous reste Rs%.2f à payer\n", vPayer - totalPaye);
            }
        }

        // Calcul de la monnaie si nécessaire
        if (totalPaye > vPayer) {
            calcule_monnaie(totalPaye - vPayer, stock);
        } else {
            printf("Paiement exact, merci!\n");
        }
        
        afficher_stock(stock);
        
        // Vérifier si on peut continuer
        int peut_continuer = 0;
        for (int i = 0; i < 10; i++) {
            if (stock[i].quantite > 0) {
                peut_continuer = 1;
                break;
            }
        }
        
        if (!peut_continuer) {
            printf("\nPlus de monnaie disponible!\n");
            printf("1. Remplir la caisse\n");
            printf("2. Quitter\n");
            printf("Votre choix: ");
            int choix;
            scanf("%d", &choix);
            
            if (choix == 1) {
                initialiser_stock(stock);
                printf("Caisse remplie à nouveau!\n");
            } else {
                continuer = 'n';
            }
        } else {
            printf("\nVoulez-vous effectuer une autre transaction? (o/n): ");
            scanf(" %c", &continuer); // Notez l'espace avant %c pour ignorer les retours à la ligne
        }
    }
    
    printf("Merci d'avoir utilisé notre caisse enregistreuse!\n");
    return 0;
}
