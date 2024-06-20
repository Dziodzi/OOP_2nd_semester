//
// Created by Gregory on 06.02.2024.
//

#include <iostream>
#include <random>
#include <string>
#include <fstream>

using namespace std;

class Cube {

protected:
    char front[3][3]{};
    char back[3][3]{};
    char top[3][3]{};
    char bottom[3][3]{};
    char left[3][3]{};
    char right[3][3]{};
    char c1{}, c2{}, c3{}, c4{}, c5{}, c6{};


//"Бегающие" квадратики на поворачивающейся грани

    static void r_switch(char a[3][3]){
        char y = a[0][0];
        a[0][0] = a[2][0];
        a[2][0] = a[2][2];
        a[2][2] = a[0][2];
        a[0][2] = y;
        char h = a[0][1];
        a[0][1] = a[1][0];
        a[1][0] = a[2][1];
        a[2][1] = a[1][2];
        a[1][2] = h;
    } //По часовой

    static void l_switch(char a[3][3]){
        char x = a[0][0];
        a[0][0] = a[0][2];
        a[0][2] = a[2][2];
        a[2][2] = a[2][0];
        a[2][0] = x;
        char t = a[0][1];
        a[0][1] = a[1][2];
        a[1][2] = a[2][1];
        a[2][1] = a[1][0];
        a[1][0] = t;
    } //Против часовой

public:
    int count = 0;
    string turns = "To build a Rubik\'s Cube from start position, you need to perform the following steps:   \n";

    explicit Cube() = default;

//Присваивание номера цвету

    void numbers() {
        c1 = bottom[1][1];
        c2 = front[1][1];
        c3 = right[1][1];
        c4 = back[1][1];
        c5 = left[1][1];
        c6 = top[1][1];
    }

//Чтение развёртки

    void file_reader () {
        ifstream fin("input.txt");
        for (auto & i : top)
            fin >> i[0] >> i[1] >> i[2];
        for (int i = 0; i < 3; i++)
           fin >> left[i][0] >> left[i][1] >> left[i][2] >> front[i][0] >> front[i][1] >> front[i][2] >> right[i][0] >> right[i][1] >> right[i][2] >> back[i][0] >> back[i][1] >> back[i][2];
        for (auto & i : bottom)
            fin >> i[0] >> i[1] >> i[2];
        }

//Вывод развёртки в файл

    void file_print() {
        ofstream fout("output.txt");
        fout << " " << endl;
        fout << "-----------------------------" << endl;
        fout << " " << endl;
        for (auto & i : top)
            fout << "       " << i[0] << " "<< i[1] << " " << i[2] << endl;
        for (int i = 0; i < 3; i++)
            fout << left[i][0] << " "<< left[i][1] << " " << left[i][2] << "  " << front[i][0] << " "<< front[i][1] << " " << front[i][2] << "  "  << right[i][0] << " "<< right[i][1] << " " << right[i][2] << "  " << back[i][0] << " "<< back[i][1] << " " << back[i][2]  << endl;
        for (auto & i : bottom)
            fout << "       " << i[0] << " "<< i[1] << " " << i[2] << endl;
        fout << " " << endl;
        fout << "-----------------------------" << endl;
        fout << " " << endl;
    }


//Вывод развёртки

    void print() {
        for (auto & i : top)
            cout << "       " << i[0] << " "<< i[1] << " " << i[2] << endl;
        for (int i = 0; i < 3; i++)
            cout << left[i][0] << " "<< left[i][1] << " " << left[i][2] << "  " << front[i][0] << " "<< front[i][1] << " " << front[i][2] << "  "  << right[i][0] << " "<< right[i][1] << " " << right[i][2] << "  " << back[i][0] << " "<< back[i][1] << " " << back[i][2]  << endl;
        for (auto & i : bottom)
            cout << "       " << i[0] << " "<< i[1] << " " << i[2] << endl;
        cout << " " << endl;
        cout << "-----------------------------" << endl;
        cout << " " << endl;
    }

//Окраска кубика в дефолтое состояние

    void color(){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                top[i][j] = 'Y';
                bottom[i][j] = 'W';
                front[i][j] = 'B';
                back[i][j] = 'G';
                left[i][j] = 'R';
                right[i][j] = 'O';
                //top[0][0] = 'Z';
                //bottom[0][0] = 'Z';
            }
        }
    }


