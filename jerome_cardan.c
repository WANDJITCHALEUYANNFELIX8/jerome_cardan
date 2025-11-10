#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<unistd.h>
#define PI 3.141592653589793

typedef struct monome{
    double coef;
    int degre;
    struct monome*suivant;
}*list_monome;

typedef struct polynome{
    list_monome debut_polynome;
    struct polynome* suivant;
}*list_polynome;

list_monome m=NULL;

void evaluation(list_monome m,double x)
{
	
	if(m==NULL){
		printf("\nliste vide.\n");
		return;
	}
	double resultat=0.0;
	list_monome l=m;
	while(l!=NULL)
	{
		//resultat=resultat*x+l->coef;
		resultat += l->coef * pow(x, l->degre);
		l=l->suivant;		
	}
	printf("\n\tP(%g)=%.12g\n",x,resultat);
}	

list_monome add_monome()
{
	double c;
	int nb_monome;
	list_monome m=NULL;
	do{
		printf("\nEntrer le dégré du polynome (vous pouvez aller jusqu'à 3 puisque c'est JEROME CARDAN): ");
		scanf("%d",&nb_monome);
	}while(nb_monome <= 0 || nb_monome > 3);
	printf("\n\n");	
	for(int i=nb_monome;i>=0;i--)
	{
		printf("Entrer le coefficient du monome de dégré %d, (S'il y'en a pas, mettez 0): ",i);
		scanf("%lf",&c);
		if(c==0) continue;
		list_monome new=(list_monome)malloc(sizeof(struct monome));
		if(new==NULL){
			printf("malloc: Allocation failed.\n");
			exit(EXIT_FAILURE);
		}
		
		new->coef=c;
		new->degre=i;
		new->suivant=NULL;
		if(m==NULL)
        {
            m=new;
        }else{
            list_monome lm=m;
            while(lm->suivant!=NULL)
            {
                lm=lm->suivant;
            }
            lm->suivant=new;
		}
		
	}
	return m;
}	

void afficher_polynome(list_monome m)
{
	list_monome n=m;
	if(n==NULL){
		printf("\nPolynome vide\n");
		return;
	}	
	printf("\n\tp(x)=");
	while(n!=NULL)
	{
		if(n->coef!=0){	
			if (n->degre == 0) {
		    		printf("(%.2f)", n->coef);
		    		if(n->suivant!=NULL){
					printf("+");
				}
			} else if (n->degre == 1) {
		    		if (n->coef != 1){
		        		printf("(%.2f)*x", n->coef);
		        		if(n->suivant!=NULL){
						printf("+");
					}
		    		}else{
		        		printf("x");
		        		if(n->suivant!=NULL){
						printf("+");
					}
				}	
			} else {
		    		if (n->coef != 1){
		        		printf("(%.2f)*x^%d", n->coef, n->degre);
		        		if(n->suivant!=NULL){
						printf("+");
					}
		    		}else{
		        		printf("x^%d", n->degre);
		        		if(n->suivant!=NULL){
						printf("+");
					}
				}	
			}
			n=n->suivant;
		}	
    }
    printf("\nAffichage réussi\n\n");
}

void liberer_polynome(list_monome m)
{
	list_monome tm=m;	
	while(m!=NULL)
	{
		tm=m;
		m=m->suivant;
		free(tm);
	}
}
		
void equation_second_degre(double tab[4]){
	double dis=pow(tab[2],2) - (4*tab[1]*tab[3]);
	if(dis<0){
		dis=dis*(-1);
		double Rx=-tab[2]/(2*tab[1]);
		double Ix=-sqrt(dis)/(2*tab[1]);
		printf("🤔️ Solution complexes: X1= %g+i(%g)  \tX2= %g-i(%g)\n",Rx,Ix,Rx,Ix);
	}else if(dis==0){
		double x0=-tab[2]/(2*tab[1]);
		printf("🤩️ Solution double: X0= %g\n",x0);
		printf("Vérification...\n");
		sleep(2);
		evaluation(m,x0);
	}else{
		double x1=(-tab[2]-sqrt(dis))/(2*tab[1]);	
		double x2=(-tab[2]+sqrt(dis))/(2*tab[1]);
		printf("😁️ Solutions réelles: X1= %f  \tX2= %f\n",x1,x2);
		printf("Vérification...\n");
		sleep(2);
		evaluation(m,x1);		
		evaluation(m,x1);
	}
}
				   	
