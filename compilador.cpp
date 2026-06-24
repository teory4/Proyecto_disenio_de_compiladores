#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stack>
#include <set>
#include <sstream>

using namespace std;

//          Índice
//Analizador léxico linea 18
//Analizador sintáctico linea 348
//Analizador semántico linea 1032
//Generación de código intermedio linea 1431


//   Analizador léxico

vector<int> tokens;
vector<string> errores;
int i = 0; 
int erroreslexico=0;

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
                erroreslexico=1;
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
                erroreslexico=1;
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

//Analizador Sintáctico

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

    if(tokens[i] == 1000 ||tokens[i] == 2000 ||tokens[i] == 2001){

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

    if(tokens[i] == 1000 ||tokens[i] == 2000 ||tokens[i] == 2001)
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

    else if((tokens[i] == 1000 || tokens[i] == 2000 || tokens[i] == 2001) && i + 1 < tokens.size() && tokens[i+1] == 44)
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

//analizador semántico

set<string> tablaSimbolos;
vector<string> erroresSemanticos;

void errorSemantico(string mensaje){

    erroresSemanticos.push_back(mensaje);
}

bool esPalabraReservada(string palabra){

    return palabra == "si" ||
           palabra == "sino" ||
           palabra == "mientras" ||
           palabra == "imprimir" ||
           palabra == "declarar" ||
           palabra == "potencia" ||
           palabra == "raiz" ||
           palabra == "sin" ||
           palabra == "cos" ||
           palabra == "tan" ||
           palabra == "logb" ||
           palabra == "redondear";
}



bool esFuncionMatematica(string palabra){

    return palabra == "potencia" ||
           palabra == "raiz" ||
           palabra == "sin" ||
           palabra == "cos" ||
           palabra == "tan" ||
           palabra == "logb" ||
           palabra == "redondear";
}

int contarParametros(string texto){

    int contador = 1;

    for(char c : texto){

        if(c == ',')
            contador++;
    }

    return contador;
}

void verificarFunciones(string expresion){

    vector<string> funcionesDos ={"potencia","raiz","logb"};

    vector<string> funcionesUno ={"sin","cos","tan","redondear"};

    for(string nombre : funcionesDos){

        size_t pos = expresion.find(nombre + "(");

        if(pos != string::npos){

            size_t ini = expresion.find("(", pos);
            size_t fin = expresion.find(")", ini);

            if(fin == string::npos){

                errorSemantico("Funcion mal formada: "+ nombre);

                continue;
            }

            string parametros =
                expresion.substr(ini + 1,fin - ini - 1);

            if(contarParametros(parametros) != 2){

                errorSemantico(
                    nombre +
                    " requiere 2 parametros");
            }

            string palabra = "";

            for(char c : parametros){

                if(isalpha(c))
                    palabra += c;

                else{

                    if(!palabra.empty()){

                        if(!tablaSimbolos.count(
                            palabra))
                        {
                            errorSemantico(
                            "Variable no declarada: "
                            + palabra);
                        }

                        palabra.clear();
                    }
                }
            }

            if(!palabra.empty()){

                if(!tablaSimbolos.count(
                    palabra))
                {
                    errorSemantico(
                    "Variable no declarada: "
                    + palabra);
                }
            }
        }
    }

    for(string nombre : funcionesUno){

        size_t pos = expresion.find(nombre + "(");

        if(pos != string::npos){

            size_t ini = expresion.find("(", pos);
            size_t fin = expresion.find(")", ini);

            if(fin == string::npos){

                errorSemantico("Funcion mal formada: "+ nombre);

                continue;
            }

            string parametros = expresion.substr(ini + 1, fin - ini - 1);

            if(contarParametros(parametros) != 1){

                errorSemantico(nombre +" requiere 1 parametro");
            }

            string palabra = "";

            for(char c : parametros){

                if(isalpha(c))
                    palabra += c;

                else{

                    if(!palabra.empty()){

                        if(!tablaSimbolos.count(palabra))
                        {
                            errorSemantico("Variable no declarada: "+ palabra);
                        }

                        palabra.clear();
                    }
                }
            }

            if(!palabra.empty()){

                if(!tablaSimbolos.count(palabra))
                {
                    errorSemantico("Variable no declarada: "+ palabra);
                }
            }
        }
    }
}

string quitarEspacios(string s){

    string r = "";

    for(char c : s){

        if(!isspace(c)){

            r += c;
        }
    }

    return r;
}

string quitarPuntoComa(string s){

    string r = "";

    for(char c : s){

        if(c != ';'){

            r += c;
        }
    }

    return r;
}

bool contieneRelacional(string texto){

    return texto.find("<=") != string::npos ||
           texto.find(">=") != string::npos ||
           texto.find("==") != string::npos ||
           texto.find("!=") != string::npos ||
           texto.find("<")  != string::npos ||
           texto.find(">")  != string::npos;
}

void verificarVariablesExpresion(string expresion){

    string palabra = "";
    for(char c : expresion){

        if(isalpha(c)){

            palabra += c;
        }

        else{
            if(!palabra.empty()){

                if(!esPalabraReservada(palabra)){
                    if(tablaSimbolos.find(palabra)==tablaSimbolos.end()){
                        
                        errorSemantico("Variable no declarada: "+ palabra);
                        }
                    }

                palabra.clear();
            }
        }
    }

    if(!palabra.empty()){
        if(!esPalabraReservada(palabra)){
                    if(tablaSimbolos.find(palabra)==tablaSimbolos.end()){
                        errorSemantico("Variable no declarada: "+ palabra);
                        }
                    }
    }
}

void analizarSemantica(string codigo){

    tablaSimbolos.clear();

    erroresSemanticos.clear();

    stringstream ss(codigo);

    string linea;

    while(getline(ss,linea)){

        linea = quitarEspacios(linea);

        if(linea.empty())
            continue;
        // DECLARAR
        if(linea.find("declarar") == 0){

            int posIgual = linea.find("=");
            string variable = linea.substr(8, posIgual - 8);
            if(tablaSimbolos.count(variable))
            {
                errorSemantico("Variable ya declarada: "+ variable);
            }

            else{

                tablaSimbolos.insert(variable);
            }

            string expresion =linea.substr(posIgual + 1);

            expresion = quitarPuntoComa(expresion);

            if(contieneRelacional(expresion))
            {
                errorSemantico("Operador relacional no permitido en declaracion");
            }

            verificarVariablesExpresion(expresion);
            verificarFunciones(expresion);
        }

        // IMPRIMIR

        else if(linea.find("imprimir") == 0){
            string variable =linea.substr(8);

            variable = quitarPuntoComa(variable);

            if(!tablaSimbolos.count(variable))
            {
                errorSemantico("Variable no declarada: "+ variable);
            }
        }

        // ASIGNACION

    else if(linea.find("si(") == 0){
            continue;
            }
    else if(linea.find("mientras(") == 0){
        continue;
        }

    else if(linea.find("=") != string::npos){

            if(linea.find("==") != string::npos)
                continue;

            int posIgual = linea.find("=");

            string variable = linea.substr(0, posIgual);

            if(!tablaSimbolos.count(variable)){

                errorSemantico("Variable no declarada: " + variable);
            }

            string expresion =linea.substr(posIgual + 1);

            expresion =quitarPuntoComa(expresion);

            if(contieneRelacional(expresion)){

                errorSemantico("Operador relacional no permitido en asignacion");
            }

            verificarVariablesExpresion(expresion);
            verificarFunciones(expresion);
        }
        }
    }

void mostrarErroresSemanticos(){

    if(erroresSemanticos.empty()){

        cout<< "\nANALISIS SEMANTICO VALIDO\n";
        return;
    }

    cout<< "\nERRORES SEMANTICOS\n";

    for(string e :erroresSemanticos)
    {
        cout<< e<< endl;
    }
}



//Generación de código intermedio

struct Cuadruplo{

    string op;
    string arg1;
    string arg2;
    string res;
};

vector<Cuadruplo> cuadruplos;

stack<string> pilaInicioWhile;
stack<string> pilaFinWhile;

stack<string> pilaFinIf;

int contadorTemporal = 0;

int contadorEtiqueta = 0;

string nuevaEtiqueta(){

    contadorEtiqueta++;

    return "L" + to_string(contadorEtiqueta);
}


string nuevoTemporal(){

    contadorTemporal++;

    return "t" + to_string(contadorTemporal);
}

void agregarCuadruplo(string op,string arg1,string arg2,string res){

    Cuadruplo c;

    c.op = op;
    c.arg1 = arg1;
    c.arg2 = arg2;
    c.res = res;

    cuadruplos.push_back(c);
}



bool esOperador(char c){

    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '%';
}

int prioridad(char op){

    if(op == '*' ||
       op == '/' ||
       op == '%')
        return 2;

    if(op == '+' ||
       op == '-')
        return 1;

    return 0;
}

string operadorTexto(char op){

    string s = "";

    s += op;

    return s;
}

vector<string> separarExpresion(string expr){

    vector<string> elementos;

    string actual = "";

    for(char c : expr){

        if(isspace(c))
            continue;

        if(esOperador(c)){

            if(actual != ""){

                elementos.push_back(actual);
                actual = "";
            }

            string op = "";

            op += c;

            elementos.push_back(op);
        }

        else{

            actual += c;
        }
    }

    if(actual != ""){

        elementos.push_back(actual);
    }

    return elementos;
}

bool esFuncion(string s){

    return s.find("potencia(") == 0 ||
           s.find("raiz(") == 0 ||
           s.find("sin(") == 0 ||
           s.find("cos(") == 0 ||
           s.find("tan(") == 0 ||
           s.find("logb(") == 0 ||
           s.find("redondear(") == 0;
}

vector<string> extraerParametros(string texto){

    vector<string> params;

    int ini = texto.find("(");
    int fin = texto.rfind(")");

    if(ini == string::npos ||
       fin == string::npos)
        return params;

    string dentro =texto.substr(ini + 1,fin - ini - 1);

    string actual = "";

    for(char c : dentro){

        if(c == ','){

            params.push_back(actual);
            actual.clear();
        }

        else{

            actual += c;
        }
    }

    if(!actual.empty())
        params.push_back(actual);

    return params;
}


string generarFuncion(string texto){

    string temp =
        nuevoTemporal();

    vector<string> p =
        extraerParametros(texto);

    if(texto.find("potencia(") == 0){

        agregarCuadruplo(
            "POTENCIA",
            p[0],
            p[1],
            temp);
    }

    else if(texto.find("raiz(") == 0){

        agregarCuadruplo(
            "RAIZ",
            p[0],
            p[1],
            temp);
    }

    else if(texto.find("sin(") == 0){

        agregarCuadruplo(
            "SIN",
            p[0],
            "-",
            temp);
    }

    else if(texto.find("cos(") == 0){

        agregarCuadruplo(
            "COS",
            p[0],
            "-",
            temp);
    }

    else if(texto.find("tan(") == 0){

        agregarCuadruplo(
            "TAN",
            p[0],
            "-",
            temp);
    }

    else if(texto.find("logb(") == 0){

        agregarCuadruplo(
            "LOGB",
            p[0],
            p[1],
            temp);
    }

    else if(texto.find("redondear(") == 0){

        agregarCuadruplo(
            "REDONDEAR",
            p[0],
            "-",
            temp);
    }

    return temp;
}

bool esFactorial(string s){

    return !s.empty() &&
           s.back() == '!';
}

string generarFactorial(string s){

    string valor =
        s.substr(
            0,
            s.size()-1);

    string temp =
        nuevoTemporal();

    agregarCuadruplo(
        "FACTORIAL",
        valor,
        "-",
        temp);

    return temp;
}




string generarExpresion(string expr){

    vector<string> elementos =
        separarExpresion(expr);

    stack<string> operandos;
    stack<char> operadores;

    for(string e : elementos){

        if(e == "+" ||
           e == "-" ||
           e == "*" ||
           e == "/" ||
           e == "%")
        {

            char op = e[0];

            while(!operadores.empty() && prioridad(operadores.top()) >= prioridad(op))
            {

                string der = operandos.top();
                operandos.pop();

                string izq = operandos.top();
                operandos.pop();

                char operador = operadores.top();

                operadores.pop();

                string temp = nuevoTemporal();

                agregarCuadruplo(operadorTexto(operador), izq, der, temp);

                operandos.push(temp);
            }

            operadores.push(op);
        }

        else{

            if(esFuncion(e)){

            operandos.push(generarFuncion(e));
            }

            else if(esFactorial(e)){

            operandos.push(generarFactorial(e));
            }
            else{
            operandos.push(e);
            }
        }
    }

    while(!operadores.empty()){

        string der = operandos.top();
        operandos.pop();

        string izq = operandos.top();
        operandos.pop();

        char operador = operadores.top();

        operadores.pop();

        string temp = nuevoTemporal();

        agregarCuadruplo(operadorTexto(operador), izq, der, temp);

        operandos.push(temp);
    }

    return operandos.top();
}


bool esRelacional(string s){

    return s == "<"  ||
           s == ">"  ||
           s == "<=" ||
           s == ">=" ||
           s == "==" ||
           s == "!=";
}


string generarCondicion(string condicion){

    string op;
    string izq;
    string der;

    vector<string> relacionales =
    {
        "<=",
        ">=",
        "==",
        "!=",
        "<",
        ">"
    };

    for(string r : relacionales){

        size_t pos = condicion.find(r);

        if(pos != string::npos){

            op = r;

            izq = condicion.substr(0,pos);

            der = condicion.substr(pos + r.size());

            break;
        }
    }

    string temp = nuevoTemporal();

    agregarCuadruplo(op, izq, der, temp);

    return temp;
}




void generarCodigoIntermedio(string codigo){

    stringstream ss(codigo);

    string linea;

    while(getline(ss,linea)){

        linea = quitarEspacios(linea);

        if(linea == "")
            continue;

        //-----------------------------------
        // DECLARAR
        //-----------------------------------

        if(linea.find("declarar") == 0){

            int posIgual =linea.find('=');

            string variable =linea.substr(8,posIgual - 8);

            string expresion = linea.substr(posIgual + 1);

            expresion = quitarPuntoComa(expresion);

            string resultado = generarExpresion(expresion);

            agregarCuadruplo("=", resultado, "-", variable);
        }

        //-----------------------------------
        // SI
        //-----------------------------------

        else if(linea.find("si(") == 0){

            size_t ini = linea.find("(");

            size_t fin = linea.find(")");

            string condicion = linea.substr(ini + 1, fin - ini - 1);

            string temp = generarCondicion(condicion);

            string etiquetaFin = nuevaEtiqueta();

            pilaFinIf.push(etiquetaFin);

            agregarCuadruplo("IF_FALSE",temp,"-",etiquetaFin);
        }

        //-----------------------------------
        // SINO
        //-----------------------------------

        else if(linea.find("sino") == 0){

            string etiquetaNueva = nuevaEtiqueta();

            agregarCuadruplo("GOTO", "-", "-", etiquetaNueva);

            agregarCuadruplo("LABEL","-","-",pilaFinIf.top());

            pilaFinIf.pop();

            pilaFinIf.push(etiquetaNueva);
        }

        //-----------------------------------
        // MIENTRAS
        //-----------------------------------

        else if(linea.find("mientras(") == 0){

            string inicio =nuevaEtiqueta();

            string fin =nuevaEtiqueta();

            pilaInicioWhile.push(inicio);

            pilaFinWhile.push(fin);

            agregarCuadruplo("LABEL","-","-",inicio);

            size_t ini =linea.find("(");

            size_t finPar =linea.find(")");

            string condicion =linea.substr(ini + 1, finPar - ini - 1);

            string temp = generarCondicion(condicion);

            agregarCuadruplo("IF_FALSE", temp, "-", fin);
        }

        //-----------------------------------
        // CIERRE DE BLOQUES
        //-----------------------------------

        else if(linea == "}"){

            if(!pilaInicioWhile.empty()){

                agregarCuadruplo("GOTO","-","-",pilaInicioWhile.top());

                agregarCuadruplo("LABEL","-","-",pilaFinWhile.top());

                pilaInicioWhile.pop();
                pilaFinWhile.pop();
            }

            else if(!pilaFinIf.empty()){

                agregarCuadruplo("LABEL","-","-",pilaFinIf.top());

                pilaFinIf.pop();
            }
        }

        //-----------------------------------
        // ASIGNACION
        //-----------------------------------

        else if(linea.find("=") != string::npos){

            int posIgual = linea.find('=');

            string variable =linea.substr(0,posIgual);

            string expresion =linea.substr(posIgual + 1);

            expresion =quitarPuntoComa(expresion);

            string resultado =generarExpresion(expresion);

            agregarCuadruplo("=",resultado,"-",variable);
        }
    }
}

void mostrarCuadruplos(){

    cout << endl;
    cout << "CUARTETOS GENERADOS" << endl;
    cout << endl;

    cout<< "OP\t"<< "OP1\t"<< "OP2\t"<< "RES"<< endl;

    cout<< "-----------------------------------"<< endl;

    for(Cuadruplo c : cuadruplos){

        cout<< c.op << "\t"<< c.arg1 << "\t"<< c.arg2 << "\t"<< c.res<< endl;
    }
}



// MAIN


int main(){

    string codigo = R"(
    declarar a = 5;
    declarar b = 3;
    declarar c = 2;
    declarar resultado = 0;
    resultado = potencia(a,b);
    si(resultado > 50){
        resultado = resultado + raiz(resultado,2);
    }
    mientras(c < 6){
        resultado = resultado + sin(c);
        c = c + 1;
    }
    resultado = resultado + logb(8,2);
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

    analizarSemantica(codigo);
    mostrarErroresSemanticos();    

   if(erroreslexico==0 and errores.empty() and erroresSemanticos.empty()){
    generarCodigoIntermedio(codigo);
    mostrarCuadruplos();
    }
    return 0;
}