//Повороты граней

    void six() {
        char buff[3];
        for (int i = 0; i < 3; i++) {
            buff[i] = front[0][i];
            front[0][i] = right[0][i];
            right[0][i] = back[0][i];
            back[0][i] = left[0][i];
            left[0][i] = buff[i];
        }
        r_switch(top);
        count++;
        turns += "6";
    }

    void six_() {
        char buff[3];
        for (int i = 0; i < 3; i++) {
            buff[i] = front[0][i];
            front[0][i] = left[0][i];
            left[0][i] = back[0][i];
            back[0][i] = right[0][i];
            right[0][i] = buff[i];
        }
        l_switch(top);
        count++;
        turns += "6'";
    }

    void one() {
        char buff[3];
        for (int i = 0; i < 3; i++) {
            buff[i] = front[2][i];
            front[2][i] = left[2][i];
            left[2][i] = back[2][i];
            back[2][i] = right[2][i];
            right[2][i] = buff[i];
        }
        r_switch(bottom);
        count++;
        turns += "1";
    }

    void one_() {
        char buff[3];
        for (int i = 0; i < 3; i++) {
            buff[i] = front[2][i];
            front[2][i] = right[2][i];
            right[2][i] = back[2][i];
            back[2][i] = left[2][i];
            left[2][i] = buff[i];
        }
        l_switch(bottom);
        count++;
        turns += "1'";
    }

    void three() {
        char buff[3];
        buff[0] = back[2][0];
        buff[1] = back[1][0];
        buff[2] = back[0][0];
        back[2][0] = top[0][2];
        back[1][0] = top[1][2];
        back[0][0] = top[2][2];
        top[0][2] = front[0][2];
        top[1][2] = front[1][2];
        top[2][2] = front[2][2];
        front[0][2] = bottom[0][2];
        front[1][2] = bottom[1][2];
        front[2][2] = bottom[2][2];
        bottom[0][2] = buff[0];
        bottom[1][2] = buff[1];
        bottom[2][2] = buff[2];
        r_switch(right);
        count++;
        turns += "3";
    }

    void three_() {
        char buff[3];
        buff[0] = back[2][0];
        buff[1] = back[1][0];
        buff[2] = back[0][0];
        back[2][0] = bottom[0][2];
        back[1][0] = bottom[1][2];
        back[0][0] = bottom[2][2];
        bottom[0][2] = front[0][2];
        bottom[1][2] = front[1][2];
        bottom[2][2] = front[2][2];
        front[0][2] = top[0][2];
        front[1][2] = top[1][2];
        front[2][2] = top[2][2];
        top[0][2] = buff[0];
        top[1][2] = buff[1];
        top[2][2] = buff[2];
        l_switch(right);
        count++;
        turns += "3'";
    }

    void five() {
        char buff[3];
        buff[0] = back[2][2];
        buff[1] = back[1][2];
        buff[2] = back[0][2];
        back[2][2] = bottom[0][0];
        back[1][2] = bottom[1][0];
        back[0][2] = bottom[2][0];
        bottom[0][0] = front[0][0];
        bottom[1][0] = front[1][0];
        bottom[2][0] = front[2][0];
        front[0][0] = top[0][0];
        front[1][0] = top[1][0];
        front[2][0] = top[2][0];
        top[0][0] = buff[0];
        top[1][0] = buff[1];
        top[2][0] = buff[2];
        r_switch(left);
        count++;
        turns += "5";
    }

    void five_() {
        char buff[3];
        buff[0] = back[2][2];
        buff[1] = back[1][2];
        buff[2] = back[0][2];
        back[2][2] = top[0][0];
        back[1][2] = top[1][0];
        back[0][2] = top[2][0];
        top[0][0] = front[0][0];
        top[1][0] = front[1][0];
        top[2][0] = front[2][0];
        front[0][0] = bottom[0][0];
        front[1][0] = bottom[1][0];
        front[2][0] = bottom[2][0];
        bottom[0][0] = buff[0];
        bottom[1][0] = buff[1];
        bottom[2][0] = buff[2];
        l_switch(left);
        count++;
        turns += "5'";
    }

    void two() {
        char buff[3];
        buff[0] = top[2][0];
        buff[1] = top[2][1];
        buff[2] = top[2][2];
        top[2][0] = left[2][2];
        top[2][1] = left[1][2];
        top[2][2] = left[0][2];
        left[2][2] = bottom[0][2];
        left[1][2] = bottom[0][1];
        left[0][2] = bottom[0][0];
        bottom[0][2] = right[0][0];
        bottom[0][1] = right[1][0];
        bottom[0][0] = right[2][0];
        right[0][0] = buff[0];
        right[1][0] = buff[1];
        right[2][0] = buff[2];
        r_switch(front);
        count++;
        turns += "2";
    }

    void two_() {
        char buff[3];
        buff[0] = top[2][0];
        buff[1] = top[2][1];
        buff[2] = top[2][2];
        top[2][0] = right[0][0];
        top[2][1] = right[1][0];
        top[2][2] = right[2][0];
        right[0][0] = bottom[0][2];
        right[1][0] = bottom[0][1];
        right[2][0] = bottom[0][0];
        bottom[0][2] = left[2][2];
        bottom[0][1] = left[1][2];
        bottom[0][0] = left[0][2];
        left[2][2] = buff[0];
        left[1][2] = buff[1];
        left[0][2] = buff[2];
        l_switch(front);
        count++;
        turns += "2'";
    }

    void four() {
        char buff[3];
        buff[0] = top[0][0];
        buff[1] = top[0][1];
        buff[2] = top[0][2];
        top[0][0] = right[0][2];
        top[0][1] = right[1][2];
        top[0][2] = right[2][2];
        right[0][2] = bottom[2][2];
        right[1][2] = bottom[2][1];
        right[2][2] = bottom[2][0];
        bottom[2][2] = left[2][0];
        bottom[2][1] = left[1][0];
        bottom[2][0] = left[0][0];
        left[2][0] = buff[0];
        left[1][0] = buff[1];
        left[0][0] = buff[2];
        r_switch(back);
        count++;
        turns += "4";
    }

    void four_() {
        char buff[3];
        buff[0] = top[0][0];
        buff[1] = top[0][1];
        buff[2] = top[0][2];
        top[0][0] = left[2][0];
        top[0][1] = left[1][0];
        top[0][2] = left[0][0];
        left[2][0] = bottom[2][2];
        left[1][0] = bottom[2][1];
        left[0][0] = bottom[2][0];
        bottom[2][2] = right[0][2];
        bottom[2][1] = right[1][2];
        bottom[2][0] = right[2][2];
        right[0][2] = buff[0];
        right[1][2] = buff[1];
        right[2][2] = buff[2];
        l_switch(back);
        count++;
        turns += "4'";
    }

