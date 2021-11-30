#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <iostream>
#include <string>
#include <sstream>

template<class Key, class Value>
class Quadratic{
private:
    unsigned int (*func)(const Key);

    unsigned int size;
    unsigned int count;
    Key *keys;
    Key initialValue;
    Value *values;

    long indexOf(const Key) const;

public:
    Quadratic(unsigned int, const Key, unsigned int (*)(const Key));
    ~Quadratic();
    bool full() const;
    bool put(const Key, const Value);
    bool contains(const Key) const;
    Value get(const Key) const;
    std::string toString() const;
};

template<class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int size, const Key initialValue, unsigned int (*func)(const Key)) {
    this->size = size;
    this->keys = new Key[size];
    if(keys == nullptr){
		std::cout << "Out of memory." << std::endl;
		
	}
    this->initialValue = initialValue;
    for(unsigned int i = 0; i < size; i++){
        this->keys[i] = initialValue;
		
    }
    values = new Value[size];
    if(values == nullptr){
		std::cout << "Out of memory." << std::endl;
		
	}
    for(int i = 0; i < size; i++){
        this->values[i] = 0;
		
    }
    this->func = func;
    this->count = 0;
	
}

template<class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
    delete[] keys;
    delete[] values;
    keys = nullptr;
    values = nullptr;
    func = nullptr;
    size = 0;
    count = 0;
	
}

template<class Key, class Value>
bool Quadratic<Key, Value>::full() const {
    return (count > size);
	
}

template<class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key key) const {
    unsigned int i, start;
    start = i = func(key) % size;
    for(int j = 0; j < size; j++){
        if(keys[i] == key){
			return i;
			
		}
        i = (start + j * j) % size;
    }
    return -1;
	
}

template<class Key, class Value>
bool Quadratic<Key, Value>::put(const Key key, const Value value) {
    unsigned i, start;
    long pos;
    pos = indexOf(key);
    if(pos != -1){
        values[pos] = value;
        return true;
		
    }
    start = i = func(key) % size;
    for(int j = 0; j < size; j++){
        if(keys[i] == initialValue){
            keys[i] = key;
            values[i] = value;
            return true;
			
        }
        i = (start + j * j) % size;
		
    }
    return false;
	
}

template<class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key key) const {
    return indexOf(key) != -1;
	
}

template<class Key, class Value>
Value Quadratic<Key, Value>::get(const Key key) const {
    long pos = indexOf(key);
    if(pos != -1){
		return values[pos];
		
	}
    return 0;
	
}

template<class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
    std::stringstream aux;
    for(int i = 0; i < size; i++){
        if(keys[i] != initialValue){
            aux << "(" << i << " ";
            aux << keys[i] << " : " << values[i] << ") ";
			
        }
		
    }
    return aux.str();
	
}

#endif 