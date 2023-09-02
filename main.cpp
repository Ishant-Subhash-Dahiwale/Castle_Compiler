#include <iostream>

#include <sstream>
#include<string>
#include<optional>
#include<fstream>
#include <vector>
using namespace std;

enum class TokenType{
    _return,
    _semi,
    int_lit
};

struct Token{
    TokenType type;
    optional<string> value {};
};


vector<Token> Tokenize(string& str){
    string buf;
    vector<Token> token;


    for (int i  = 0; i < str.length();i++) {
        char c= str.at(i);
        if(isalpha(c)){
            buf.push_back(c);
            i++;
            while(isalnum(str.at(i)))
            {

                buf.push_back(str.at(i));
                i++;

            }
            i--;
            if(buf == "return"){
                    token.push_back({.type = TokenType::_return });
                    buf.clear();
                    continue;
            }
            else{
                    cerr<<" an error "<<buf<<endl;
                    exit(EXIT_FAILURE);
            }

        }
        else if(isdigit(str.at(i))){
            buf.push_back(str.at(i));
            i++;
            while(isdigit(str.at(i))){
                    buf.push_back(str.at(i));
                    i++;
            }
            i--;
            token.push_back({.type = TokenType::int_lit , .value = buf});
            buf.clear();
        }
        else if(c == ';'){
            token.push_back({.type = TokenType::_semi});

        }
        else if(isspace(str.at(i))){
            continue;
        }
        else{
            cerr<<"an error here"<<endl;
            exit(EXIT_FAILURE);
        }
    }



        return token;
}

string token_to_asm(vector<Token>& tokens){
        stringstream op;

        op<<"global _start \n_start: \n";

        for (int i = 0; i < tokens.size();i++) {
        const Token token = tokens.at(i);

        if(token.type == TokenType::_return){

            if(i+1 <tokens.size() && tokens.at(i+1).type == TokenType::int_lit ){

                    if(i+2 <tokens.size() && tokens.at(i+2).type == TokenType::_semi ){
                        op<<"   mov rax, 60 \n";
                        op<<"   mov rdi, "<<tokens.at(i+1).value.value()<<"\n";
                        op<<"   syscall";
                    }
            }

        }

        }
        return op.str();
}



int main(int argc , char* argv[])
{
    if(argc != 2){
        cerr<<"INCORRECT USAGE . CORRECT USAGE..."<<endl;
        cerr<<"castle <input.castle>"<<endl;
        return EXIT_FAILURE;
    }
    string str;
    {
        stringstream content;
        fstream input(argv[1],ios::in);
        content << input.rdbuf();
        str = content.str();
    }

    vector<Token> thing  =   Tokenize(str);
//        cout<<str<<endl;
//    cout<<token_to_asm(thing)<<endl;

    {
        fstream output("../test.asm",ios::out);
        output<<token_to_asm(thing);
    }

    system("nasm -felf64 ../test.asm ");
    system("ld -o out ../test.o");
//    system("./out");

    //    cout << argv[1] <<"  "<<argc  << endl;
    return EXIT_SUCCESS;
}
