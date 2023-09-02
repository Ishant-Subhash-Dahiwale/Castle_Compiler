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
    optional<string> value;
};


vector<Token> Tokenize(string str){





    //    for(char c:str){
    //        cout<<c<<endl;
    //    }
    //    vector<Token> d;
    //    return d;
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

    Tokenize(str);
    //    cout<<str<<endl;


    //    cout << argv[1] <<"  "<<argc  << endl;
    return EXIT_SUCCESS;
}