//Перемешивание кубика

    void shuffle() {
        for (int i = 0; i < 3; i++) {
            six_();
            three_();
            two();
            six_();
            five_();
            four();
            one();
        }
   }

};

class Maker: public Cube {

public:

    bool cond1() {
        if ((c1 == bottom[0][1])  &&
                (c1 == bottom[2][1]) &&
                (c1 == bottom[1][0]) &&
                (c1 == bottom[1][2]) &&
                (c2 == front[2][1]) &&
                (c3 == right[2][1]) &&
                (c4 == back[2][1]) &&
                (c5 == left[2][1]))
                return true;
        else
            return false;
    }

    void step1() {
        int k1 = 0;
        while (!cond1()) {
            if (k1 == 3) {break;}

            else if ((c2 == front[0][1]) && (c1 == top[2][1])) {two(); two(); k1=0;}
            else if ((c3 == right[0][1]) && (c1 == top[1][2])) {three(); three(); k1=0;}
            else if ((c5 == left[0][1]) && (c1 == top[1][0])) {five(); five(); k1=0;}
            else if ((c4 == back[0][1]) && (c1 == top [0][1])) {four(); four(); k1=0;}

            else if ((c1 == front[0][1]) && (c2 == top[2][1])) {six_(); three_(); two(); three(); k1=0;}
            else if ((c1 == right[0][1]) && (c3 == top[1][2])) {six_(); four_(); three(); four(); k1=0;}
            else if ((c1 == left[0][1]) && (c5 == top[1][0])) {six_(); two_(); five(); two(); k1=0;}
            else if ((c1 == back[0][1]) && (c4 == top[0][1])) {six_(); five_(); four(); five(); k1=0;}

            else if (c1 == front[1][2]) {two_(); six_(); two(); k1=0;}
            else if (c3 == right[1][2]) {three_(); six_(); three(); k1=0;}
            else if (c5 == left[1][2]) {five_(); six_(); five(); k1=0;}
            else if (c4 == back[1][2]) {four_(); six_(); four(); k1=0;}

            else if (c1 == front[1][0]) {two(); six_(); two_(); k1=0;}
            else if (c3 == right[1][0]) {three(); six_(); three_(); k1=0;}
            else if (c5 == left[1][0]) {five(); six_(); five_(); k1=0;}
            else if (c4 == back[1][0]) {four(); six_(); four_(); k1=0;}

            else if (c1 == front[2][1]) {two(); two(); six_(); two(); two(); k1=0;}
            else if (c3 == right[2][1]) {three(); three(); six_(); three(); three(); k1=0;}
            else if (c5 == left[2][1]) {five(); five(); six_(); five(); five(); k1=0;}
            else if (c4 == back[2][1]) {four(); four(); six_(); four(); four(); k1=0;}

            else if ((c1 == bottom[0][1]) && (c2 != front[2][1])) {two(); two(); six_(); two(); two();}
            else if ((c1 == bottom[1][2]) && (c3 != right[2][1])) {three(); three(); six_(); three(); three(); k1=0;}
            else if ((c1 == bottom[1][0]) && (c5 != left[2][1])) {five(); five(); six_(); five(); five(); k1=0;}
            else if ((c1 == bottom[2][1]) && (c4 != back[2][1])) {four(); four(); six_(); four(); four(); k1=0;}

            else if (count >= 1000) {cout << count; break;}
            else {six(); k1++;}
            }
        print();
    }

