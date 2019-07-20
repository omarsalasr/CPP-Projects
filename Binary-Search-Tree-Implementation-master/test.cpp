#include <iostream>
#include "bst.h"


int main(){
    int x;
    int nleaves;
    int h;

    bst<int> *t = new bst<int>();

    while( (std::cin >> x)) 
        t->insert(x);

    if(t->size() <= 20) {
      t->inorder();
	    t->preorder();
	    t->postorder();
    }

    std::vector<int> *vec;
    vec = t->to_vector();

    for(int i = 0; i < vec->size(); i++)
        std::cout << vec->at(i) << " ";
    std::cout << "\n";

    int z = -999;
    std::cout << "\n## ith 0:   " << t->get_ith(0,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## ith 20:   " << t->get_ith(20,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## ith 5:   " << t->get_ith(5,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## ith 9:   " << t->get_ith(9,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## ith 4:   " << t->get_ith(4,z) << "\n";
    std::cout << z << "\n";

    std::cout << "\n## --ith 0:   " << t->get_ith_SLOW(0,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## --ith 20:   " << t->get_ith_SLOW(20,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## --ith 5:   " << t->get_ith_SLOW(5,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## --ith 9:   " << t->get_ith_SLOW(9,z) << "\n";
    std::cout << z << "\n";
    std::cout << "\n## --ith 4:   " << t->get_ith_SLOW(4,z) << "\n";
    std::cout << z << "\n";



    std::cout << "\n## Range 11 89:   " << t->num_range(11,89) << "\n";
    std::cout << "\n## Range 50 12:   " << t->num_range(50,12) << "\n";
    std::cout << "\n## Range 15 98:   " << t->num_range(15,98) << "\n";
    std::cout << "\n## Range 20 20:   " << t->num_range(20,20) << "\n";
    std::cout << "\n## Range 33 33:   " << t->num_range(33,33) << "\n";

    std::cout << "\n## --Range 11 89:   " << t->num_range_SLOW(11,89) << "\n";
    std::cout << "\n## --Range 50 12:   " << t->num_range_SLOW(50,12) << "\n";
    std::cout << "\n## --Range 15 98:   " << t->num_range_SLOW(15,98) << "\n";
    std::cout << "\n## --Range 20 20:   " << t->num_range_SLOW(20,20) << "\n";
    std::cout << "\n## --Range 33 33:   " << t->num_range_SLOW(33,33) << "\n";


    std::cout << "\n## Geq 89:   " << t->num_geq(89) << "\n";
    std::cout << "\n## Geq 11:   " << t->num_geq(11) << "\n";
    std::cout << "\n## Geq 25:   " << t->num_geq(25) << "\n";

    std::cout << "\n## --Geq 89:   " << t->num_geq_SLOW(89) << "\n";
    std::cout << "\n## --Geq 11:   " << t->num_geq_SLOW(11) << "\n";
    std::cout << "\n## --Geq 25:   " << t->num_geq_SLOW(25) << "\n";


    std::cout << "\n## Leq 89:   " << t->num_leq(89) << "\n";
    std::cout << "\n## Leq 11:   " << t->num_leq(11) << "\n";
    std::cout << "\n## Leq 25:   " << t->num_leq(25) << "\n";

    std::cout << "\n## --Leq 89:   " << t->num_leq_SLOW(89) << "\n";
    std::cout << "\n## --Leq 11:   " << t->num_leq_SLOW(11) << "\n";
    std::cout << "\n## --Leq 25:   " << t->num_leq_SLOW(25) << "\n";

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";

    nleaves = t->num_leaves();
    std::cout << "\n#### Reported number of leaves:   " << nleaves  << "\n";

    delete t;
    
    return 0;
}
