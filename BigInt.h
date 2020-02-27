#ifndef BIGINT_H
#define BIGINT_H
#include<iostream>
#include<string>
using namespace std;
class BigInt
{
    int *a,n,semn;
    /*
    - Variabila a va fi un vector alocat dinamic
    - n reprezintq numarul de cifre ale numarului + 1
    - In semn se retine daca numarul este pozitiv sau negativ
    */
public:
    BigInt();//constructorul fara parametrii
    BigInt(const BigInt&);//constructorul de copiere
    BigInt(char *s);//constructorul ce utilizeaza un sir de caractere
    BigInt(int );//constructorul ce utilizeaza o variabila ce are ca parametru un numar intreg
    void Show();//metoda ce afiseaza toate datele ce privsc un obiect
    int Suma();//metoda ce realizeaza suma cifrelor unui obiect
    void Paritate();//metoda ce stabileste daca un numr este par sau impar
    void Verif_Palindrom();//metoda ce verifica daca numarul este palindrom
    void Putere(int );//functie ce calculeaza valoarea unui numar ridicat la o anumita putere
    BigInt operator + (const BigInt &op2);//supraincarcarea operatorului + in vederea adunarii
    BigInt operator - (const BigInt &op2);//supraincarcarea operatorului - in vederea scaderii
    BigInt operator * (const BigInt &op2);//supraincarcarea operatorului * in vederea inmultirii
    BigInt operator / (const BigInt &op2);//supraincarcarea operatorului / in vederea impartirii
    BigInt operator = (const BigInt &op2);//supraincarcarea operatorului = in vederea copierii unui obiect
    BigInt operator = (char *s);//supraincarcarea operatorului = atribuie un numar sub forma de sir de caractere
    BigInt operator = (int x);//supraincarcarea operatorului = atribuie un numar sub forma de int
    friend ostream& operator << (ostream& os, const BigInt& dt);//supraincarca operatorului de afisare
    friend istream& operator >> (istream& is,BigInt& dt);//supraincarca operatorului de citire
    ~BigInt()//destructor
    {
        n=0;
        semn=0;
        delete []a;// se distruce vectorul ce retine numarul
    }
};

#endif // BIGINT_H