    bool cond2() {
    if  ((c1 == bottom [0][0]) &&
    (c1 == bottom [0][1]) &&
    (c1 == bottom [0][2]) &&
    (c1 == bottom [1][0]) &&
    (c1 == bottom [1][2]) &&
    (c1 == bottom [2][0]) &&
    (c1 == bottom [2][1]) &&
    (c1 == bottom [2][2]) &&
    (c2 == front[2][0]) &&
    (c2 == front[2][1]) &&
    (c2 == front[2][2]) &&
    (c3 == right[2][0]) &&
    (c3 == right[2][1]) &&
    (c3 == right[2][2]) &&
    (c4 == back[2][0]) &&
    (c4 == back[2][1]) &&
    (c4 == back[2][2]) &&
    (c5 == left[2][0]) &&
    (c5 == left[2][1]) &&
    (c5 == left[2][2]))
        return true;
    else
        return false;


}

    void step2() {
        int k2 = 0;
        for (int i = 0; i < 100; i++) {
            if (k2 == 4) {break;}
            else if (cond2()) {break;}

            else if ((c2 == front[2][1]) && (c1 == front[0][2]) && (c3 == right[2][1]) && (c3 == right[0][0]) && (c2 == top[2][2])) {two_(); six_(); two(); k2=0;}
            else if ((c5 == left[2][1]) && (c1 == left[0][2]) && (c2 == front[2][1]) && (c2 == front[0][0]) && (c5 == top[2][0])) {five_(); six_(); five(); k2=0;}
            else if ((c3 == right[2][1]) && (c1 == right[0][2]) && (c4 == back[2][1]) && (c4 == back[0][0]) && (c3 == top[0][2])) {three_(); six_(); three(); k2=0;}
            else if ((c4 == back[2][1]) && (c1 == back[0][2]) && (c5 == left[2][1]) && (c5 == left[0][0]) && (c4 == top[0][0])) {four_(); six_(); four(); k2=0;}

            else if ((c2 == front[2][1]) && (c2 == front[0][2]) && (c3 == right[2][1]) && (c1 == right[0][0]) && (c3 == top[2][2])) {three(); six(); three_(); k2=0;}
            else if ((c5 == left[2][1]) && (c5 == left[0][2]) && (c2 == front[2][1]) && (c1 == front[0][0]) && (c2 == top[2][0])) {two(); six(); two_(); k2=0;}
            else if ((c3 == right[2][1]) && (c3 == right[0][2]) && (c4 == back[2][1]) && (c1 == back[0][0]) && (c4 == top[0][2])) {four(); six(); four_(); k2=0;}
            else if ((c4 == back[2][1]) && (c4 == back[0][2]) && (c5 == left[2][1]) && (c1 == left[0][0]) && (c5 == top[0][0])) {five(); six(); five_(); k2=0;}

            else if ((c2 == front[2][1]) && (c3 == front[0][2]) && (c3 == right[2][1]) && (c2 == right[0][0]) && (c1 == top[2][2])) {three(); six_(); three_(); six(); six(); three(); six(); three_(); k2=0;}
            else if ((c5 == left[2][1]) && (c2 == left[0][2]) && (c2 == front[2][1]) && (c5 == front[0][0]) && (c1 == top[2][0])) {two(); six_(); two_(); six(); six(); two(); six(); two_(); k2=0;}
            else if ((c3 == right[2][1]) && (c4 == right[0][2]) && (c4 == back[2][1]) && (c3 == back[0][0]) && (c1 == top[0][2])) {four(); six_(); four_(); six(); six(); four(); six(); four_(); k2=0;}
            else if ((c4 == back[2][1]) && (c5 == back[0][2]) && (c5 == left[2][1]) && (c4 == left[0][0]) && (c1 == top[0][0])) {five(); six_(); five_(); six(); six(); five(); six(); five_(); k2=0;}

            else if ((c2 == front[2][1]) && (c1 == front[2][2]) && (c3 == right[2][1])) {two_(); six_(); two(); k2=0;}
            else if ((c5 == left[2][1]) && (c2 == front[2][1]) && (c1 == left[2][2])) {five_(); six_(); five(); k2=0;}
            else if ((c1 == right[2][2]) && (c3 == right[2][1]) && (c4 == back[2][1])) {three_(); six_(); three(); k2=0;}
            else if ((c4 == back[2][1]) && (c5 == left[2][1]) && (c1 == back[2][2])) {four_(); six_(); four(); k2=0;}

            else if ((c2 == front[2][1]) && (c1 == right[2][0]) && (c3 == right[2][1])) {two_(); six_(); two(); k2=0;}
            else if ((c5 == left[2][1]) && (c2 == front[2][1]) && (c1 == front[2][0])) {five_(); six_(); five(); k2=0;}
            else if ((c1 == back[2][0]) && (c3 == right[2][1]) && (c4 == back[2][1])) {three_(); six_(); three(); k2=0;}
            else if ((c4 == back[2][1]) && (c5 == left[2][1]) && (c1 == left[2][0])) {four_(); six_(); four(); k2=0;}

            else if ((c1 == bottom[0][0]) && (c1 == bottom[0][1]) && (c1 == bottom[1][2]) &&
                    (c1 == bottom[2][1]) && (c1 == bottom[1][0]) && (c5 == left[2][1]) && (c2 == front[2][1]) &&
                     ((c5 != bottom[2][2]) || (c2 != front[2][0]))) {two(); six_(); two_(); k2=0;}
            else if ((c1 == bottom[0][2]) && (c1 == bottom[0][1]) && (c1 == bottom[1][2]) &&
                     (c1 == bottom[2][1]) && (c1 == bottom[1][0]) && (c3 == right[2][1]) && (c2 == front[2][1]) &&
                     ((c3 != right[2][0]) || (c2 != front[2][2]))) {three(); six_(); three_(); k2=0;}
            else if ((c1 == bottom[2][2]) && (c1 == bottom[0][1]) && (c1 == bottom[1][2]) &&
                     (c1 == bottom[2][1]) && (c1 == bottom[1][0]) && (c3 == right[2][1]) && (c4 == back[2][1]) &&
                     ((c4 != back[2][0]) || (c3 != right[2][2]))) {four(); six_(); four_(); k2=0;}
            else if ((c1 == bottom[2][0]) && (c1 == bottom[0][1]) && (c1 == bottom[1][2]) &&
                     (c1 == bottom[2][1]) && (c1 == bottom[1][0]) && (c5 == left[2][1]) && (c4 == back[2][1]) &&
                     ((c4 != back[2][2]) || (c3 != left[2][0]))) {four(); six_(); four_(); k2=0;}
            else if (count >= 1000) {cout << count; break;}
            else {six(); k2++;}
        }
        print();
    }