void application_non_deprime(double tab[4], double p, double q,double dep){
	printf("\n-Posons Y = u+v\n");
	printf("On obtient donc une équation du second dégré: t^2 + q*t - (p^3/27)\n");
	dep=tab[1]/(3*tab[0]);
	double q2=q/2;
	double p3=p/3;
	double dis=pow(q2,2)+pow(p3,3);
	if(dis > 0){
		printf("\n😀️ Discriminant strictement positif, on a une racine réelle et deux racines complexes conjugués (deux racines réelles distinctes).\n");
		double a= -q2-sqrt(dis);
		double b= -q2+sqrt(dis);
		double u= cbrt(a);
		double v=cbrt(b);
		double racine1=u+v;
		printf("La racine réelle est : %g\n",racine1);
		double Rracine2=-0.5*(u+v);
		double Rracine3=-0.5*(u+v);
		double Iracine2=(sqrt(3)/2)*(u-v);
		double X1=racine1 - dep;
		double X2=Rracine2 - dep;
		double X3=Rracine3 - dep;
		printf("\nLe résultat est: p(X)= (X-(%g))(X-(%g)+i(%g))(X-(%g)-i(%g))\n\n",X1,X2,Iracine2,X3,Iracine2);
		printf("\nTaper ENTREE pour continuer.....\n");
		getchar();
		printf("Evaluons le polynome(si P(val)<10^-12)...\n");
		evaluation(m,X1);	
		
    }else if(dis==0){
    	if(p>pow(10,-12)){
			printf("😶️ Discriminant nul, on a une racine double a.\n");
			double u=cbrt(-q2);
			double racine1=2*u;
			double racine2=-u;				
			printf("Les racines sont: racine1=%g\tracine2=%g(double)\n",racine1,racine2);
			double X1=racine1 - dep;
			double X2=racine2 - dep;
			printf("\nRésultat: p(X)=(X-%g)((X-%g)^2)\n\n",X1,X2);
			printf("\nTaper ENTREE pour continuer.....\n");
			getchar();
			printf("Evaluons le polynome(si P(val)<10^-12)...\n");
			evaluation(m,X1);
			evaluation(m,X2);
			
    	}else{
    		printf("😶️ Discriminant nul, on a une racine triple (car p est sensiblement égale à 0.");
    		double racine=0;
    		double X=racine - dep;
    		printf("Le résultat est: p(X) = (X-(%g))^3\n",X);
    	}	
    }else{
    	printf("🤔️ Discriminant strictement négatif, on a 3 racines réelles....\n");
    	double r=-p/3;
    	if(r<0)r=0;
		double pr=2*sqrt(r);
		double c=(-q2)/(sqrt(pow(r,3)));
		if(c>1)c=1;
		if(c<-1)c=-1;
		double angle=acos(c);
		double racine1=pr*cos(angle / 3);
		double racine2=pr*cos((angle + 2*PI) / 3);
		double racine3=pr*cos((angle + 2*PI*2) / 3);
		double X1=racine1 - dep;
		double X2=racine2 - dep;
		double X3=racine3 - dep;
		printf("Les racines sont: %g\t%g\t%g\n",X1,X2,X3);
		printf("\nRésultat: P(X)=(X-(%g))(X-(%g))(X-(%g))\n\n",X1,X2,X3);
		printf("\nTaper ENTREE pour continuer.....\n");
		getchar();
		printf("Evaluons le polynome (P(val) doit etre <10^-12)...\n");
		evaluation(m,X1);
		evaluation(m,X2);
		evaluation(m,X3);
    }
} 

void estce_deprime(double tab[4],double p,double q){
	double dep=tab[1]/(3*tab[0]);
	//s'il est déjà déprimé, dep=0
	if(dep!=0){
		printf("\nLe polynome n'est cubique déprimé (pas sous la forme X^3 + p*X + q=0). Mettons la sous la forme cubique déprimé.\n\n");
		printf("-Posons X=Y-b/3a..\n");
		printf("-Trouvons p et q .....\n");
		printf("\nTaper ENTREE pour continuer.....\n");
		getchar();
		printf("\np = %g; q = %g \n",p,q);
		application_non_deprime(tab,p,q,dep);
	}else{
		printf("\nPolynome cubique déjà déprimé\n");
		application_non_deprime(tab,p,q,dep);	
	}	
}

void ecrire_progressivement(const char* texte, int delai){
	for(int i=0; texte[i]!='\0';i++){
		putchar(texte[i]);
		fflush(stdout);
		usleep(delai);
	}
}
			       
int main(){
	system("clear");
    printf("\n\t\t------------------------------------------------------------------------------------------\n");
    printf("\t\t||"); 
    printf("\033[1;42m"); 
    ecrire_progressivement("\t\t\t\tAPPLICATION DE JEROME CARDAN \t\t",120000);
    printf("\033[0m");
    printf("\t\t||\n");
    printf("\t\t------------------------------------------------------------------------------------------\n");
    printf("\033[1;36m");
    
	printf("\nCréation du polynome... \n\n");
	list_monome M=add_monome();
	
	if(M==NULL){
		printf("polynome vide\n");
		exit(0);
	}	
	m=M;
	afficher_polynome(M);
	printf("\nTaper ENTREE pour continuer.....\n");
	getchar();getchar();
    
	list_monome t=M;

	double Tab[4]={0,0,0,0};
	while(t!=NULL){
		if (t->degre >= 0 && t->degre <= 3) {
			Tab[3-t->degre]=t->coef;
		}else{
			printf("Attention 😑️😑️: polynome avec pour dégré maximale 3\n");
		}		
		t=t->suivant;
	}	
	if(Tab[0]==0 && Tab[1]==0 ){
		if(Tab[2]==0){
			printf("😶️ PAS DE SOLUTION\n");
			printf("\nTaper ENTREE pour continuer.....\n");
			getchar();
			
		}else{
			printf("😐️ Solution linéaire: X=%g\n",-Tab[3]/Tab[2]);
			printf("\nTaper ENTREE pour continuer.....\n");
			getchar();
		}	
		liberer_polynome(M);
		return 0;
	}else if(Tab[0]==0 && Tab[1]!=0){
		printf("Equation du second dégré..\n");
		equation_second_degre(Tab);
		printf("\nTaper ENTREE pour continuer.....\n");
		getchar();
		liberer_polynome(M);
		return 0;
	}else{	
		//Normalisation de p et Q
		double P=(3*Tab[0]*Tab[2]-pow(Tab[1],2)) / (3*pow(Tab[0],2));
		double Q=(2*pow(Tab[1],3) - 9*Tab[0]*Tab[1]*Tab[2] + 27*pow(Tab[0],2)*Tab[3]) / (27*pow(Tab[0],3));
		
		estce_deprime(Tab,P,Q);
		liberer_polynome(M);
	}
	return 0;
}		
		
