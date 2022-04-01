#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

// Fungsi untuk menentukan nilai (kasta) operator
int kasta(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Fungsi mengubah infix ke postfix
string infixToPostfix(const string &s) {
    stack<char> st;
    string hasil;

    for (char i: s) {
        char c = i;

        if (c == ' ')
            continue;

        // Jika karakter adalah sebuah operand, tambah ke output string
        else if (c >= '0' && c <= '9')
            hasil += c;

        // Jika karakter adalah '(', push ke stack
        else if (c == '(')
            st.push('(');

        // Jika karakter adalah ')', pop hingga output string bertemu dengan '('
        else if (c == ')') {
            while (st.top() != '(') {
                hasil += st.top();
                st.pop();
            }
            st.pop();
        }

        // Jika karakter adalah sebuah operator
        else {
            while (!st.empty() && kasta(i) <= kasta(st.top())) {
                hasil += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop semua elemen yang tersisa dari stack
    while (!st.empty()) {
        hasil += st.top();
        st.pop();
    }

    // Tambah spasi untuk setiap karakter
    string output;
    for (int i = 0; i < hasil.length(); ++i) {
        output += hasil.substr(i, 1) + " ";
    }

    return output;
}

// Fungsi untuk mengkalkulasi hasil dari sebuah notasi postfix
double kalkulasiPostfix(string exp) {
    stack<double> st;
    int i;

    // Scan karakter satu-satu
    for (i = 0; exp[i]; ++i) {
        // Jika karakter kosong, skip
        if (exp[i] == ' ')
            continue;

        // Jika karakter adalah operand, ambil nomor, kemudian push ke st
        else if (isdigit(exp[i])) {
            int num = 0;

            // Ambil nomor penuh
            while (isdigit(exp[i])) {
                num = num * 10 + (int) (exp[i] - '0');
                i++;
            }
            i--;

            // push element ke st
            st.push(num);
        }

        // Jika karakter adalah sebuah operator, pop kedua operator untuk digunakan
        else {
            double nilai1 = st.top();
            st.pop();
            double nilai2 = st.top();
            st.pop();
            switch (exp[i]) {
                case '+':
                    st.push(nilai2 + nilai1);
                    break;
                case '-':
                    st.push(nilai2 - nilai1);
                    break;
                case '*':
                    st.push(nilai2 * nilai1);
                    break;
                case '/':
                    st.push(nilai2 / nilai1);
                    break;
                case '^':
                    st.push(pow(nilai2, nilai1));
            }
        }
    }
    double hasil = st.top();
    st.pop();
    return hasil;
}

// === Fungsi Main ===
int main() {
    string infix = "(1+2)-3*4^5/3";
    string postfix;
    double hasil;

    cout << "Notasi Infix: " << infix << endl;
    postfix = infixToPostfix(infix);
    cout << "Notasi Postfix: " << postfix << endl;
    hasil = kalkulasiPostfix(postfix);
    cout << "Hasil Kalkulasi Postfix: " << hasil << endl;
}
