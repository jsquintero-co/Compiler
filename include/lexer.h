#ifndef LEXER_H
#define LEXER_H

#include <string>
using namespace std;

// 1. Definición de tipos de tokens
enum class TokenType {
    INT_LIT,
    VAR_ID,
    ASSIGN,
    PLUS,
    SEMICOLON,
    END_OF_FILE
};

// 2. Estructura de un Token
struct Token {
    TokenType type;
    string lexeme;
    int line;
};

// 3. Declaración de la clase Lexer
class Lexer {
private:
    string code;
    size_t cursor;
    int line;

    // Métodos privados de apoyo (solo firmas)
    char peek();
    char advance();
    void skipWhitespace();

public:
    // Constructor
    Lexer(string source);

    // Método principal para obtener el siguiente token
    Token nextToken();
};

#endif