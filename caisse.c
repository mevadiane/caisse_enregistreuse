#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	srand(time(NULL));
	double vPayer=0;
	double min=10.00;
	double max=10000.00;
	vPayer=((double)rand()/RAND_MAX)*(max-min)+min;
	printf("Vous devez payer Rs %.2f\n", &vPayer);

	int vPaiement=0;
	printf("Valeur de paiement: \n");
	scanf("%lf", &vPaiement);

	while(vPaiement<vPayer)
	{
		double restePayer=vPayer-vPaiement;
		printf("Il vous reste Rs %.2f", &restePayer, " à payer");
		printf("Veuillez entrer une autre valeur de paiement");
		double paiementSup=0;
		scantf("%lf", &paiementSup);
		vPaiement+=paiementSup;
	}

	double change=vPaiement-vPayer;
	if(change>0)
	{
		printf("Votre monnaie : Rs %.2\n", change);
	else
	{
		printf("Paiement exact. Merci\n");
	}
	return 0;
}

