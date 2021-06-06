template<class Q>
class CircularBuffer {

private:
    Q *arr;
    Q *first;
    Q *last;
    Q *younger;
    Q *elder;
    int capacity = 0;

public:
    CircularBuffer(){};
//+1 ÿ÷åéêà, õîòÿ áû 1 ìåæäó Ýëäåð è ßíãåð
    explicit CircularBuffer(int size):  arr(new Q[size]), first(&arr[0]),  last(&arr[size - 1]), younger(&arr[0]), elder(&arr[0]), capacity(size){}
//Êîíñòðóêòîð
    void push_front(const Q &value) {
        *younger = value;
        if (first == younger)
            younger = last;
        else
            younger--;
    }

    void push_back(const Q &value) {
        *elder = value;
        if (last == elder)
            elder = first;
        else
            elder++;
    }
//Äåñòðóêòîð
    void pop_front() {
        *younger = 0;
        if (younger == last)
            younger = first;
        else
            younger++;
    }

    void pop_back() {
        *elder = 0;
        if (elder == first)
            elder = last;
        else
            elder--;
    }

    Q& first_index() const {
            return *younger;
    }

    Q& last_index() const {
            return *elder;
    }

    Q& operator[](int z) const {
        return arr[z];
    }

    void change_capacity(int z) {
        if (z > capacity) {
            int *temp = new int[z];
            for (int i = 0; i < capacity; i++) {
                temp[i] = *arr[i];
            }
            delete[] *arr;
            capacity = z;
            arr = temp;
        }
    }
};

int main() {
    return 0;
}
