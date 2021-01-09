


class array_of_ints {
    int data[10] = {};
public:
    int size() const { return 10; }
    int& at(int i) { return data[i]; }
};

void double_each_element(array_of_ints& arr)
{
    for (int i=0; i < arr.size(); ++i) {
        arr.at(i) *= 2;
    }
}

int main (){
    array_of_ints arr;


}