    bool cond3() {
        if ((c1 == bottom[0][0]) &&
            (c1 == bottom[0][1]) &&
            (c1 == bottom[0][2]) &&
            (c1 == bottom[1][0]) &&
            (c1 == bottom[1][2]) &&
            (c1 == bottom[2][0]) &&
            (c1 == bottom[2][1]) &&
            (c1 == bottom[2][2]) &&
            (c2 == front[2][0]) &&
            (c2 == front[2][1]) &&
            (c2 == front[2][2]) &&
            (c3 == right[2][0]) &&
            (c3 == right[2][1]) &&
            (c3 == right[2][2]) &&
            (c4 == back[2][0]) &&
            (c4 == back[2][1]) &&
            (c4 == back[2][2]) &&
            (c5 == left[2][0]) &&
            (c5 == left[2][1]) &&
            (c5 == left[2][2]) &&
            (c5 == left[1][0]) &&
            (c5 == left[1][2]) &&
            (c4 == back[1][0]) &&
            (c4 == back[1][2]) &&
            (c3 == right[1][0]) &&
            (c3 == right[1][2]) &&
            (c2 == front[1][0]) &&
            (c2 == front[1][2]))
            return true;
        else
            return false;
    }

    void step3() {
        int k3 = 0;
        while (!cond3()) {
            if (k3 == 3) {
                k3 = 0;
                if ((c2 == front[2][0]) && (c2 == front[2][1]) && (c2 == front[2][2]) && (c3 == right[2][0]) && (c3 == right[2][1]) &&
                (c3 == right[2][2]) && ((c2 != front[1][2]) || (c3 != right[1][0]))) {six(); three(); six_(); three_(); six_(); two_(); six(); two();}
                else if ((c2 == front[2][0]) && (c2 == front[2][1]) && (c2 == front[2][2]) && (c5 == left[2][0]) && (c5 == left[2][1]) &&
                (c5 == left[2][2]) && ((c2 != front[1][0]) || (c5 != left[1][2]))) {six(); two(); six_(); two_(); six_(); five_(); six(); five();}
                else if  ((c4 == back[2][0]) &&(c4 == back[2][1]) &&(c4 == back[2][2]) &&(c5 == left[2][0]) &&(c5 == left[2][1]) &&
                (c5 == left[2][2]) && ((c4 != back[1][2]) || (c5 != left[1][0]))) {six(); five(); six_(); five_(); six_(); four_(); six(); four();}
                else if ((c3 == right[2][0]) && (c3 == right[2][1]) &&(c3 == right[2][2]) &&(c4 == back[2][0]) &&(c4 == back[2][1]) &&
                (c4 == back[2][2]) && ((c4 != back[1][0]) || (c5 != right[1][2]))) {six(); four(); six_(); four_(); six_(); three_(); six(); three();}
                else {shuffle(); step2();}
                }

            else if ((c2 == front[2][0]) && (c2 == front[2][1]) && (c2 == front[2][2]) && (c5 == left[2][0]) && (c5 == left[2][1]) &&
                     (c5 == left[2][2]) && (c2 == front[0][1]) && (c5 == top[2][1])) {six_(); five_(); six(); five(); six(); two(); six_(); two_();}
            else if ((c2 == front[2][0]) && (c2 == front[2][1]) && (c2 == front[2][2]) && (c3 == right[2][0]) && (c3 == right[2][1]) &&
                    (c3 == right[2][2]) && (c3 == right[0][1]) && (c2 == top[1][2])) {six_(); two_(); six(); two(); six(); three(); six_(); three_();}
            else if ((c3 == right[2][0]) && (c3 == right[2][1]) && (c3 == right[2][2]) && (c4 == back[2][0]) && (c4 == back[2][1]) &&
                    (c4 == back[2][2]) && (c4 == back[0][1]) && (c3 == top[0][1])) {six_(); three_(); six(); three(); six(); four(); six_(); four_();}
            else if ((c4 == back[2][0]) && (c4 == back[2][1]) && (c4 == back[2][2]) && (c5 == left[2][0]) && (c5 == left[2][1]) &&
                    (c5 == left[2][2]) && (c5 == left[0][1]) && (c4 == top[1][0])) {six_(); four_(); six(); four(); six(); five(); six_(); five_();}

            else if ((c2 == front[2][0]) && (c2 == front[2][1]) && (c2 == front[2][2]) && (c3 == right[2][0]) && (c3 == right[2][1]) &&
                     (c3 == right[2][2]) && (c2 == front[0][1]) && (c3 == top[2][1])) {six(); three(); six_(); three_(); six_(); two_(); six(); two();}
            else if ((c2 == front[2][0]) && (c2 == front[2][1]) && (c2 == front[2][2]) && (c5 == left[2][0]) && (c5 == left[2][1]) &&
                     (c5 == left[2][2]) && (c5 == left[0][1]) && (c2 == top[1][0])) {six(); two(); six_(); two_(); six_(); five_(); six(); five();}
            else if ((c4 == back[2][0]) && (c4 == back[2][1]) && (c4 == back[2][2]) && (c5 == left[2][0]) && (c5 == left[2][1]) &&
                     (c5 == left[2][2]) && (c4 == back[0][1]) && (c5 == top[0][1])) {six(); five(); six_(); five_(); six_(); four_(); six(); four();}
            else if ((c3 == right[2][0]) && (c3 == right[2][1]) && (c3 == right[2][2]) && (c4 == back[2][0]) && (c4 == back[2][1]) &&
                     (c4 == back[2][2]) && (c5 == right[0][1]) && (c4 == top[1][2])) {six(); four(); six_(); four_(); six_(); three_(); six(); three();}

            else if (count >= 1000) {cout << count; break;}
            else {six(); k3++;}
        }
        print();
    }

