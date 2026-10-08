//Un lexer básico que pueda identificar argumentos básicos
#include <string>
#include <cctype> //Analizar caracteres individuales


using namespace std;
enum class TokenType {
    INT_LIT,
    VAR_ID,
    ASSIGN,
    PLUS,
    SEMICOLON,
    END_OF_FILE
};

size_t cursor = 0;

string code;

int line = 1;

//Verifica una cadena de caracteres
char peek(){
    if(cursor >= code.size()){
        return '\0'; /*Si está en el  final de la cadena, devuelve un fin
        de la cadena*/ 
    }
    return code[cursor]; //Si no, devuelve el caracter donde está el cursor
}

//Devuelve el carácter actual y avance un caracter más
char advance(){
    if (cursor >= code.size()){
        return '\0';
    }
    char aux = code[cursor];
    if(aux == '\n'){
        line++;
    }
    cursor++;
    return aux;
}

void skipWhitespace(){
    while(true){
        char c = peek(); // Mira que hay sin aún moverse
        // Si hay espacio de tabulación o salto de linea
        if(c == ' ' || c == '\t' || c == '\n'){
            advance();
        } else{
            break; //De lo contrario termina
       }
    }
}

struct Token{
    TokenType type;
    string lexeme;
    int line;
};

Token nextToken(){
    skipWhitespace(); //Verifica que le vale monda si hay espacios en el buffer
    char c = advance(); //Verifica el caracter actual

    if(isdigit(c)){
        string lexeme = ""; //Un string vacio para añadirle los digitos
        lexeme += c; //Se guarda el primer digito
        
        while(isdigit(peek())){ //Verifica que el siguiente sea digito tambien
            lexeme += advance(); //Guarda el siguiente digito (si hay)
        }

        return{TokenType::INT_LIT, lexeme, line};
    }

    switch(c){
        case '=': 
            return{TokenType::ASSIGN, "=", line};
        case '+':
            return{TokenType::PLUS, "+", line};
        case ';':
            return{TokenType::SEMICOLON, ";", line};
        case '\0': 
            return {TokenType::END_OF_FILE, "", line};
        default:
            return{TokenType::END_OF_FILE, string(1,c), line};
    }
}