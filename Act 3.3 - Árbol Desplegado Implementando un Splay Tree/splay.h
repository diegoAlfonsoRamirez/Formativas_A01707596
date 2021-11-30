#ifndef SPLAY_H_
#define SPLAY_H_

#include <string>
#include <sstream>

template <class T> class SplayTree;

template <class T>
class Node{
private:
	T value;
	Node *left, *right, *parent;
	unsigned int count;
	Node<T>* succesor();
	Node<T>* zag(Node<T>*);
	Node<T>* zig(Node<T>*);

public:
	Node(T);
	Node(T,Node<T>*,Node<T>*,Node<T>*);
	Node<T>*add(T);
	Node<T>*find(T);
	Node<T>*remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void print_tree(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*,Node<T>*);

	friend class SplayTree<T>;
	
};

template <class T>
Node<T>::Node(T val): value(val),left(0),right(0),parent(0){}

template <class T>
Node<T>::Node(T val,Node<T> *le,Node<T> *ri,Node<T> *p) : value(val),left(le),right(ri),parent(p){}

template <class T>
Node<T>* Node<T>::add(T val){
	if(val < value){
		if(left != 0){
			return left->add(val);
			
		}else{
			left = new Node<T>(val);
			left->parent = this;
			return left;
			
		}
		
	}else{
		if(right != 0){
			return right->add(val);
			
		}else{
			right = new Node<T>(val);
			right->parent = this;
			return right;
			
		}
		
	}
	
}

template<class T>
Node<T>* Node<T>::find(T val){
	if(val == value){
		return this;
		
	}else if(val < value){
		if(left != 0){
			return left->find(val);
			
		}else{
			return this;
			
		}
		
	}else if (val > value){
		if(right != 0){
			return right->find(val);
		
		}else{
			return this;
			
		}
		
	}
	
	return 0;
	
}

template<class T>
Node<T>* Node<T>::succesor(){
	Node<T> *le, *ri;
	le = left;
	ri = right;
	if(right == 0){
		if(left != 0){
			left = 0;
			
		}if(le){
			le->parent = 0;
			
		}
		return le;
		
	}
	
	if(right->left == 0){
		right = right->right;
		if(right){
			right->parent = parent;
		}
		
		if(ri){
			ri->right = 0;
			ri->parent = 0;
		}
		
		return ri;
	}
	
	Node<T> *p, *c;
	p = right;
	c = right->left;
	while(c->left != 0){
		p = c;
		c = c->left;
		
	}
	p->left = c->right;
	if(p->left != 0){
		p->left->parent = p;
		
	}
	
	c->right = 0;
	return c;
	
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *succ, *old;
	if (val < value){
		if (left != 0){
			if (left->value == val){
				old = left;
				if(old->left != 0 && old->right != 0){
					succ = left->succesor();
					if (succ != 0){
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left){
							succ->left->parent = succ;
							
						}
						if(succ->right){
							succ->right->parent = succ;
							
						}
						
					}
					
					left = succ;
				}else if(old->right != 0){
					old->right->parent = left->parent;
					left = old->right;

				}else if(old->left != 0){
					old->left->parent = left->parent;
					left = old->left;
					
				}else{
					left = 0;
					
				}
				
				delete old;
				return this;
				
			}else{
				return left->remove(val);
				
			}
		}
		
	}else if(val > value){
		if(right != 0){
			if(right->value == val){
				old = right;
				if(old->left != 0 && old->right != 0){
					succ = right->succesor();
					if(succ != 0){
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						
						if(succ->left){
							succ->left->parent = succ;
							
						}
						if(succ->right){
							succ->right->parent = succ;
							
						}
					}
					right = succ;
				}else if(old->right != 0){
					old->right->parent = right->parent;
					right = old->right;
					
				}else if(old->left != 0){
					old->left->parent = right->parent;
					right = old->left;
					
				}else{
					right = 0;
					
				}
				delete old;
				return this;
				
			}else{
				return right->remove(val);
				
			}
		}
	}
	return this;
	
}

template<class T>
void Node<T>::removeChilds(){
	if(left != 0){
		left->removeChilds();
		delete left;
		left = 0;
		
	}
	if(right != 0){
		right->removeChilds();
		delete right;
		right = 0;
		
	}
}

