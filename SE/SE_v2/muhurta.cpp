#include "nativ.h"

#include "main.h"

muhurta::muhurta(){
    cout << "Мухурта без привязки к нативу."<<endl;
};

muhurta::muhurta(nativ& nat){
    cout << "Мухурта для: "<<nat.name<<endl;
};

