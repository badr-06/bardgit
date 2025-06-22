#include <iostream>
#include <cassert>

class Stack {

    int size;
    int array[10];

    public:
        void reset() {
            if(size){
                for(int &to : array){
                    to = 0;
                }
            }
        }
        bool push(const int X){
            bool res = false;
            if(size <= 10){
                array[size] = X;
                res = true;
                size++;
            }
            return res;
        }
        void pop(){
            assert(size != 0);
            array[size] = 0;
            size--;
        }
        void print(){
            std::cout << "( " ;
            for(int i = 0; i < size; ++i){
                std::cout << array[i] << ' ';
            }
            std::cout << " )" << '\n';
        }
};

int main()
{
    int a = 2;
    static_assert(a != 2);
	Stack stack;
	stack.reset();
 
	stack.print();
 
	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();
 
	stack.pop();
	stack.print();
 
	stack.pop();
	stack.pop();
 
	stack.print();
 
	return 0;
}