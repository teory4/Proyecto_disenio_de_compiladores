#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

//   ANALIZADOR LEXICO

vector<int> tokens;
vector<string> errores;
int i = 0; 

vector<int> lexico(string codigo){

    int i = 0;
    int estado = 0;
    string lexema = "";
    vector<int> tokens;
    codigo += " ";
    while(i < codigo.length()){

        char c = codigo[i];
        switch(estado){

        case 0:

            if(isdigit(c)){

                lexema += c;
                estado = 1;
                i++;
            }

            else if(isalpha(c)){

                lexema += c;
                estado = 3;
                i++;
            }

            else if(c == '+'){

                tokens.push_back(20);
                i++;
            }

            else if(c == '-'){

                tokens.push_back(21);
                i++;
            }

            else if(c == '*'){

                tokens.push_back(22);
                i++;
            }

            else if(c == '/'){

                tokens.push_back(23);
                i++;
            }

            else if(c == '%'){

                tokens.push_back(24);
                i++;
            }

            else if(c == '<'){

                estado = 4;
                i++;
            }

            else if(c == '>'){

                estado = 5;
                i++;
            }

            else if(c == '='){

                estado = 6;
                i++;
            }

            else if(c == '!'){

                estado = 7;
                i++;
            }

            else if(c == '('){

                tokens.push_back(30);
                i++;
            }

            else if(c == ')'){

                tokens.push_back(31);
                i++;
            }

            else if(c == '{'){

                tokens.push_back(32);
                i++;
            }

            else if(c == '}'){

                tokens.push_back(33);
                i++;
            }

            else if(c == ','){

                tokens.push_back(51);
                i++;
            }

            else if(c == ';'){

                tokens.push_back(52);
                i++;
            }

            else if(c == ':'){

                tokens.push_back(50);
                i++;
            }

            else if(isspace(c)){

                i++;
            }

            else{

                cout<<"Error lexico: simbolo desconocido "<<c<<endl;
                return {};
            }

            break;

        case 1:

            if(isdigit(c)){

                lexema += c;
                i++;
            }

            else if(c == '.'){

                lexema += c;
                estado = 2;
                i++;
            }

            else{

                tokens.push_back(2000);

                lexema = "";
                estado = 0;
            }

            break;

        case 2:

            if(isdigit(c)){

                lexema += c;
                i++;

                while(i < codigo.length() && isdigit(codigo[i])){

                    lexema += codigo[i];
                    i++;
                }

                tokens.push_back(2001);

                lexema = "";
                estado = 0;
            }

            else{

                cout<<"Error lexico: numero flotante mal formado "<<lexema<<endl;
                return {};
            }

            break;

        case 3:

            if(isalnum(c)){

                lexema += c;
                i++;
            }

            else{

                if(lexema == "declarar")
                    tokens.push_back(3);

                else if(lexema == "si")
                    tokens.push_back(4);

                else if(lexema == "sino")
                    tokens.push_back(5);

                else if(lexema == "mientras")
                    tokens.push_back(6);

                else if(lexema == "imprimir")
                    tokens.push_back(7);

                else if(lexema == "potencia")
                    tokens.push_back(300);

                else if(lexema == "raiz")
                    tokens.push_back(301);

                else if(lexema == "sin")
                    tokens.push_back(302);

                else if(lexema == "cos")
                    tokens.push_back(303);

                else if(lexema == "tan")
                    tokens.push_back(304);

                else if(lexema == "logb")
                    tokens.push_back(305);

                else if(lexema == "redondear")
                    tokens.push_back(306);

                else if(lexema == "ENTERO")
                    tokens.push_back(10);

                else if(lexema == "FLOTANTE")
                    tokens.push_back(12);

                else
                    tokens.push_back(1000);

                lexema = "";
                estado = 0;
            }

            break;

        case 4:

            if(c == '='){

                tokens.push_back(42);
                i++;
            }

            else{

                tokens.push_back(40);
            }

            estado = 0;

            break;

        case 5:

            if(c == '='){

                tokens.push_back(43);
                i++;
            }

            else{

                tokens.push_back(41);
            }

            estado = 0;

            break;

        case 6:

            if(c == '='){

                tokens.push_back(45);
                i++;
            }

            else{

                tokens.push_back(25);
            }

            estado = 0;

            break;

        case 7:

            if(c == '='){

                tokens.push_back(44);
                i++;
            }

            else{

                tokens.push_back(46);
            }

            estado = 0;

            break;
        }
    }

    return tokens;
}

