#ifndef LIST_H
#define LIST_H
#include <string>
#include <sstream>

template <class T> class List;

template <class T>
class Link{
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);
	T		value;
	Link<T> *next;
	
	friend class List<T>;
	
};

template <class T>
Link<T>::Link(T val) : value(val), next(0){}

template <class T>
Link<T>::Link(T val, Link* next) : value(val), next(next){}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.val), next(source.next){}

template <class T>
class List{
public:
	List();
	List(const List<T>&);
	
	void insertion(T);
	void iFirst(T);
	int search(T);
	void update(int, T);
	void deleteAt(int);
	std::string toString() const;
	bool empty() const;
	
private:
		Link<T> *head;
		int size;

};

template <class T>
List<T>::List() : head(0), size(0){}

template <class T>
void List<T>::iFirst(T val){
	Link<T> *newLink;
	newLink = new Link<T>(val);
	newLink->next = head;
	head = newLink;
	size++;
	
}

template <class T>
void List<T>::insertion(T val){
	Link<T> *newLink, *p;
	newLink = new Link<T>(val);
	if(empty()){
		iFirst(val);
		return;
		
	}
	p = head;
	while(p->next!=0){
		p = p->next;
		
	}
	newLink->next = 0;
	p->next = newLink;
	size++;
	
}

template <class T>
void List<T>::update(int a, T val){
	Link<T> *p;
	int b = 0;
	p = head;
	if((a < 0) || (a > (size-1))){
		p->value = -1;
	}else{	
		while(b != a){
			p = p->next;
			b++;
			
		};
		p->value = val;
	}
	
}

template <class T>
int List<T>::search(T val){
	Link<T> *p;
	p = head;
	int b = 0;
	while(((p->value) != val) && (b != (size-1))){
		p = p->next;
		b++;
		
	}
	if((p->value) != val){
		b = -1;
	}
	return b;
	
}

template <class T>
void List<T>::deleteAt(int a){
	Link<T> *p;
	int b = 0;
	int aux_1, aux_2 = 0;
	p = head;
	if((a > 0) && (a < (size-1))){
		aux_1 = p->value;
		while(b != a){
			p = p->next;
			aux_2 = p->value;
			p->value = aux_1;
			aux_1 = aux_2;
			b++;
			
		}
		p = head;
		head = p->next;
		delete p;
		size--;
		
		
	}else if(a == 0){
		head = p->next;
		delete p;
		size--;
		
	}else{
		p->val = -1;
	}
	
}

template <class T>
bool List<T>::empty() const{
	return (head == 0);
	
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while(p != 0){
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
			
		}
		
		p = p->next;
		
	}
	aux << "]";
	return aux.str();
	
}

#endif