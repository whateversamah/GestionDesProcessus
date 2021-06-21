#include<iostream>
#include<fstream>
#include "RR.h"
#include "fifo.h"
#include "sjf.h"

using namespace std;
void fifo(void)
{
    int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    int numberOfProcessus;
    cout<<"Entrer le nombre des processus(maximum 20):";
    cin>>n;


    ifstream inputFile ;
    inputFile.open("data.txt");
    i = 0;
    while(!inputFile.eof())
    {
       inputFile >> bt[i];
        i++;
    }
    numberOfProcessus = i;


    wt[0]=0;    //temps d'attente du premier processus est 0

    //calcul du temps d'attente
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }

    cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";

    //calculating turnaround time
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avwt+=wt[i];
        avtat+=tat[i];
        cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i];
    }

    avwt/=i;
    avtat/=i;
    cout<<"\n\nMoyenne de Temps d'Attente:"<<avwt;
    cout<<"\nMoyenne de Temps de Rotation:"<<avtat;

}
void RR(void)
{
    // initialisation des variables
    int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
   cout<<" Entrer le nombre des processus (maximum 10): ";
   cin>>NOP;
    y = NOP; // Assigner le nombre du processus a la variable y


for(i=0; i<NOP; i++)
{
cout<<"\n Enter le temps d arrive et d execution :" ;
cout<<" Temps d'arrive : ";  // temps d'arrive
cin>>at[i];
cout<<" \nTemps d'execution : "; // temps d'execution
cin >>bt[i];
temp[i] = bt[i]; // enregistrer temps d'execution dans l'array
}
// Quantum
cout<<"Entrer le Quantum pour le processus:";
cin>>quant;
// Affichage de :the process No, burst time, Turn Around Time and the waiting time
cout<<"\n Process  \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ";
for(sum=0, i = 0; y!=0; )
{
if(temp[i] <= quant && temp[i] > 0) // definir les conditions
{
    sum = sum + temp[i];
    temp[i] = 0;
    count=1;
    }
    else if(temp[i] > 0)
    {
        temp[i] = temp[i] - quant;
        sum = sum + quant;
    }
    if(temp[i]==0 && count==1)
    {
        y--; //decrementer le numero du processus
        cout<<"\nProcess "<<i+1<<" \t\t" << bt[i]<<"\t\t\t\t" << sum-at[i]<<"\t\t\t"<< sum-at[i]-bt[i];
        wt = wt+sum-at[i]-bt[i];
        tat = tat+sum-at[i];
        count =0;
    }
    if(i==NOP-1)
    {
        i=0;
    }
    else if(at[i+1]<=sum)
    {
        i++;
    }
    else
    {
        i=0;
    }
}
//Moyenne de Temps d'Attente et Moyenne de Temps de Rotation
avg_wt = wt * 1.0/NOP;
avg_tat = tat * 1.0/NOP;
printf("\n Moyenne de Temps d'Attente: \t%f", avg_wt);
printf("\n Moyenne de Temps de Rotation: \t%f", avg_tat);

}
void sjf(void)
{
// initlialiser les variables
      int n,temp,tt=0,min,d,i,j, a[n],b[n],e[n],tat[n],wt[n];
      int numberOfProcessus;
      float avtat=0,avwt=0,stat=0,swt=0;

      cout<<"Entrer le nombre des processus (maximum 10):"<<endl;
      cin>>n;

// lecture des details comme le temps d'arrive et temps d'execution

      ifstream inputFile ;
    inputFile.open("burst.txt");
    i = 0;
    while(!inputFile.eof())
    {
       inputFile >> b[i];
        i++;
    }
    ifstream halFile ;
    halFile.open("arrival.txt");
    i = 0;
    while(!halFile.eof())
    {
       halFile >> a[i];
        i++;
    }
    numberOfProcessus = i;// assigner le nombre de processus a la variable i




      for(i=0;i<n;i++)
      {
         for(j=i+1;j<n;j++)
          {
                if(b[i]>b[j])
                {
                      temp=a[i];
                      a[i]=a[j];
                      a[j]=temp;

                      temp=b[i];
                      b[i]=b[j];
                      b[j]=temp;
                }
          }
      }
      min=a[0];
      for(i=0;i<n;i++)
      {
            if(min>a[i])
            {
                  min=a[i];
                  d=i;
            }
      }
      tt=min;
      e[d]=tt+b[d];
      tt=e[d];

      for(i=0;i<n;i++)
      {
            if(a[i]!=min)
            {
                  e[i]=b[i]+tt;
                  tt=e[i];
            }
      }
      for(i=0;i<n;i++)
      {

            tat[i]=e[i]-a[i];
            stat=stat+tat[i];
            wt[i]=tat[i]-b[i];
            swt=swt+wt[i];
      }
      avtat=stat/n;
      avwt=swt/n;
      cout<<"Process  Arrival time(s)  Burst time(s)  Waiting time(s)  Turnaround time(s)\n";

    for(i=0;i<n;i++)
    {
    cout<<"P"<<i+1<<"              "<<a[i]<<"                "<<b[i]<<"                  "<<wt[i]<<"               "<<tat[i]<<endl;
    }

    cout<<"Moyenne de Temps d'Attente:"<<avwt<<" Moyenne de temps de Rotation:"<<avtat;  //Moyenne de Temps d'Attente et Moyenne de temps de Rotation
}

