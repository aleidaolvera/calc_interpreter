//
//  helpers.h
//  pl-a1
//
//  Created by Aleida Olvera on 10/15/18.
//  Copyright © 2018 Aleida Olvera. All rights reserved.
//

#ifndef helpers_h
#define helpers_h
#include <string>

using namespace std;

// check if string is float or not
bool isFloat(const string& string);

// check if string is num or not
bool isNum(const string& s);

// check if string is num or not
bool isVar(const string& s);

// check if string is num or not
bool isOp(const string& string);

// check if string is '(' or ')' or not
int isParen(const string& s);

class Token {
    
public:
    string type;
    string token_type; // characterizes type of token
    float value; // if int / float return value
    string result; // store result of operations
    
    // instantiates Token
    Token() {
        result = "";
        type = "";
        token_type = "";
    }
    Token(string token) {
        if(token == "#t" || token == "#f") {
            token_type = "LITERAL";
            type = setType(token);
        }
        else if(isOp(token)){
            token_type = "OPERATOR";
            type = setType(token);
        }
        else if(isNum(token)) {
            token_type = "LITERAL";
            value = stoi(token);
            type = "i";
        }
        else if(isFloat(token)) {
            token_type = "LITERAL";
            value = stof(token);
            type = ".";
        }
        else if(isParen(token)) {
            token_type = "PARENTHESES";
            type = setType(token);
            
        }
        
    }
    // returns Token type
    string setType(string string) {
        if ( string.length() > 1 ) {
            if (string[0] == '>' && string[1] == '=') return "equal_greater_than";
            else if (string[0] == '<' && string[1] == '=') return "equal_less_than";
            else if(string[0] == '=' && string[1] == '=') return "equal_op";
            else if(string[0] == '!' && string[1] == '=') return "log_not";
            else if(string[0] == '&' && string[1] == '&') return "log_and";
            else if(string[0] == '|' && string[1] == '|') return "log_or";
            else if(string[0] == 'o' && string[1] == 'r') return "log_or";
            else if(string[0] == 'a' && string[1] == 'n' && string[2] == 'd') return "log_and";
            else if(string[0] == 'A' && string[1] == 'N' && string[2] == 'D') return "log_and";
            else if(string[0] == 'n' && string[1] == 'o' && string[2] == 't') return "log_not";
            else if(string[0] == 'N' && string[1] == 'O' && string[2] == 'T') return "log_not";
            else if (string[0] == '#' && string[1] == 't') return "bool_true";
            else if (string[0] == '#' && string[1] == 'T') return "bool_true";
            else if (string[0] == '#' && string[1] == 'f') return "bool_false";
            else if (string[0] == '#' && string[1] == 'F') return "bool_false";
        }
        if (string[0] == '+') return "plus_op";
        else if (string[0] == '-') return "sub_op";
        else if (string[0] == '*') return "mult_op";
        else if (string[0] == '/') return "div_op";
        else if (string[0] == '=') return "equal_op";
        else if (string[0] == '>') return "greater_than";
        else if (string[0] == '<') return "less_than";
        else if (string[0] == '(') return "left_par";
        else if (string[0] == ')') return "right_par";
        
        return "";
    }
    // returns value of Token, if int or float
    double getValue() {
        return value;
    }
    
    // if it is bool, grab bool
    string getBool() {
        if (type == "bool_false") return "false";
        else return "true";
    }
    
    void operator = ( const Token &t ) {
        this->type = t.type;
        this->token_type = t.token_type;
        this->value = t.value;
        this->result = t.result;
    }
    
    
};


/*****************************************************
 *************INSERT DISCLOSURES HERE *********
 ******************************************************/


/*
 PUTTING MY OWN STUFF HERE AND THEN CLEANING UP LATER!!
 
 
 i. Arithmetic Operations
 +, -, *, /
 ii. Relational
 >, <, >=, <=, =
 iii. Logical
 OR, AND, NOT
 iv. Literals
 Integers, floats, #t, #f
 v. Operations
 ()
 */

typedef string OPERATOR;
typedef string LITERAL;
typedef string OPERAND;
typedef string LEFT_PAR;
typedef string RIGHT_PAR;



/*****************
 DEFINE CONSTANTS
 ******************/

// You may wish to define some token codes for your tokenizer categories

typedef int NUMBER;
typedef int NAME;
const int  NAMELENG = 25;      /* Maximum length of a name */
const int  MAXNAMES = 500;     /* Maximum number of different names */
const int  MAXINPUT = 40000;     /* Maximum length of an input */
const char*   PROMPT = "calc_interpreter> ";
const char*   PROMPT2 = "--> ";
const char  COMMENTCHAR = '%';
const char  ENDOFINPUT = '$';   // use as sentinel to mark end of input
const int   TABCODE = 9;        /* in ASCII */



