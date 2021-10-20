#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>
#include <math.h>

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
	int binariaReal(std::vector<T>&, int, int, int);
public:
	void ordenaBurbuja(std::vector<T>&);
	void ordenaSeleccion(std::vector<T>&);
	void ordenaMerge(std::vector<T>&);
	int busqSecuencial(std::vector<T>&, int);
	int busqBinaria(std::vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v) {
	for(int i=v.size()-1; i>0; i--){
		for(int j=0; j<i; j++){
			if(v[j]>v[j+1]){
				swap(v,j,j+1);
			}
		}
	}
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v) {
	for(int i=v.size()-1; i>=0; i--){
		int aux = 0;
		for(int j=0; j<=i; j++){
			if(v[j]>v[aux]){
				aux=j;
			}
		}
		swap(v,i,aux);
	}
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for(int i=low; i<=high; i++){
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i = low;
	int j = mid+1;
	int k = low;

	while(i<=mid && j<= high){
		if(A[i]<A[j]) {
			B[k] = A[i];
			i++;
		}else{
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if(i>mid){
		for(int i=mid; j<=high; j++){
			B[k++] = A[j];
		}
	}else{
		for(int j=low; i<=mid; i++){
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if((high-low)<1){
		return;
	}
	mid = (high+low)/2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid+1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);

}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v) {
	std::vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0, v.size()-1);
}

template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &v, int a){
	for(int i=0; i<=(v.size()-1); i++){
		if(v[i]==a){
			return i;
		}
	}
	return -1;
}

template <class T>
int Sorts<T>::binariaReal(std::vector<T> &A, int h, int l, int a){
	if(h>=l){
		int p=floor(l+(h-l)/2);
		if(A[p]==a){
			return p;
		}else if(A[p]>a){
			return binariaReal(A, p-1, l, a);
		}
		return binariaReal(A, h, p+1, a);
	}
	return -1;
}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &v, int a){
	int h=(v.size()-1);
	int l=0;
	return binariaReal(v, h, l, a);
}

#endif
