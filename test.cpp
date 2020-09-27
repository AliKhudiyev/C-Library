#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<vector<int>*> *v1, *v2;
    v1 = new vector<vector<int>*>;
    v2 = new vector<vector<int>*>;

    vector<int>* v3 = new vector<int>;

    v3->push_back(5);

    v1->push_back(v3);
    v2->push_back(v3);

    cout<<(*(*v1)[0])[0]<<", "<<(*(*v2)[0])[0]<<endl;

    for(int i=0; i<v1->size(); ++i){
        delete (*v1)[i];
    }

    delete v1;

    for(int i=0; i<v2->size(); ++i){
        delete (*v2)[i];
    }

    delete v2;

    return 0;
}