template <class T>
Node<T>* Node<T>::zag(Node<T>* a){
	Node<T> *b = a->left;
	a->left = b->right;
	if(b->right)
		b->right->parent = a;
	b->right = a;
	b->parent = a->parent;
	a->parent = b;
	if(b->parent){
		if(b->parent->left && b->parent->left->value == a->value)
			b->parent->left = b;
		else
			b->parent->right = b;
	}
	return b;
}

template<class T>
Node<T>* Node<T>::zig(Node<T>*a){
	Node<T> *b = a->right;
	a->right = b->left;
	if(b->left)
		b->left->parent = a;
	b->left = a;
	b->parent = a->parent;
	a->parent = b;
	if(b->parent){
		if(b->parent->left && b->parent->left->value == a->value){
			b->parent->left = b;
		
		}else{
			b->parent->right = b;
			
		}
		
	}
	return b;
	
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if(left != 0){
		left->inorder(aux);
		
	}
	if(aux.tellp() != 1){
		aux<<" ";
		
	}
	aux<<value;
	if(right != 0){
		right->inorder(aux);
		
	}
}

template<class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* a){
	while(a->parent != 0){
		if(a->parent->value == root->value){
			if(a->parent->left && a->parent->left->value == a->value){
				zag(a->parent);
			}
            else{
				zig(a->parent);
			}
		}
        else{
			Node<T>*p = a->parent;
			Node<T>*g = p->parent;
		if(p->left && g->left && a->value == p->left->value && p->value == g->left->value){
				zag(g);
				zag(p);
				
			}else if(p->right && g->right && a->value == p->right->value && p->value == g->right->value){
				zig(g);
				zig(p);
				
			}else if(p->left && g->right && a->value == p->left->value && p->value == g->right->value){
				zag(p);
				zig(g);
				
			}else{
				zig(p);
				zag(g);
				
			}
		}
	}
	return a;
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}
    else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const{
	aux << value;
	if(left != 0){
		aux << " ";
		left->preorder(aux);
		
	}
	if(right != 0){
		aux << " ";
		right->preorder(aux);
		
	}
	
}

template<class T>
class SplayTree{
private:
	Node<T> *root;
	int count;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	int size() const;
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree():root(0){
	count = 0;
}

template<class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template<class T>
bool SplayTree<T>::empty() const{
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val){
	if(root !=0){
		Node<T>* added = root->add(val);
		root = root->splay(root, added);
	}
    else{
		root = new Node<T>(val);
	}
	count++;
}

template<class T>
bool SplayTree<T>::find(T val){
	if(root != 0){
		Node<T>* found = root->find(val);
		if(found == 0){
			return false;
			
		}
		root = root->splay(root, found);
		return(root->value == val);
		
	}else{
		return false;
		
	}
}

template<class T>
void SplayTree<T>::removeAll(){
	if(root != 0){
		root->removeChilds();
		
	}
	delete root;
	root = 0;
	count = 0;
}

template<class T>
void SplayTree<T>::remove(T val){
	if(root != 0){
		if(val == root->value){
			Node<T> *succ = root->succesor();
			
			if(succ != 0){
				succ->left = root->left;
				succ->right = root->right;
				succ->parent = 0;
				
				if(succ->left){
					succ->left->parent = succ;
					
				}
				if(succ->right){
					succ->right->parent = succ;
					
				}
			}
			delete root;
			root = succ;
		}else {
			Node<T>*p = root->remove(val);
			if (p != 0){
				root = root->splay(root, p);
				
			}
			
		}
	}
	count--;
}

template <class T>
int SplayTree<T>::size() const{
	return count;
}

template<class T>
std::string SplayTree<T>::inorder() const{
	std::stringstream aux;
	aux<<"[";
	if(!empty()){
		root->inorder(aux);
	}
	aux<<"]";
	return aux.str();
}

template<class T>
std::string SplayTree<T>::print_tree() const{
	std::stringstream aux;
	aux<<"\n ====================== ";
	if(!empty()){
		root->print_tree(aux);
	}
	aux<<" ==================== \n";
	return aux.str();
}

template<class T>
std::string SplayTree<T>::preorder() const{
	std::stringstream aux;
	aux<<"[";
	if(!empty()){
		root->preorder(aux);
	}
	aux<<"]";
	return aux.str();
}

#endif