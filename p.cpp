#include <iostream>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;

// input m n  if m! % n = 0 print it

void criba (vector <int> &v, int m){
    vector <bool> b (m + 1, true);
    
    b[0] = b[1] = false; 
    
    stack <int> p;
    p.push (1);
    p.pop ();
    

}

int main (){
    int m = 120, n = 5;
    vector <int> primos;

    long n = 0;

    criba (primos, m);
    for (int i = 0; i < primos.size (); i++)
        cout << primos[i] << endl;
    criba (v, 100);

    for (auto i: primos)
        cout << i << endl;

    return 0;
}

