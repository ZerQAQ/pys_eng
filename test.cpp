#include<cstdio>
#include<vector>

class A{
    public:
    int x;
    A(int x):x(x) {}
    void print(){
        printf("%d\n", x);
    }
};


int main(){
    void* pt = new A(1);
    return 0;
}