/****************
 DECLARE GLOBAL STUFF
 ******************/

int stringToInt(string);
string intToString(int);
string charToString(char);


char userinput[MAXINPUT];//array to store the user input
int  inputleng, pos; // indices for tokenizer



int  enterIfScope = 0; // antiquated ... holds input buffer until matching endif
string currentOutput = "Output: No statements";



/**************************************************
 **********   Some Tokenizer Helpers below  *********
 * Feel free to insert tokenizer code here (or in other file)*
 ***************************************************/
// some helpers for the lexer, that you may or may not want to use ...

bool isFloat(const string& string){
    string::const_iterator string_it = string.begin();
    bool decimalPoint = false;
    int minSize = 0;
    if(string.size()>0 && (string[0] == '-' || string[0] == '+')){
        string_it++;
        minSize++;
    }
    while(string_it != string.end()){
        if(*string_it == '.'){
            if(!decimalPoint) decimalPoint = true;
            else break;
        }else if(!isdigit(*string_it) && ((*string_it!='f') || string_it+1 != string.end() || !decimalPoint)){
            break;
        }
        ++string_it;
    }
    if (!decimalPoint) {
        return false;
    }
    else {
        return string.size()>minSize && string_it == string.end();
    }
}

// check if string is num or not
bool isNum(const string& s){
    int start = 0;
    if(s[0] == '-' || s[0] == '+') {
        start = 1;
    }
    for(int i = start; i < s.length(); i++) {
        if (!( '0' <= s[i] && s[i] <= '9') ) {
            return false;
        }
    }
    return true;
}

