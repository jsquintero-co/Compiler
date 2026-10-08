//Un lexer básico que pueda identificar argumentos básicos
#include "lexer.h"
#include <cctype> //Analizar caracteres individuales


using namespace std;

        Lexer::Lexer(string source){
            code = source;
            cursor = 0;
            line = 1;
        }


        //Verifica una cadena de caracteres
        char Lexer::peek(){
            if(cursor >= code.size()){
                return '\0'; /*Si está en el  final de la cadena, devuelve un fin
                de la cadena*/ 
            }
            return code[cursor]; //Si no, devuelve el caracter donde está el cursor
        }

        //Devuelve el carácter actual y avance un caracter más
        char Lexer::advance(){
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

        void Lexer::skipWhitespace(){
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

        
        Token Lexer::nextToken(){
            skipWhitespace(); //Verifica que le vale monda si hay espacios en el buffer
            char c = advance(); //Verifica el caracter actual

            //Verifica que sea un número literal (con uno o más dígitos)
            if(isdigit(c)){
                string lexeme = ""; //Un string vacio para añadirle los digitos
                lexeme += c; //Se guarda el primer digito
                
                while(isdigit(peek())){ //Verifica que el siguiente sea digito tambien
                    lexeme += advance(); //Guarda el siguiente digito (si hay)
                }

                return{TokenType::INT_LIT, lexeme, line};
            }

            //Verifica que sea una variable
            if(isalpha(c) || c == '_'){
                string lexeme = "";
                lexeme += c;
                while(isalnum(peek() || peek() == '_')){
                    lexeme += advance();
                }
                return {TokenType::VAR_ID, lexeme, line};
            }

            //Verifica cada opción de argumento
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