//    ANALIZADOR SINTACTICO

bool sig(int t){

    return t == 20 || t == 21 || t == 22 || t == 23 ||
           t == 24 || t == 40 || t == 41 || t == 42 ||
           t == 43 || t == 45 || t == 46;
}

void error(string mensaje){

    errores.push_back(mensaje);
}

bool fin(){

    return i >= tokens.size();
}

void sincronizar(){

    while(i < tokens.size() && tokens[i] != 52){

        i++;
    }

    if(i < tokens.size() && tokens[i] == 52){

        i++;
    }
}

void accion();
void sentencia();
void declar();
void asignacion();
void mien();
void sient();
void impr();
void operacion();
void op();
void varnum();
void funcion();
void potencia();
void raiz();
void seno();
void coseno();
void tangente();
void logaritmo();
void redondea();
void factorial();


void accion(){

    while(i < tokens.size() && tokens[i] != 33){

        sentencia();
    }
}


void sentencia(){

    if(fin()) return;

    if(tokens[i] == 3){

        declar();
    }

    else if(tokens[i] == 1000){

        asignacion();
    }

    else if(tokens[i] == 6){

        mien();
    }

    else if(tokens[i] == 4){

        sient();
    }

    else if(tokens[i] == 7){

        impr();
    }

    else{

        error("Error: se esperaba SENTENCIA");
        i++;
    }
}

void declar(){

    if(tokens[i] == 3){

        i++;
    }

    else{

        error("Error: se esperaba DECLARAR");
        sincronizar();
        return;
    }

    if(fin()) return;

    if(tokens[i] == 1000){

        i++;
    }

    else{

        error("Error: se esperaba VARIABLE");
    }

    if(fin()) return;

    if(tokens[i] == 25){

        i++;
    }

    else{

        error("Error: se esperaba =");
    }

    operacion();

    if(fin()) return;

    if(tokens[i] == 52){

        i++;
    }

    else{

        error("Error: se esperaba ;");
        sincronizar();
    }
}

void asignacion(){

    if(tokens[i] == 1000){

        i++;
    }

    else{

        error("Error: se esperaba VARIABLE");
        sincronizar();
        return;
    }

    if(fin()) return;

    if(tokens[i] == 25){

        i++;
    }

    else{

        error("Error: se esperaba =");
    }

    operacion();

    if(fin()) return;

    if(tokens[i] == 52){

        i++;
    }

    else{

        error("Error: se esperaba ;");
        sincronizar();
    }
}

void impr(){

    if(tokens[i] == 7){

        i++;
    }

    else{

        error("Error: se esperaba IMPRIMIR");
        sincronizar();
        return;
    }

    if(fin()) return;

    if(tokens[i] == 1000){

        i++;
    }

    else{

        error("Error: se esperaba VARIABLE");
    }

    if(fin()) return;

    if(tokens[i] == 52){

        i++;
    }

    else{

        error("Error: se esperaba ;");
        sincronizar();
    }
}

void mien(){

    if(tokens[i] == 6){

        i++;
    }

    else{

        error("Error: se esperaba MIENTRAS");
        sincronizar();
        return;
    }

    if(fin()) return;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    operacion();

    if(fin()) return;

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }

    if(fin()) return;

    if(tokens[i] == 32){

        i++;
    }

    else{

        error("Error: se esperaba {");
    }

    accion();

    if(fin()) return;

    if(tokens[i] == 33){

        i++;
    }

    else{

        error("Error: se esperaba }");
    }
}