void mq(void)
{
    // initlialiser les variables

int p[20],bt[20], su[20], wt[20],tat[20],i, k, n, temp[20];
float wtavg, tatavg;
cout<<"Entrer le nombre des processus(maximum 10):";
cin>>n;
//lire les details des processus
for(i=0; i<n; i++)
{
   p[i]=i;
  ifstream ouvrir;
   ouvrir.open("process.txt");
    i = 0;
    while(!ouvrir.eof())
    {
       ouvrir >> p[i] ;
        i++;
    }


 ifstream inputFile ;
    inputFile.open("burstMQ.txt");
    i = 0;
    while(!inputFile.eof())
    {
       inputFile >> bt[i];
        i++;
    }
    ifstream halFile ;
    halFile.open("userProcess.txt");
    i = 0;
    while(!halFile.eof())
    {
      halFile >> su[i];
        i++;
    }
    temp[i] = bt[i];
    }
for(i=0;i<n;i++)
for(k=i+1;k<n;k++)
if(su[i] > su[k])// definir les conditions
{
temp[i]=p[i];
p[i]=p[k];
p[k]=temp[i];
temp[i]=bt[i];
bt[i]=bt[k];
bt[k]=temp[i];
temp[i]=su[i];
su[i]=su[k];
su[k]=temp[i];
}
wtavg = wt[0] = 0;
tatavg = tat[0] = bt[0];
for(i=1;i<n;i++)
{
//  temps d'attente et temps de rotation
wt[i] = wt[i-1] + bt[i-1];
tat[i] = tat[i-1] + bt[i];
// Moyenne de Temps d'Attente et Moyenne de temps de Rotation
wtavg = wtavg + wt[i];
tatavg = tatavg + tat[i];
}
cout<<"\nProcess\tSYS/USR Process\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time";
for(i=0;i<n;i++)
cout<<"\nP["<<i<<"]"<<"\t\t\t"<<su[i]<<"\t\t\t"<<bt[i]<<"\t\t\t"<<wt[i]<<"\t\t\t"<<tat[i];
// Moyenne de Temps d'Attente et Moyenne de temps de Rotation
cout<<"\n\nMoyenne de Temps d'Attente:"<<wtavg/n;
cout<<"\nMoyenne de Temps de Rotation:"<<tatavg/n;


}

void admin()
{
  while(1)
  {
 	cout<<"\n\t\t\t==============================\n";
	cout<<"\n\t\t\t          BIENVENUE   \n";
	cout<<"\n\t\t\t==============================\n\n";
	cout<<"\n\t\t\t* * * * * * * * * * * * * * * *\n";
 	cout<<"\n\t\t\t1. First In First Out  \n\n\t\t\t2. Multilevel Queue\n\n\t\t\t3. Shortest Job First\n\n\t\t\t4. Round Robin \n\n\t\t\t5. Quitter \n";
  cout<<"\n\n\t\t\tEntrez votre choix !\n";
  int u;
  cin>>u;
if(u==1)
  {
  fifo();
}
  else if(u==2)
  {
  mq();
}
  else if(u==3)
  {
  sjf();
}
  else if(u==4)
  {
  RR();
}

  else if(u==5)
  {
  break;
}
  else cout<<"Option invalide. Essayez encore une fois!\n";
 }

}


int main(){

    int ch;



      while(1){
        cout<<"\n \t\t\t ";
        cout<<"\n \t\t\t";
        cout<<"\n \t\t\t";
        cout<<"\n \t\t\t* * * * * * * * * * * *  * * * * * * * * * * *  * ";
         cout<<"\n \t\t\tBIENVENUE SUR LE SYSTEME D'ORDONNANCEMENT DES PROCESSUS";
        cout<<"\n \t\t\t* * * * * * * * * * * *  * * * * * * * * * * *  * ";
        cout<<"\n\t\t\t  1. ACCEDER AU SYSTEME";
        cout<<"\n\t\t\t  2. QUITTER";
        cout<<"\n\t\t\t* * * * * * * * * * * *\n";
        cout<<"\n\t\t\t Entrer Votre Choix: ";
        cin>>ch;
        switch(ch){
            case 1:
                admin();
                break;
            case 2:
                exit(0);
                break;
            default:
                cout<<"Entrer un choix valide!\n";
                break;
        }
    }
    return 0;
}

