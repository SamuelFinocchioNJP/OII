#include <iostream>
#include <stack>

#define debugno
using namespace std;

/**
    Returns true if open bracket,
    false if closed bracket
**/
bool check_bracket ( char b ) {
    switch ( b ) {
        case '(':
        case '{':
        case '<':
        case '[':
            return true;
    }
    return false;
}

bool matching_brackets ( char b1, char b2 ) {
    if ( b1 == '(' && b2 == ')' )
        return true;

    if ( b1 == '[' && b2 == ']' )
        return true;

    if ( b1 == '{' && b2 == '}' )
        return true;

    if ( b1 == '<' && b2 == '>' )
        return true;

    return false;
}

int main( void )
{
    /// Input redirection
    freopen( "input.txt", "r", stdin );
    freopen( "output.txt", "w", stdout );

    int brackets_amount;
    cin >> brackets_amount;
    stack <char> bracket_stack;

    /// Brackets string
    string source;
    cin >> source;

    /// Bracket to be checked
    char current_bracket;

    bool correct = true;

    /** Reading and evauating brackets in input **/
    for ( int i = 0; i < brackets_amount && correct; i++ ) {
        current_bracket = source.at( i );
        /// If it is an opening bracket, pushes it to the stack
        if ( check_bracket( current_bracket ) ) {
            bracket_stack.push( current_bracket );

            #ifdef debug
            cout << "Added " << current_bracket << endl;
            #endif // debug
        }
        else {
            if ( bracket_stack.empty() )
                correct = false;
            else {
                char popped = bracket_stack.top();
                bracket_stack.pop();

                #ifdef debug
                cout << "Checking " << popped << " " << current_bracket << endl;
                #endif // debug

                if ( !matching_brackets( popped, current_bracket ) ) {
                    #ifdef debug
                    cout << "Error " << bracket_stack.top() << " " << current_bracket << endl;
                    #endif // debug

                    bracket_stack.pop();
                    correct = false;
                }
            }
        }
    }

    if ( !correct || !bracket_stack.empty() )
        cout << "malformata";
    else
        cout << "corretta";

    return 0;
}
