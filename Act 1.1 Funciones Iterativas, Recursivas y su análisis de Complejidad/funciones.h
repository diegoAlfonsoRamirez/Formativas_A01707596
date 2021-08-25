#ifndef FUNCIONES_H
#define FUNCIONES_H

class Funciones{
    public:
        Funciones();
        int sumaIterativa(int a);
        int sumaRecursiva(int a);
        int sumaDirecta(int a);
};

Funciones::Funciones(){}

int Funciones::sumaIterativa(int a){
    int n=0;
    for(int i=1; i<=a; i++){
        n+=i;
    }
    return n;
}

int Funciones::sumaRecursiva(int a){
    if(a==0){
        return 0;
    }else{
        return (a+sumaRecursiva(a-1));
    }
}

int Funciones::sumaDirecta(int a){
    return ((a*(a+1))/2);
}

#endif