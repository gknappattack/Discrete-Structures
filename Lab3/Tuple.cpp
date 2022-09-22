//
// Created by Gregory Knapp on 7/14/20.
//

#include "Tuple.h"

void Tuple::toString() const {

    for (unsigned int i = 0; i < this->size(); i++) {
        cout << this->at(i) << " ";
    }
    cout << endl;
}