    bool cond4() {
    if ((c2 == front[2][0]) &&
        (c2 == front[2][1]) &&
        (c2 == front[2][2]) &&
        (c3 == right[2][0]) &&
        (c3 == right[2][1]) &&
        (c3 == right[2][2]) &&
        (c4 == back[2][0]) &&
        (c4 == back[2][1]) &&
        (c4 == back[2][2]) &&
        (c5 == left[2][0]) &&
        (c5 == left[2][1]) &&
        (c5 == left[2][2]) &&
        (c5 == left[1][0]) &&
        (c5 == left[1][2]) &&
        (c4 == back[1][0]) &&
        (c4 == back[1][2]) &&
        (c3 == right[1][0]) &&
        (c3 == right[1][2]) &&
        (c2 == front[1][0]) &&
        (c2 == front[1][2]) &&
        (c6 == top[0][1])  &&
        (c6 == top[2][1]) &&
        (c6 == top[1][0]) &&
        (c6 == top[1][2]))
        return true;
    else
        return false;
}

    void step4() {
        while(!cond4()) {
            if ((c6 == front[0][1]) && (c6 == back[0][1]) && (c6 == top[1][0]) && (c6 == top[1][2])) {two(); three(); six(); three_(); six_(); two_(); break;}
            if ((c6 == left[0][1]) && (c6 == right[0][1]) && (c6 == top[0][1]) && (c6 == top[2][1])) {three(); four(); six(); four_(); six_(); three_(); break;}
            if ((c6 == front[0][1]) && (c6 == right[0][1]) && (c6 == top[1][0]) && (c6 == top[0][1])) {two(); six(); three(); six_(); three_(); two_(); break;}

            if ((c6 == front[0][1]) && (c6 == left[0][1]) && (c6 == top[0][1]) && (c6 == top[1][2])) {five(); six(); two(); six_(); two_(); five_(); break;}
            if ((c6 == back[0][1]) && (c6 == right[0][1]) && (c6 == top[1][0]) && (c6 == top[2][1])) {three(); six(); four(); six_(); four_(); three_(); break;}
            if ((c6 == back[0][1]) && (c6 == left[0][1]) && (c6 == top[1][2]) && (c6 == top[2][1])) {four(); six(); five(); six_(); five_(); four_(); break;}
            if ((c6 == front[0][1]) && (c6 == right[0][1]) && (c6 == left[0][1]) && (c6 == back[0][1])) {two(); six(); three(); six_(); three_(); two_(); three(); four(); six(); four_(); six_(); three_(); break;}
            break;
        }
        print();
    }