// check if string is num or not
bool isVar(const string& s){
    for(int i = 0; i < s.length(); i++) {
        if( !((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A')) ) {
            return false;
        }
    }
    
    return true;
}

// check if string is num or not
bool isOp(const string& string){
    if (string.length() >= 2) {
        if (string[0] == '>' && string[1] == '=') return true;
        else if (string[0] == '<' && string[1] == '=') return true;
        else if(string[0] == '=' && string[1] == '=') return true;
        else if(string[0] == '!' && string[1] == '=') return true;
        else if(string[0] == '&' && string[1] == '&') return true;
        else if(string[0] == '|' && string[1] == '|') return true;
        else if(string[0] == 'o' && string[1] == 'r') return true;
        else if(string[0] == 'a' && string[1] == 'n' && string[2] == 'd') return true;
        else if(string[0] == 'A' && string[1] == 'N' && string[2] == 'D') return true;
        else if(string[0] == 'n' && string[1] == 'o' && string[2] == 't') return true;
        else if(string[0] == 'N' && string[1] == 'O' && string[2] == 'T') return true;
        else if (string[0] == '#' && string[1] == 't') return true;
        else if (string[0] == '#' && string[1] == 'T') return true;
        else if (string[0] == '#' && string[1] == 'f') return true;
        else if (string[0] == '#' && string[1] == 'F') return true;
        else return false;
    }
    else {
        if (string[0] == '+') return true;
        else if (string[0] == '-') return true;
        else if (string[0] == '*') return true;
        else if (string[0] == '/') return true;
        else if (string[0] == '=') return true;
        else if (string[0] == '>') return true;
        else if (string[0] == '<') return true;
        else return false;
    }
    
    
}

string operator_type(const string& string) {
    if ( string.length() > 1 ) {
        if (string[0] == '>' && string[1] == '=') return "equal_greater_than";
        else if (string[0] == '<' && string[1] == '=') return "equal_less_than";
        else if(string[0] == '=' && string[1] == '=') return "equal_op";
        else if(string[0] == '!' && string[1] == '=') return "log_not";
        else if(string[0] == '&' && string[1] == '&') return "log_and_op";
        else if(string[0] == '|' && string[1] == '|') return "log_or";
        else if(string[0] == 'o' && string[1] == 'r') return "log_or";
        else if(string[0] == 'a' && string[1] == 'n' && string[2] == 'd') return "log_and";
        else if(string[0] == 'n' && string[1] == 'o' && string[2] == 't') return "log_not";
        else if (string[0] == '#' && string[1] == 't') return "bool_true";
        else if (string[0] == '#' && string[1] == 'f') return "bool_false";
    }
    if (string[0] == '+') return "plus_op";
    else if (string[0] == '-') return "sub_op";
    else if (string[0] == '*') return "mult_op";
    else if (string[0] == '/') return "div_op";
    else if (string[0] == '=') return "equal_op";
    else if (string[0] == '>') return "greater_than";
    else if (string[0] == '<') return "less_than";
    else if (string[0] == '(') return "left_par";
    else if (string[0] == ')') return "right_par";
    
    return "";
}

int isParen(const string& s)
{
    if ((s[0] == '(') || (s[0] == ')'))
        return 1;
    else
        return 0;
}



/*********************************
 LOW-LEVEL HELPER METHODS FOR READING INPUT
 *********************************/
void nextchar(char& c) // pulls next char
{
    scanf("%c", &c);
    if (c == COMMENTCHAR)
    {
        while (c != '\n')
            scanf("%c", &c);
    }
}

// skips over blanks
int skipblanks(int p)
{
    while (userinput[p] == ' ')
        ++p;
    return p;
}

int isDelim(char c) // checks char for particular delimiters
{
    return ((c == '(') || (c == ')') || (c == ' ') || (c == COMMENTCHAR) || (c == '\n'));
}

int matches(int s, int leng, char* nm) // lookahead checks input for matching string. Helps to check for keywords.
{
    int i = 0;
    
    while (i < leng)
    {
        
        if (userinput[s] != nm[i]) {
            return 0;
        }
        ++i;
        ++s;
    }
    if (!isDelim(userinput[s]))
        return 0;
    
    return 1;
}/* matches */

int matches(int s, int leng, char* nm, bool testing) // lookahead checks input for matching string. Helps to check for keywords.
{
    int i = 0;
    
    while (i < leng)
    {
        if (userinput[s] != nm[i]) {
            return 0;
        }
        ++i;
        ++s;
    }
    
    
    return 1;
}/* matches */



// reads input from console and stores in global userinput[]
void readInput()
{
    char  c;
    cout << PROMPT;
    pos = 0;
    do
    {
        ++pos;
        if (pos == MAXINPUT)
        {
            cout << "User input too long\n";
            exit(1);
        }
        nextchar(c);
        if (c == '\n')
            userinput[pos] = ' ';// or space
        else
            userinput[pos] = c;
        
    } while (c != '\n');
    inputleng = pos + 1;
    userinput[pos+1] = ENDOFINPUT; // sentinel
    // input buffer is now filled, reset pos to 1 (later in reader()) and begin parse
}


// Reads input until end
void reader()
{
    do
    {
        readInput();
        pos = skipblanks(1); // reset pos for tokenizer
    } while (pos > inputleng-1); // ignore blank lines
}

/*********************************
 END OF LOW-LEVEL HELPER METHODS FOR READING INPUT
 *********************************/

/* my own code! */

string eval_queue(queue<Token> &expression, string result){
    result = "";
    if(expression.empty()) {
        throw invalid_argument("-- You must enter a finished expression.");
    }
    else {
        Token eval_me = expression.front();
        expression.pop();
        // cout << "We are attempting to evaluate expression at token [" << eval_me.type << "]\n";
        if (eval_me.type == "left_par") {
            result = eval_queue(expression, result);
            //  cout << "we have exited parentheses with a result of [" << result << "]\n";
            if (expression.empty()) {
                throw invalid_argument("-- No matching parentheses was found.");
            }
            eval_me = expression.front();
            expression.pop();
            if(eval_me.type == "right_par") {
                return result;
            }
            else {
                throw invalid_argument("-- There an error handling parentheses expression.");
            }
            
        }
        else if(eval_me.token_type == "OPERATOR"){
            if(eval_me.type == "log_and") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isNum(eval2)) || (isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    if(eval1 == eval2){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else if(( eval1 == "false" || eval1 == "true" ) && ( eval2 == "false" || eval2 == "true" )) {
                    if (eval1 == eval2) {
                        return "true";
                    }
                    else if(eval1 != eval2){
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `logical and` for literals of different types.");
                }
            }
            else if(eval_me.type == "log_or") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if(( eval1 == "false" || eval1 == "true" ) && ( eval2 == "false" || eval2 == "true" )) {
                    if (eval1 == "true" || eval2 == "true") {
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `logical or` over non-boolean literals.");
                }
            }
            else if(eval_me.type == "log_not") {
                string eval1 = eval_queue(expression, result);
                if(eval1 == "false") {
                    return "true";
                }
                else if(eval1 == "true") {
                    return "false";
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `logical not` over non-boolean literals.");
                }
            }
            else if(eval_me.type == "equal_op") {
                // cout << "inside equal_op" << endl;
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                // cout << "eval1 [" << eval1 << "] eval2 [" << eval2 << "]\n";
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    if(stof(eval1) == stof(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                    
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    if(stoi(eval1) == stoi(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `equal-to` relational operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "greater_than") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    if(stof(eval1) > stof(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                    
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    if(stoi(eval1) > stoi(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `greater-than` relational operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "less_than") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    if(stof(eval1) < stof(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                    
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    if(stoi(eval1) < stoi(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `less-than` relational operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "equal_greater_than") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    if(stof(eval1) >= stof(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                    
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    if(stoi(eval1) >= stoi(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `greater-than / equal-to` relational operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "equal_less_than") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    if(stof(eval1) <= stof(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                    
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    if(stoi(eval1) <= stoi(eval2)){
                        return "true";
                    }
                    else {
                        return "false";
                    }
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `less-than / equal-to` relational operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "plus_op") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    float evaluate = stof(eval1) + stof(eval2);
                    return to_string(evaluate);
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    int evaluate = stoi(eval1) + stoi(eval2);
                    return to_string(evaluate);
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `plus operation` for non numerical literals.");
                }
            }
            else if(eval_me.type == "sub_op") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    float evaluate = stof(eval1) - stof(eval2);
                    return to_string(evaluate);
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    int evaluate = stoi(eval1) - stoi(eval2);
                    return to_string(evaluate);
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `sub.` operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "mult_op") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    float evaluate = stof(eval1) * stof(eval2);
                    return to_string(evaluate);
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    int evaluate = stoi(eval1) * stoi(eval2);
                    return to_string(evaluate);
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `mult.` operation for non numerical literals.");
                }
            }
            else if(eval_me.type == "div_op") {
                string eval1 = eval_queue(expression, result);
                string eval2 = eval_queue(expression, result);
                if((isNum(eval1) && isFloat(eval2)) || (isFloat(eval1) && isFloat(eval2))) {
                    float evaluate = stof(eval1) / stof(eval2);
                    return to_string(evaluate);
                }
                else if(isNum(eval1) && isNum(eval2)) {
                    int evaluate = stoi(eval1) / stoi(eval2);
                    return to_string(evaluate);
                }
                else {
                    throw invalid_argument("-- Cannot evaluate `div. operation` for non numerical literals.");
                }
            }
        }
        else if(eval_me.token_type == "LITERAL") {
            if(eval_me.type == "."){
                return to_string(eval_me.getValue());
            }
            else if(eval_me.type == "i"){
                return to_string(int(eval_me.getValue()));
            }
            else if(eval_me.type == "bool_false" || eval_me.type == "bool_true") {
                // cout << "we are returning a LITERAL of type boolean..\n";
                return eval_me.getBool();
            }
        }
        else if (eval_me.type == "right_par") {
            return result;
        }
        else if(eval_me.type != "right_par") {
            throw invalid_argument("-- Expression could not be valid because of a missing operand/parenthesis.");
        }
        else {
            cout << eval_me.type << endl;
            throw invalid_argument("-- An invalid token was entered.");
        }
    }
    return result;
}

queue<Token> generate_tokens(vector<string> tokens) {
    vector <string> tokenList;
    queue <Token> token_class;
    string currentToken = "";
    string type = "";
    for (unsigned j = 0; j < tokens.size(); j++) {
        currentToken = tokens.at(j);
        if(currentToken == "quit") {
            exit(0);
        }
        else if(currentToken == "\n" || currentToken == "" || currentToken == " ") {
            continue;
        }
        else if(isParen(currentToken)) {
            token_class.push(*new Token(currentToken));
            type = "parenthesis";
            tokenList.push_back(type);
        }
        else if(isOp(currentToken)) {
            token_class.push(*new Token(currentToken));
            type = operator_type(currentToken);
            tokenList.push_back(type);
        }
        else if (isFloat(currentToken)) {
            token_class.push(*new Token(currentToken));
            type = "float";
            tokenList.push_back("float");
        }
        else if (isNum(currentToken)) {
            type = "int";
            token_class.push(*new Token(currentToken));
            tokenList.push_back(type);
        }
        else if(isVar(currentToken)) {
            type = "var";
            token_class.push(*new Token(currentToken));
            tokenList.push_back(type);
        }
        else {
            string error = "[" + currentToken + "] is not a valid token.\n";
            throw invalid_argument(error);
        }
        
    }
    return token_class;
}


queue<Token> tokenize() {
    vector<string> tokens;
    string token = "";
    token.clear();
    for (int i = 1; i <= inputleng;  i++)// mimic input to confirm userinput array is populated.
        if (*&userinput[i] == ' ' || *&userinput[i] == '\n' || *&userinput[i] == '('  || *&userinput[i] == ')') {
            if(*&userinput[i] == '(') {token = "(";}
            if(*&userinput[i] == ')') {
                if(token.size() > 0) {
                    tokens.push_back(token);
                }
                tokens.push_back(")");
                token = "";
            }
            if(*&userinput[i] == '\n') token = "";
            else {
                tokens.push_back(token);
                token = "";
            }
        }
        else {
            token += userinput[i];
        }
    /***************************************************
     **************** DEBUG CODE: **********************
     Checks the tokens that were stored in the vector
     ***************************************************
     
     cout << "here are all the tokens:\n";
     
     for (unsigned j = 0; j < tokens.size(); j++) {
     cout << "\t" << j + 1 << " [" << tokens.at(j) << "] \n";
     }
     */
    return generate_tokens(tokens);
}



#endif /* helpers_h */