void sient(){

    if(tokens[i] == 4){

        i++;
    }

    else{

        error("Error: se esperaba SI");
        sincronizar();
        return;
    }

    if(fin()) return;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    operacion();

    if(fin()) return;

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }

    if(fin()) return;

    if(tokens[i] == 32){

        i++;
    }

    else{

        error("Error: se esperaba {");
    }

    accion();

    if(fin()) return;

    if(tokens[i] == 33){

        i++;
    }

    else{

        error("Error: se esperaba }");
    }
}

void operacion(){

    op();

    while(i < tokens.size() && sig(tokens[i])){

        i++;
        op();
    }
}

void op(){

    if(fin()) return;

    if(tokens[i] == 1000 ||
       tokens[i] == 2000 ||
       tokens[i] == 2001)
    {

        if(i + 1 < tokens.size() && tokens[i+1] == 44)
        {
            funcion();
        }

        else{
            varnum();
        }
    }

    else if(tokens[i] >= 300 && tokens[i] <= 306)
    {
        funcion();
    }

    else{
        error("Error: se esperaba VARIABLE O NUMERO O FUNCION");
        i++;
    }
}

void varnum(){

    if(fin()) return;

    if(tokens[i] == 1000 ||
       tokens[i] == 2000 ||
       tokens[i] == 2001)
    {

        i++;
    }

    else{

        error("Error: se esperaba VARIABLE o NUMERO");
    }
}

void funcion(){

    if(tokens[i] == 300)
        potencia();

    else if(tokens[i] == 301)
        raiz();

    else if(tokens[i] == 302)
        seno();

    else if(tokens[i] == 303)
        coseno();

    else if(tokens[i] == 304)
        tangente();

    else if(tokens[i] == 305)
        logaritmo();

    else if(tokens[i] == 306)
        redondea();

    else if((tokens[i] == 1000 ||
             tokens[i] == 2000 ||
             tokens[i] == 2001)
             &&
            i + 1 < tokens.size() &&
            tokens[i+1] == 44)
    {
        factorial();
    }

    else{

        error("Error: funcion invalida");
    }
}

void potencia(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 51){

        i++;
    }

    else{

        error("Error: se esperaba ,");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void raiz(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 51){

        i++;
    }

    else{

        error("Error: se esperaba ,");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void seno(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void coseno(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void tangente(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void logaritmo(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 51){

        i++;
    }

    else{

        error("Error: se esperaba ,");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void redondea(){

    i++;

    if(tokens[i] == 30){

        i++;
    }

    else{

        error("Error: se esperaba (");
    }

    varnum();

    if(tokens[i] == 31){

        i++;
    }

    else{

        error("Error: se esperaba )");
    }
}

void factorial(){

    varnum();

    if(tokens[i] == 44){

        i++;
    }

    else{

        error("Error: se esperaba !");
    }
}


//            MAIN


int main(){

    string codigo = R"(

    declarar x = 2;
    declarar y = 3;
    declarar res = 0;

    mientras (x < 6) {

        si (x % 2 == 0) {

            res = res + potencia(x, y) + raiz(x, 2);
        }

        x = x + 1;
    }

    imprimir res;
    )";

    tokens = lexico(codigo);

    if(tokens.empty()){

        return 0;
    }

    cout<<"TOKENS GENERADOS:"<<endl;

    for(int t : tokens){

        cout<<t<<" ";
    }

    cout<<endl<<endl;

    accion();

    if(errores.empty()){

        cout<<"ANALISIS SINTACTICO VALIDO"<<endl;
    }

    else{

        cout<<"ERRORES SINTACTICOS:"<<endl;

        for(string e : errores){

            cout<<e<<endl;
        }
    }

    return 0;
}