    bool cond5() {
        if ((cond4()) && (c2 == front[0][1]) && (c3 == right[0][1]) && (c4 == back[0][1]) && (c5 == left[0][1]))
            return true;
        else
            return false;
    }

//Вспомогательное условие
    bool cond5_() {
        if ((c6 == top[0][1]) && (c6 == top[1][0]) && (c6 == top[1][2]) && (c6 == top[2][1]))
            return true;
        else
            return false;
    }

    void step5() {
        if (cond5_() && (c2 == right[0][1])) {six(); five_(); six(); six(); five(); six(); five_(); six(); five();}
        else if (cond5_() && (c2 == left[0][1])) {six(); four_(); six(); six(); four(); six(); four_(); six(); four();}
        else if (cond5_() && (c2 == back[0][1])) {six(); three_(); six(); six(); three(); six(); three_(); six(); three(); six(); four_();
        six(); six(); four(); six(); four_(); six(); four(); six(); three_(); six(); six(); three(); six(); three_(); six(); three();}

        if (cond5_() && (c3 == back[0][1])) {six(); two_(); six(); six(); two(); six(); two_(); six(); two();}
        else if (cond5_() && (c3 == left[0][1])) {six(); four_(); six(); six(); four(); six(); four_(); six(); four(); six(); five_();
        six(); six(); five(); six(); five_(); six(); five(); six(); four_(); six(); six(); four(); six(); four_(); six(); four();}

        if (cond5_() && (c4 == left[0][1])) {six(); three_(); six(); six(); three(); six(); three_(); six(); three();}
        print();
    }

    void step6() {
        bool k6 = true;
        if (cond5() && (((c2 == top[2][0]) && (c3 == left[0][2]) && (c6 == front[0][0])) ||
            ((c2 == top[2][0]) && (c6 == left[0][2]) && (c3 == front[0][0])) || ((c3 == top[2][0]) && (c2 == left[0][2]) && (c6 == front[0][0])) ||
            ((c3 == top[2][0]) && (c6 == left[0][2]) && (c2 == front[0][0])) || ((c6 == top[2][0]) && (c2 == left[0][2]) && (c3 == front[0][0])) ||
            ((c6 == top[2][0]) && (c3 == left[0][2]) && (c2 == front[0][0])))) {two_(); five_(); two(); three_(); two_(); five(); two(); three();}
        else if (cond5() && (((c2 == top[0][2]) && (c3 == right[0][2]) && (c6 == back[0][0])) ||
                ((c2 == top[0][2]) && (c6 == right[0][2]) && (c3 == back[0][0])) || ((c3 == top[0][2]) && (c2 == right[0][2]) && (c6 == back[0][0])) ||
                ((c3 == top[0][2]) && (c6 == right[0][2]) && (c2 == back[0][0])) || ((c6 == top[0][2]) && (c3 == right[0][2]) && (c2 == back[0][0])) ||
                 ((c6 == top[0][2]) && (c2 == right[0][2]) && (c3 == back[0][0])))) {three_(); two_(); five_(); two(); three(); two_(); five(); two();}
        else if (cond5() && (((c2 == left[0][0]) && (c3 == top[0][0]) && (c6 == back[0][2])) ||
                ((c2 == left[0][0]) && (c6 == top[0][0]) && (c3 == back[0][2])) || ((c3 == left[0][0]) && (c2 == top[0][0]) && (c6 == back[0][2])) ||
                ((c3 == left[0][0]) && (c6 == top[0][0]) && (c2 == back[0][2])) || ((c6 == left[0][0]) && (c3 == top[0][0]) && (c2 == back[0][2])) ||
                ((c6 == left[0][0]) && (c2 == top[0][0]) && (c3 == back[0][2])))) {two_(); five_(); four_(); five(); two(); five_(); four(); five();}
        else {k6 = false;}
        if (!k6) {
            if (cond5() && (((c3 == left[0][2]) && (c4 == top[2][0]) && (c6 == front[0][0])) ||
                ((c3 == left[0][2]) && (c6 == top[2][0]) && (c4 == front[0][0])) || ((c4 == left[0][2]) && (c6 == top[2][0]) && (c3 == front[0][0])) ||
                ((c3 == left[0][2]) && (c3 == top[2][0]) && (c6 == front[0][0])) || ((c6 == left[0][2]) && (c3 == top[2][0]) && (c4 == front[0][0])) ||
                ((c6 == left[0][2]) && (c4 == top[2][0]) && (c3 == front[0][0])))) {four_(); three_(); four(); five_(); four_(); three(); four(); five();}
            else if (cond5() && (((c4 == left[0][0]) && (c3 == top[0][0]) && (c6 == back[0][2])) ||
                ((c4 == left[0][0]) && (c6 == top[0][0]) && (c3 == back[0][2])) || ((c3 == left[0][0]) && (c4 == top[0][0]) && (c6 == back[0][2])) ||
                ((c3 == left[0][0]) && (c6 == top[0][0]) && (c4 == back[0][2])) || ((c6 == left[0][0]) && (c3 == top[0][0]) && (c4 == back[0][2])) ||
                ((c6 == left[0][0]) && (c4 == top[0][0]) && (c3 == back[0][2])))) {five_(); four_(); three_(); four(); five(); four_(); three(); four();}
        }
        print();
    }

