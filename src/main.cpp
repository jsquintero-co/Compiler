//prueba del lexer
#include <iostream>
#include "lexer.h"

using namespace std;

// Función auxiliar en main para imprimir el enum como texto legible
string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT_LIT:     return "INT_LIT";
        case TokenType::VAR_ID:      return "VAR_ID";
        case TokenType::ASSIGN:      return "ASSIGN";
        case TokenType::PLUS:        return "PLUS";
        case TokenType::SEMICOLON:   return "SEMICOLON";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default:                     return "UNKNOWN";
    }
}

int main() {
    // Código de prueba que simula un archivo fuente
    string sourceCode = "x = 10 + 5;\ntotal = x + 42;";

    cout << "--- CODIGO FUENTE DE PRUEBA ---\n";
    cout << sourceCode << "\n\n";
    cout << "--- SALIDA DEL LEXER ---\n";

    // Creamos la instancia de nuestro Lexer
    Lexer lexer(sourceCode);
    Token token;

    // Pedimos tokens iterativamente hasta encontrar el fin del archivo
    do {
        token = lexer.nextToken();
        cout << "[Linea " << token.line << "] "
             << "Tipo: " << tokenTypeToString(token.type)
             << "\t| Lexema: \"" << token.lexeme << "\"\n";
    } while (token.type != TokenType::END_OF_FILE);

    return 0;
}