#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

vector<int> lexico(string codigo) {
    int i = 0;
    int estado = 0;
    string lexema = "";
    vector<int> tokens;
    codigo += " ";
    while (i < codigo.length()) {
        char c = codigo[i];
        switch (estado) {
        case 0:
            if (isdigit(c)) {
                lexema += c;
                estado = 1;
                i++;
            }
            else if (isalpha(c)) {
                lexema += c;
                estado = 3;
                i++;
            }
            else if (c == '+') {
                tokens.push_back(20);
                i++;
            }
            else if (c == '-') {
                tokens.push_back(21);
                i++;
            }
            else if (c == '*') {
                tokens.push_back(22);
                i++;
            }
            else if (c == '/') {
                tokens.push_back(23);
                i++;
            }
            else if (c == '%') {
                tokens.push_back(24);
                i++;
            }
            else if (c == '<') {
                estado = 4;
                i++;
            }
            else if (c == '>') {
                estado = 5;
                i++;
            }
            else if (c == '=') {
                estado = 6;
                i++;
            }
            else if (c == '!') {
                estado = 7;
                i++;
            }
            else if (c == '(') {
                tokens.push_back(30);
                i++;
            }
            else if (c == ')') {
                tokens.push_back(31);
                i++;
            }
            else if (c == '{') {
                tokens.push_back(32);
                i++;
            }
            else if (c == '}') {
                tokens.push_back(33);
                i++;
            }
            else if (c == ',') {
                tokens.push_back(51);
                i++;
            }
            else if (c == ';') {
                tokens.push_back(52);
                i++;
            }
            else if (c == ':') {
                tokens.push_back(50);
                i++;
            }
            else if (isspace(c)) {
                i++;
            }
            else {
                cout << "Error lexico: simbolo desconocido '" << c << "'" << endl;
                return {};
            }
            break;

        case 1:
            if (isdigit(c)) {
                lexema += c;
                i++;
            }
            else if (c == '.') {
                lexema += c;
                estado = 2;
                i++;
            }
            else {
                tokens.push_back(2000);
                lexema = "";
                estado = 0;
            }
            break;

        case 2:
            if (isdigit(c)) {
                lexema += c;
                i++;

                while (i < codigo.length() && isdigit(codigo[i])) {
                    lexema += codigo[i];
                    i++;
                }
                tokens.push_back(2001);
                lexema = "";
                estado = 0;
            }
            else {
                cout << "Error lexico: numero flotante mal formado -> "<< lexema << endl;
                return {};
            }
            break;

        case 3:
            if (isalnum(c)) {
                lexema += c;
                i++;
            }
            else {
                if (lexema == "declarar")
                    tokens.push_back(3);
                else if (lexema == "mientras")
                    tokens.push_back(6);

                else if (lexema == "si")
                    tokens.push_back(4);

                else if (lexema == "sino")
                    tokens.push_back(5);

                else if (lexema == "imprimir")
                    tokens.push_back(7);

                else if (lexema == "potencia")
                    tokens.push_back(300);

                else if (lexema == "raiz")
                    tokens.push_back(301);

                else if (lexema == "sin")
                    tokens.push_back(302);

                else if (lexema == "cos")
                    tokens.push_back(303);

                else if (lexema == "tan")
                    tokens.push_back(304);

                else if (lexema == "logb")
                    tokens.push_back(305);

                else if (lexema == "redondear")
                    tokens.push_back(306);

                else if (lexema == "ENTERO")
                    tokens.push_back(10);

                else if (lexema == "FLOTANTE")
                    tokens.push_back(12);

                else
                    tokens.push_back(1000);
                lexema = "";
                estado = 0;
            }
            break;

        case 4:
            if (c == '=') {
                tokens.push_back(42);
                i++;
            }
            else {
                tokens.push_back(40);
            }
            estado = 0;
            break;

        case 5:
            if (c == '=') {
                tokens.push_back(43);
                i++;
            }
            else {
                tokens.push_back(41);
            }
            estado = 0;
            break;

        case 6:
            if (c == '=') {
                tokens.push_back(45);
                i++;
            }
            else {
                tokens.push_back(25);
            }
            estado = 0;
            break;

        case 7:
            if (c == '=') {
                tokens.push_back(44);
                i++;
            }
            else {
                tokens.push_back(46);
            }
            estado = 0;
            break;
        }
    }
    return tokens;
}

int main() {

    string codigo = R"(

        declarar x = 2;
        declarar y = 3;
        declarar res = 0;
        mientras (x < 6) {
            si (x % 2 == 0) {
                res = res + potencia(x, y) + raiz(x, 2);
            }
            si (x > 3) {
                res = res + sin(0) + cos(0);
            }
            x = x + 1;
        }
        imprimir res;
    )";

    vector<int> tokens = lexico(codigo);

    if (!tokens.empty()) {
        cout << "Tokens generados:" << endl;
        for (int token : tokens) {
            cout << token << " ";
        }
        cout << endl;
    }
    return 0;
}