    bool cond7() {
        if ((c1 == bottom[0][0]) &&
             (c1 == bottom[0][1]) &&
             (c1 == bottom[0][2]) &&
             (c1 == bottom[1][0]) &&
             (c1 == bottom[1][2]) &&
             (c1 == bottom[2][0]) &&
             (c1 == bottom[2][1]) &&
             (c1 == bottom[2][2]) &&
             (c2 == front[0][0]) &&
             (c2 == front[0][1]) &&
             (c2 == front[0][2]) &&
             (c2 == front[1][0]) &&
             (c2 == front[1][2]) &&
             (c2 == front[2][0]) &&
             (c2 == front[2][1]) &&
             (c2 == front[2][2]) &&
             (c3 == right[0][0]) &&
             (c3 == right[0][1]) &&
             (c3 == right[0][2]) &&
             (c3 == right[1][0]) &&
             (c3 == right[1][2]) &&
             (c3 == right[2][0]) &&
             (c3 == right[2][1]) &&
             (c3 == right[2][2]) &&
             (c4 == back[0][0]) &&
             (c4 == back[0][1]) &&
             (c4 == back[0][2]) &&
             (c4 == back[1][0]) &&
             (c4 == back[1][2]) &&
             (c4 == back[2][0]) &&
             (c4 == back[2][1]) &&
             (c4 == back[2][2]) &&
             (c5 == left[0][0]) &&
             (c5 == left[0][1]) &&
             (c5 == left[0][2]) &&
             (c5 == left[1][0]) &&
             (c5 == left[1][2]) &&
             (c5 == left[2][0]) &&
             (c5 == left[2][1]) &&
             (c5 == left[2][2]) &&
             (c6 == top[0][0]) &&
             (c6 == top[0][1]) &&
             (c6 == top[0][2]) &&
             (c6 == top[1][0]) &&
             (c6 == top[1][2]) &&
             (c6 == top[2][0]) &&
             (c6 == top[2][1]) &&
             (c6 == top[2][2]))
            return true;
        else
            return false;
    }

    bool cond7_1() {
        if ((c6 == top[0][1]) && (c6 == top[2][1]) && (c6 == top[1][0]) && (c6 == top[1][2]) && (c6 == right[0][0]))
            return true;
        else
            return false;
    }

    bool cond7_2() {
        if ((c6 == top[0][1]) && (c6 == top[2][1]) && (c6 == top[1][0]) && (c6 == top[1][2]) && (c6 == front[0][2]))
            return true;
        else
            return false;
    }

    void step7() {
        for (int i = 0; i < 100; i++) {
            if (cond7_1()) {two_(); three(); two(); three_(); two_(); three(); two(); three_();}
            else if (cond7_2()) {three(); two_(); three_(); two(); three(); two_(); three_(); two();}
            six();
            if (cond7()) {break;}
        }
        print();
    }

    bool solver(){
        if (!cond7()) {
            step1();
            step2();
            step3();
            step4();
            step5();
            step6();
            step7();
        }
        if (cond7())
            return true;
        else
            return false;
    }

    void answer() {
        ofstream fout("output.txt");
       if (solver()) {
           fout << turns;
       }
       else {
           fout << "Unfortunately, this color combination is not a Rubik's cube and it is impossible to assemble it.";
       }
    }

};

int main() {
    ofstream fout("output.txt");
    Maker c;
    c.file_reader();
    c.numbers();
    c.print();
    cout << c.count << " " << c.cond7() << endl;
    c.shuffle();
    c.print();
    c.solver();
    c.answer();
    cout << c.count << " " << c.cond7() << endl;
    return 0;
}
