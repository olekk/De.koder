#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

int ilelinii=0;
vector<string> liniewpliku;

fstream plik;
string nazwapliku;


void zapis()
{
    ofstream zapisplik(nazwapliku);
    for(int i=0; i<ilelinii; i++)
    {
        zapisplik << liniewpliku[i]<<"\n";
    }
    zapisplik.close();
}

void dekoder()
{
    cout<<endl<<"DEKODER";
    const int klucz = liniewpliku[0][4]-48;

    for(int i=0; i<ilelinii; i++)
    {
        for(int j=0; j<liniewpliku[i].length(); j++)
        {
            liniewpliku[i][j]+=(klucz*3);
        }
    }

    liniewpliku[0].erase(0,5);


    zapis();
}

void koder()
{
    cout<<"KODER";
    srand(time(NULL));
    const int klucz = rand()%9+1;

    for(int i=0; i<ilelinii; i++)
    {
        for(int j=0; j<liniewpliku[i].length(); j++)
        {
            liniewpliku[i][j]-=(klucz*3);
        }
    }

    char dopisek[7] = "olek";
    dopisek[4] = klucz+48;

    liniewpliku[0] = dopisek + liniewpliku[0];

    zapis();
}


int main()
{

    do
    {
        system("cls");
        cout<<"Plik: ";
        cin>>nazwapliku;
        plik.open(nazwapliku, ios::in | ios::out | ios::app);
    }while(!plik.good());


    string liniatmp;
    while(!plik.eof())
    {
        getline(plik, liniatmp);
        liniewpliku.push_back(liniatmp);
        ilelinii++;
    }

    if(liniewpliku[0][0]=='o' && liniewpliku[0][1]=='l' && liniewpliku[0][2]=='e' &&
        liniewpliku[0][3]=='k') dekoder();
    else koder();

    plik.close();

    return 0;
}
