#include "BigInt.h"
#include <iostream>
#include<string>
#include <cstring>
BigInt::BigInt()//constructorul fara parametrii
{
    a=NULL;//vectorul alocat dinamic devine nul
    n=0;//numarul de elemente
}
BigInt::BigInt(char *s)//constructorul ce are ca parametru un sir de caractere
{
    int i=0,u=0;//u este variabila care detecteaza daca numarul este negativ sau nu
    n=strlen(s);//se retine lumgimea numarului
    a=new int[strlen(s)+1];//se aloca spatiul necesar retinerii numarului
    if(s[0]=='-')//se verifica daca primul caracter este -
    {
        semn=-1;//semnul devine -1, deoarece primul caracter din numar este -
        u=1;//se detecteaza faptul ca numarul este negativ
    }
    else
        semn =1;//semnul devine 1, deoarece numarul este pozitiv
    for(i=u; i<strlen(s); i++)
        a[i-u]=s[strlen(s)-i-1+u]-'0';//in functie de primul caracter din sir numarul este procesat in forma de int, astfel incat fiecare spatiu din vector sa contina o cifra a numarului
    n=n-u;//daca semnul este negativ, atunci si n, care reprezinta numarul de elemente este mai mic cu o unitate
}
BigInt::BigInt(int x)//constructorul ce are ca parametru un int
{
    n=0;//numarul de cifre ale numarului este initilizat cu 0
    if(x<0)
        semn=-1;// daca numarul este mai mic ca 0, atunci semnul devine negativ
    else
        semn=1;// daca numarul este mai mare egal ca 0, atunci semnul devine pozitiv
    int y=x;//se face o copie pentru x
    while(y!=0)//se determina numarul de cifre al copiei
    {
        n++;
        y=y/10;
    }
    a=new int[n];//se aloca spatiul necesar numarului
    n=0;
    while(x!=0)//este creat numarul intr-o forma ce ofera accesibilitate in vederea efectuarii operatiilor cu numee mari
    {
        a[n]=x%10;
        if(a[n]<0)
            a[n]=0-a[n];
        x=x/10;
        n++;
    }
}
ostream& operator<<(ostream& os, const BigInt& dt)//supraincarcarea afisarii
{
    if(dt.semn==-1)//daca semnul are valoarea -1 atunci se afiseaza un - in fata, deoarece numarul este negativ
        cout<<"-";
    for(int i=dt.n-1; i>=0; i--)//se parcurge numarul in ordine inversa, deoarece acesta este memorat pe dos in memorie
        os << dt.a[i];//se afiseaza cifra cu cifra
   //cout<<endl;//se trece pe urmatorul rand pentru vizibilitate
    return os;
}
istream& operator>>(istream& is, BigInt& dt)//supraincarcarea citirii
{
    int u=0;//variabila ce indica daca numarului este negativ
    char *s=new char[1000];//se aloca un spatiu mare pentru un sir s, deoarece nu se stie cat de lung va fi cuvantul
    is>>s;//se citeste sirul s
    dt.n=strlen(s);//i se atribuie obiectului in n lungimea s
    int i=0;//se initializeaza o variabila i ce va fi folosita pe ost de contor
    dt.a=new int[strlen(s)+1];//se aloca spatiu pentru viitorul cuvant modelat in memorie
    if(s[0]=='-')
    {
        dt.semn=-1;//daca primul caracter este -, atunci si semnul obiectului devine negativ
        u=1;//se retine faptul ca numarul este un numar negativ
    }
    else
        dt.semn =1;//deoarece primul caracter nu este -, atunci semnul obiectului este pozitiv
    for(i=u; i<strlen(s); i++)
        dt.a[i-u]=s[strlen(s)-i-1+u]-'0';//se creaza numarul in memorie in ordine inversa ex.(1234 va fi 4321)
    dt.n=dt.n-u;//daca valoarea citit a fost negativa, atunci din n se scade 1 element pentru a fi in conformitate cu numarul de cifre ale numarului
    delete []s;//se dezaloca s
    return is;
}
BigInt::BigInt(const BigInt &c)//constructirul de copiere
{
    n=c.n;//se copiaza numarul de elemente din vectorul ce contine ciferele numarului
    semn=c.semn;//se copiaza semnul
    a=new int[n];//se aloca memoria
    for(int i=0; i<n; i++)
        a[i]=c.a[i];//se copiaza cifra cu cifra
}
void BigInt::Show()//aceasta metoda a fost folosita provizoriu si nu se afla printre cerintele proiectului
{
    if(semn==-1)
        cout<<"-";
    for(int i=n-1; i>=0; i--)
        cout<<a[i]<<" ";
    cout<<endl<<"n="<<n<<endl;
    cout<<"semn="<<semn<<endl;
}
int BigInt::Suma()//metoda ce calculeaza suma cifrelor numarului
{
    int s=0;//se ia o variabila s in care se va calcula suma si i se atribuie valoarea 0
    for(int i=0; i<n; i++)
        s=s+a[i];//se aduna s cu fiecare cifra a numarului
    return s;//se returneaza suma
}
void BigInt::Paritate()//metoda ce afiseaza daca un numar este par sau impar
{
    if(a[0]%2==0)//daca prima cifra din vector ce corespunde cu ultima cifra din numar este para, atuncti se afiseaza faptul ca numarul este par
        cout<<"\nNumarul este par \n";
    else//in celalat caz numarul este impar
        cout<<"\nNumarul este impar \n";
}
void BigInt::Verif_Palindrom()//metoda ce verifica daca un numar este palindrom sau nu
{
    int ok=1;//variabila ce indica daca numarul este palindrom dau nu
    for(int i=0; i<n/2; i++)//se parcurge numarul pana la jumatate si se compara cu simetricul
        if(a[i]!=a[n-1-i])
            ok=0;
    if(ok)//daca valoarea lui ok nu se schimba atunci numarul este palindrom
        cout<<"\nPalindrom\n";
    else
        cout<<"\nNu este palindrom\n";

}
void BigInt::Putere(int x)
{
    if(x==0)//daca puterea este 0,atunci numarul la x va fi 1
        cout<<endl<<"Puterea este 1\n"<<endl;
    else if(x==1)//daca puterea e 1, atunci numarul ramane neschimbat
        cout<<"Numarul la puterea 1 este el insusi\n";
    else if(n==0&&a[0]==0)//daca numarul este 0 atunci va fi el insusi la orice putere
        cout<<"Numarul 0 e acelasi la orice putere\n";
    else
    {
        int *c=new int[n*2],k,*p=new int[n*2];
        /*
        -In c se vor retine valorile in urma combinarii dintre inmultirea precedenta+ inmultirea actuala
        -In p se va copia c pentru urmatoarea ridicare la o noua putere
        Nu prea ma pricep sa explic asta
        123X
        123
        ---
          369 c[0]=9     c[1]=6           c[2]=3
         246  c[0]=9+0=9 c[1]=6+6=12%10=2 c[2]=1+3+4=8       c[3]=2
        123   c[0]=9+0=9 c[1]=2+0=2       c[2]=8+3=11%10=1   c[3]=2+2+1=5 c[4]=1
        ----
        15129 <- p va lua aceasta valoare,iar c se va reinitializa cu 0
        */
        for(k=0; k<n*2; k++)
        {
            if(k<n)
                p[k]=a[k];// p primeste valorile din a si rezpectiv 0
            else
                p[k]=0;
            c[k]=0;// vlorile din c devin 0
        }
        int i=0;//se initializeaza un contor i si o valoare t care va reprezenta transportul necesar in inmultire , deoarece o sa existe si valori cu 2 cifre
        x--;//puterea scade deoarece se considera ca s-a ridicat deja numarul odata la puterea 1 cand p a primit valorile din a
        int n1=n;//n1 reprezinta lungimea numarului ridicat la putere
        while(i<x)//cat timp nu am terminat de ridicat la putere
        {
            int j=0,t=0;//j este celalalt contor ce va parcurge p in care se afla numarul dupa ce a fost ridicat la i+1
            while(j<n1)
            {
                k=0;//k este contorul cu care va fi parcurs numarul ce trebuie ridicat la o putere
                t=0;//transortul devine 0 dupa iecare parcurgere cu ridicare la putere
                while(k<n)//se parcurge numarul initial care trebuie ridicat la putere
                {
                    c[j+k]=c[j+k]+p[j]*a[k]+t;//cout<<"cf["<<j+k<<"]="<<c[j+k]<<endl<<"p["<<j<<"]"<<"="<<p[j]<<"   a["<<k<<"]"<<"="<<a[k]<<"   t="<<t<<endl;
                    //in c[k+j] se face inmultirea celor doua cifre si se aduna cu transportul
                    t=c[j+k]/10;//transportul devine c[j+k] / 10 , astfel incat in cazul valorilor de 2 cifre t sa ia valoarea corespunzatoare in vederea unei adunari corecte
                    c[j+k]=c[j+k]%10;//in cazul in care c[j+k] are mai mult de o cifra, acesta trebuie sa revina la o valoare corespunzatoare
                    k++;//contorul creste
                }
                if(t>0)
                {
                    c[j+k]=t;//daca t nu este 0 atunci numarul s-a mai marit cu o cifra
                    //n1++;
                }
                j++;//contorul creste
            }

            if(c[j+k]!=0)//in functie de cate numere sunt valoarea lui n se actualizeaza
                n1=j+k+1;
            else
                n1=j+k;
            int *copie1=new int[n1+n+1];//se initializeaza 2 vectori pentru realocare
            int *copie2=new int[n1+n+1];
            for(k=0; k<=n1+n; k++)
            {
                if(k<n1-1)
                    copie1[k]=c[k];//in prima copie se copiaza c
                else
                    copie1[k]=0;//si dupa ce s-a trecut de n se face 0
                copie2[k]=0;
            }
            delete []c;//se dezaloca c
            delete []p;//se dezaloca p
            c=copie2;//c pointeaza spre copia initializata cu 0
            p=copie1;//p pointeaza spre copia ce il contine numarul trecut deja prin cateva ridicari la putere
            i++;//contorul creste indicand ca s-a mai ridicat la o putere
        }
        cout<<endl<<"Numarul ridicat la puterea "<<x+1<<" este: ";
        if((x+1)%2!=0&&semn==-1)//daca puterea nu e para,iar semnul numarului este -1 atunci se scrie un - in fata
            cout<<"-";
        int ok=1;//contor ce inidca daca un 0 trebuie scris sau nu
        for(int z=n1-1; z>=0; z--)
        {
            if(ok==1&&p[z]==0);//se foloseste pentru a nu scrie 0-urile din fata
            else
            {
                cout<<p[z];
                ok=0;
            }
        }
        delete []c;//dezalocarea lui c
        delete []p;//dezalocarea lui p
        cout<<endl;
    }
}
BigInt BigInt::operator=(const BigInt& op2)//overload pe =
{
    n = op2.n;//n primeste numarul de cifre din op2.n
    semn=op2.semn;//se copiaza semnul din op2
    delete []a;//se dezaloca ce exista deja in a
    int *u=new int[n+1];//se aloca un nou vector cu n+1 spatii
    a=u;//a pointeaza spre valorile continute in u
    for(int i=0; i<n; i++)
        a[i]=op2.a[i];//valorile din a primesc valorile din op2
    return *this;
}
BigInt BigInt::operator = (char *s)//la fel ca la constructorul cu parametru sir de caractere
{
    int i=0,u=0;
    n=strlen(s);
    a=new int[strlen(s)+1];
    if(s[0]=='-')
    {
        semn=-1;
        u=1;
    }
    else
        semn =1;
    for(i=u; i<strlen(s); i++)
        a[i-u]=s[strlen(s)-i-1+u]-'0';
    n=n-u;
    return *this;
}
BigInt BigInt::operator = (int x)//la fel ca la cosntructirul cu un paramatru de tip int
{
    n=0;
    if(x<0)
        semn=-1;
    else
        semn=1;
    int y=x;
    while(y!=0)
    {
        n++;
        y=y/10;
    }
    if(x==0)
    {
        a=new int[1];
        a[0]=0;
        n=1;
    }
    a=new int[n];
    n=0;

    while(x!=0)
    {

        a[n]=x%10;
        if(a[n]<0)
            a[n]=0-a[n];
        x=x/10;
        n++;
    }
    return *this;
}
BigInt BigInt::operator+(const BigInt &op2)//overload pe + pentru adunarea celor 2 numere
{
    BigInt temp;//se creaza un obiect temporar
    int t=0,i;//se declara transportul si un contor
    temp.a=new int[max(n,op2.n)+2];//se aloca in a maximul dintre n si op2.n in vederea obtinerii unei marimi corecte a vectorului
    if(semn==op2.semn)//daca operatorii de semn sunt egali atunci se efectueaza simpla adunare
    {
        for( i=0; i<n&&i<op2.n; i++)//se merge pana la cel mai mic numar de numere
        {
            temp.a[i]=a[i]+op2.a[i]+t;//se aduna cifrele intre ele , iar apoi se aduna cu transportul
            t=temp.a[i]/10;//daca temp.a[i] este mai mare de o cifra , atunci transportul devine 1
            temp.a[i]=temp.a[i]%10;//daca temp.a[i] este mai mare de 2 cifre acesta trebuie modelat astfel incat sa ramana cu o singura cifra
        }
        if(op2.n<n)//daca op2.n este mai mic ca n , inseamna ca nu au fost parcurse cifrerele intregului obiect, asa ca se mai aduna la temp.a[i]
        {
            for(int k=i; k<n; k++)//la fel ca la prima adunare
            {
                temp.a[k]=a[k]+t;
                t=temp.a[k]/10;
                temp.a[k]=temp.a[k]%10;
            }
            if(t!=0)//daca transportul ramane 1 , atunci mai avem o cifra in numar care trebuie adaugata
            {
                temp.a[n]=1;
                n++;
            }
            temp.n=n;//pentru ca n este mai mare decat op2.n, atunci si temp.n va avea valoarea lui n
        }
        else// la fel ca mai sus, numai ca in acest caz op2.n este mai mare ca n asa ca se folosesc valorile din op2
        {
            for(int k=i; k<op2.n; k++)
            {
                temp.a[k]=op2.a[k]+t;
                t=temp.a[k]/10;
                temp.a[k]=temp.a[k]%10;
            }
            int xp=op2.n;
            if(t!=0)
            {
                temp.a[n]=1;
                xp++;
            }
            temp.n=xp;
        }
        temp.semn=semn;//pentru ca amblele numere au acelas semn si temp.n va lua valoarea scestuia
    }
    else //cand semnele sunt diferite atunci intervine operatia de scadere
    {
        int ok=0,u=n-1,p=op2.n-1;//ok stabileste care dintre numere este mai mare in caz ca eleau acelas numar de cifre
        if(u==p)//daca amble obiecte au un numar de numere egale se decide care este mai mare
        {
            while(a[u]==op2.a[u])
            {
                u--;
            }
            if(a[u]<op2.a[u])//daca obiectul 2 contin un numar mai mare decat cel din primul , atunci ok devine -1, altfel 1
                ok=-1;
            else
                ok=1;
        }
        if(op2.n<n||(op2.n==n&&ok==1))//daca numarul din op2<decat cel din primul obiect atuncti se efectueaza scaderea din numarul memorat in a
        {
            for(i=0; i<op2.n; i++)//deoarece numarul din obiectul 2 este mai mic se merge pana la cate numere sunr in el
            {

                temp.a[i]=a[i]-op2.a[i]+t;
                if(temp.a[i]<0)//daca numarul obtinut in urma scaderii celor 2 cifre e mai mic decat 0
                {
                    t=-1;//transportul devine -1
                    temp.a[i]=10+temp.a[i];//numarul trebuie sa ajunga la o forma pozitiva
                }
                else
                    t=0;//pe alt caz transportul devine 0 pentru ca nu este nevoie de el
            }
            for(int k=i; k<n; k++)//se completeaza numarul cu ce a ramas in cel mai mare dintre ele daca este cazul
            {
                temp.a[k]=a[k]+t;
                if(temp.a[i]<0)
                {
                    t=-1;
                    temp.a[i]=10+temp.a[i];
                }
                else
                    t=0;
            }
            temp.n=n;
            temp.semn=semn;//numarul cu semn mai mare domina
            if(temp.a[n-1]==0)//cat timp avem valori de 0 in fata numarul de numere continute de a scade
                temp.n--;
        }
        else//la fel ca in cazul precedent, numai ca op2 si obiectul 1 sunt inversati
        {
            for(i=0; i<n; i++)
            {
                temp.a[i]=op2.a[i]-a[i]+t;
                if(temp.a[i]<0)
                {
                    t=-1;
                    temp.a[i]=10+temp.a[i];
                }
                else
                    t=0;
            }
            for(int k=i; k<op2.n; k++)
            {
                temp.a[k]=op2.a[k]+t;
                if(temp.a[i]<0)
                {
                    t=-1;
                    temp.a[i]=10+temp.a[i];
                }
                else
                    t=0;
            }
            temp.n=op2.n;
            temp.semn=op2.semn;
            while(temp.a[temp.n-1]==0&&temp.n!=0)
                temp.n--;
        }
    }
    while(temp.a[temp.n-1]==0&&temp.n!=0)//se curata numarul de 0-uri inutile
        temp.n--;
    if(temp.n==0)//daca numarul de numere a ajuns sa fie 0 in urma curatarii, atunci cele 2 obiecte contineau numere cu valori gale asa ca temp trebuie sa fie aiba parametrii in conformitate
    {
        temp.a[0]=0;
        temp.n=1;
        semn=1;
    }
    return temp;
}
BigInt BigInt::operator-(const BigInt &op2)//overload pe -
{
    //prima parte este la fel ca la adunare
    BigInt temp;
    int t=0,i;
    temp.a=new int[max(n,op2.n)+2];
    if(semn!=op2.semn)//daca semnele sunt diferite adunci se executa adunarea precum in algoritmul anterior
    {
        for( i=0; i<n&&i<op2.n; i++)
        {
            temp.a[i]=a[i]+op2.a[i]+t;
            t=temp.a[i]/10;
            temp.a[i]=temp.a[i]%10;
        }
        if(op2.n<n)
        {
            for(int k=i; k<n; k++)
            {
                temp.a[k]=a[k]+t;
                t=temp.a[k]/10;
                temp.a[k]=temp.a[k]%10;
            }
            if(t!=0)
            {
                temp.a[n]=1;
                n++;
            }
            temp.n=n;
        }
        else
        {
            for(int k=i; k<op2.n; k++)
            {
                temp.a[k]=op2.a[k]+t;
                t=temp.a[k]/10;
                temp.a[k]=temp.a[k]%10;
            }
            if(t!=0)
            {
                temp.a[n]=1;
                temp.n=op2.n+1;
            }
            else
                temp.n=op2.n;
        }
        //aici se face o discutie speciala pentru semn
        if(n>op2.n&&op2.semn==1)
            temp.semn=-1;
        else if(n<op2.n&&op2.semn==-1)
            temp.semn=1;
        else if(n>op2.n&&op2.semn==-1)
            temp.semn=1;
        else if(n<op2.n&&op2.semn==1)
            temp.semn=-1;
        else
            temp.semn=semn;
    }
    else
    {
        int u=n,ok=0;
        if(op2.n==n)
        {
            while(ok==0&&u>=0)
            {
                if(op2.a[u]<a[u])
                    ok=1;
                else if (op2.a[u]>a[u])
                    ok=-1;
                u--;
            }
        }
        else if(op2.n>n)
            ok=-1;
        else
            ok=1;
        if(ok==1&&semn==1)
            temp.semn=1;
        else if(ok==-1&&semn==1)
            temp.semn=-1;
        else if(ok==-1&&semn==-1)
            temp.semn=1;
        else
            temp.semn=-1;
        if(ok==1)
        {
            for(i=0; i<op2.n; i++)
            {
                temp.a[i]=a[i]-op2.a[i]+t;
                if(temp.a[i]<0)
                {
                    t=-1;
                    temp.a[i]=10+temp.a[i];
                }
                else
                    t=0;
            }
            for(int k=i; k<n; k++)
            {
                temp.a[k]=a[k]+t;
                if(temp.a[i]<0)
                {
                    t=-1;
                    temp.a[i]=10+temp.a[i];
                }
                else
                    t=0;
            }
            temp.n=n;
            if(ok==1&&semn==1)
                temp.semn=1;
            else if(ok==-1&&semn==1)
                temp.semn=-1;
            else if(ok==-1&&semn==-1)
                temp.semn=1;
            else
                temp.semn=-1;
            while(temp.a[temp.n-1]==0)
            {
                temp.n--;
            }
        }
        else if(ok==0)
        {
            temp.a[0]=0;
            temp.n=1;
            temp.semn=1;
        }
        else//aici incepe cazul in care semnele sunt egale ce necesita - efectuata la fel ca in metoda de adunare
        {
            for(i=0; i<n; i++)
            {

                temp.a[i]=op2.a[i]-a[i]+t;
                if(temp.a[i]<0)
                {
                    t=-1;
                    temp.a[i]=10+temp.a[i];
                }
                else
                    t=0;
            }
            for(int k=i; k<op2.n; k++)
            {
                temp.a[k]=op2.a[k]+t;
                if(temp.a[k]<0)
                {
                    t=-1;
                    temp.a[k]=10+temp.a[k];
                }
                else
                    t=0;
            }
            temp.n=op2.n;
            if(ok==1&&semn==1)
                temp.semn=1;
            else if(ok==-1&&semn==1)
                temp.semn=-1;
            else if(ok==-1&&semn==-1)
                temp.semn=1;
            else
                temp.semn=-1;
            while(temp.a[temp.n-1]==0)
            {
                temp.n--;
            }
        }
    }
    while(temp.a[temp.n-1]==0&&temp.n!=0)
        temp.n--;

    if(temp.n==0)
    {
        temp.a[0]=0;
        temp.n=1;
        semn=1;
    }
    return temp;
}
BigInt BigInt::operator*(const BigInt &op2)//overload pe *
{
    BigInt temp;// se declara un obiect temporar
    if((op2.n==1&&op2.a[0]==0)||(n==1&&a[0]==0))//acesta este cazul in care unul sau mai multe dintre obiecte contin numarul 0
    {
        temp.n=1;
        temp.a=new int();
        temp.a[0]=0;
        temp.semn=1;
        return temp;
    }
    int k;
    int *c=new int[n+op2.n+2];//se aloca spatiu intr-un c care va retine provizoriu numarul
    for(k=0; k<n+op2.n+1; k++)
        c[k]=0;//se initializeaza elementele din c cu 0
    int i=0,t=0,j=0;//se initializeaza un transport t, iar i si j vor avea rolul de contor
    int n1=n;//n1 reprezinta numarul de elemente ce vor fi retinute in c
    while(j<n)
    {
        k=0;//se incepe din nou de la inceputul celui de-al doilea numar
        t=0;//transportul devine 0, pregatindu-se pentru niste noi adunari
        while(k<op2.n)//se procedeaza la fel ca in metoda Putere definita anterior
        {
            c[j+k]=c[j+k]+op2.a[k]*a[j]+t;
            t=c[j+k]/10;
            c[j+k]=c[j+k]%10;
            k++;
        }
        if(t>0)
            c[j+k]=t;
        j++;
    }
    if(c[j+k]!=0)
        n1=j+k+1;
    else
        n1=j+k;
    temp.n=n1;
    temp.a=new int [n1+2];//se aloca suficient spatiu pentru t2
    for(i=0; i<temp.n; i++)//se copiaza numarul din c in cel din temp.a
        temp.a[i]=c[i];
    while(temp.a[temp.n-1]==0)
        temp.n--;
    if(semn==op2.semn)//semnul ia o valoare in conformitate cu conventiile matematice
        temp.semn=1;
    else
        temp.semn=-1;
    return temp;
}
BigInt BigInt::operator/(const BigInt &op2)
{
    BigInt temp;//se declara un obiect temporar
    int *z=new int[n+2],*nr=new int[n+2];//in nr va fi numarul rezultat in urma impartirii,iar in z va tot ramane temp-op2
    int u=n-1,ok=1;
    if(n==op2.n)//daca numarul de cifre din numere este egal, atunci se determina care dintre obiecte contine un numar mai mare
    {
        while(u>=0)
        {
            if(a[u]<op2.a[u])
                ok=0;
            u--;
        }
    }
    if(op2.n>n||a[0]==0&&n==1||ok==0)//daca obiectul la care se face impartirea este mai mare decat primul, atunci se returneaza direct 0
    {
        temp.a=new int();
        temp.a[0]=0;
        temp.semn=1;
        temp.n=1;
        return temp;
    }
    if(op2.a[0]==0&&op2.n==0)//daca obiectul la care se face impartirea este 0 atunci se returneaza un mesaj de eroare
    {
        cout<<"Eroare : nu se poate efectua impartirea la 0"<<endl;
        return temp;
    }
    int n1=n,i,t=0,l=1;//n1 este un numar provizoriu care se modifica dupa fiecare scadere
    for(i=0; i<n; i++)
    {
        z[i]=a[i];//se copiaza in z[i] elementele de tip a[i] din obiectul initial
        nr[i]=0;//numarul final se initializeaza cu 0
    }
    while(n1>=op2.n)//cat timp numarul este mai mare sau egal cu
    {
        int ok=0;
        nr[0]++;//numarul creste la fiecare scadere
        for(i=0; i<op2.n; i++)//se face scaderea la fel ca in overload+
        {
            z[i]=z[i]-op2.a[i]+t;
            if(z[i]<0)
            {
                t=-1;
                z[i]=10+z[i];
            }
            else
                t=0;
        }
        for(int k=i; k<n1; k++)
        {
            z[k]=z[k]+t;
            if(z[k]<0)
            {
                t=-1;
                z[k]=10+z[k];
            }
            else
                t=0;
        }
        while(z[n1-1]==0)//se elimina 0-urile care nu sunt necesare
            n1--;
        for(i=0; i<l; i++)//se aduce nr la o forma care sa permita retinera cate unei cifre
        {
            nr[i+1]=nr[i]/10+nr[i+1];
            nr[i]=nr[i]%10;
        }
        if(nr[l])//daca numarul cifrelor din nr creste, atunci si contorul dedicat lui creste
            l++;
        if(op2.n==n1)//se verifica daca am ajuns in cazul in care numarul e mai mic decat cel retinut in op2
        {
            int u=n1-1;
            int ok=0;
            while(u>-1&&ok==0)
            {
                if(z[u]<op2.a[u])
                    ok=1;
                else if(z[u]>op2.a[u])
                    break;
                u--;
            }
            if(ok)
                break;
        }
    }
    //se stabileste semnul
    if((semn==-1&&op2.semn==-1)||(semn==1&&op2.semn==1))
        temp.semn=1;
    else
        temp.semn=-1;
    temp.a=new int[l+2];//se aloca suficient spatiu
    for(i=0; i<l; i++)
        temp.a[i]=nr[i];//se copiaza componentele din nr
    temp.n=l;
    while(temp.a[temp.n-1]==0)//se elimina 0-urile
        temp.n--;
    return temp;
}
