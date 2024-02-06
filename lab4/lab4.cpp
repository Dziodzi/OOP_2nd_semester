#include <iostream>
#include <string>
using namespace std;

template<class Iter, class Pred>
bool all_of(Iter start, Iter end, Pred prikol){
    while (start != end) {
        if (!prikol(*start))
            return false;
        start++;
    }
    return true;
}

template<class Iter, class Pred>
bool any_of(Iter start, Iter end, Pred prikol){
    while (start != end) {
        if (prikol(*start))
            return true;
        start++;
    }
    return false;
}

template<class Iter, class Pred>
bool none_of(Iter start, Iter end, Pred prikol){
    while (start != end) {
        if (prikol(*start))
            return false;
        start++;
    }
    return true;
}

template<class Iter, class Pred> //(((((
bool one_of(Iter start, Iter end, Pred prikol){
    while (start != end) {
        if (!prikol(*start))
            return true;
        start++;
    }
    return false;
}

template<class Iter, class Pred>
bool is_sorted(Iter start, Iter end, Pred prikol) {
    if (start == end)
        return false;
    else {
        auto next = start;
        while (++next != end) {
            if (!prikol(*start, *next))
                return false;
            start = next;
        }
    }
    return true;
}

template<class Iter, class Pred>
bool is_partitioned(Iter start, Iter end, Pred prikol) {
    while (start != end) {
        if (!prikol(*start))
            break;
        start++;
    }
    while (start != end) {
        if (prikol(*start))
            return false;
        start++;
    }
    return true;
}

template<class Iter, class Pred>
auto find_not(Iter start, Iter end, const Pred& prikol) {
    while (start != end) {
        if (prikol != *start)
            return start;
        start++;
    }
    return end;
}

template<class Iter, class Pred>
auto find_backward(Iter start, Iter end, const Pred& prikol) {
    auto current = end;
    while (current != start) {
        current--;
        if (*current == prikol)
            return current;
    }
    return end;
}

template<class Iter, class Pred>
bool is_palindrome(Iter start, Iter end, Pred prikol) {
    auto current = end;
    while((start != end) && (start != current)){
        end--;
        if(!prikol(*start, *end))
            return false;
        start++;
    }
    return true;
}

int pred_1 (int x) {
    if (x%2 == 0)
        return 1;
    else
        return 0;
}

int pred_2 (int x, int y) {
    if (x >= y)
        return 1;
    else
        return 0;
}

auto pred_3 = 5;


int main () {
    setlocale(LC_ALL, "Russian");
    int array[] = {22, 8, 14, 88};
    auto pred_3a = *find_backward(array, array + 3, pred_3);
    if (pred_3a == pred_3)
        cout << "ћда, братан, ничего не вышло - каков программист, таков и его array на вход";
    else
        cout << pred_3a;
}
