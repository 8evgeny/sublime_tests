// constcast.cpp -- using const_cast<>
#include <iostream>
using std::cout;
using std::endl;

void change(const int * pt, int n);

int main()
{
    int pop1 = 38383;
    const int pop2 = 2000;

    cout << "pop1, pop2: " << pop1 << ", " << pop2 << endl;
    change(&pop1, -103);
    change(&pop2, -103);
    cout << "pop1, pop2: " << pop1 << ", " << pop2 << endl;
    // std::cin.get();
    return 0;
}

void change(const int * pt, int n)
{
    int * pc;
  
    pc = const_cast<int *>(pt);
    *pc += n;
 
}
ˌ9M���{�n3��I��-1��-"/�س�AAxn���w6V�e���wCp��]�~�$Ɲ{*(�!}$��E|�<�W���{N�'dnS���¡}���`�C��5D�'�}��w�"K�D�YG��p��Z�p��<��<���I���Q��*�8�?�T�(`����o�?�ḱ���Hմ�h��_i��ճ�O[P.�pC�үm�9��ǹN�,�N�H@� E���>0�LQͥCZ_@-O�[Ia�GVl���9\�7H�x*n�*���;9;{��Ơ��YЫf�����t	������sϓ��C�W˦ѡ>{�O���S	�U+靗�{�u n2~��L]Ѫ���G�F��r����(wÄ\l��L��%��j�����)P��T���+�����qf}�嗯z�o��A뀁��˩��a�U���h�͘X'��'��=Cx�!
��MH�X�xJȒJ6�ڧI߆/f����yv|