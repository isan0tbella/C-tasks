#include "std_lib_facilities.h"
class Token
{
public:
    char kind;
    int value;

    Token(char ch) : kind{ch}, value{0} {}
    Token(char ch, int val) : kind{ch}, value{val} {}
};

class Token_stream
{
public:
    Token_stream();
    Token get();
    void putback(Token t);

private:
    bool full{false};
    Token buffer;
};

Token_stream::Token_stream() : buffer{0} 
{
}

void Token_stream::putback(Token t)
{
    if (full)
        error("putback() into a full buffer");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }   

    char ch;
    cin >> ch;

    switch (ch)     
    {
    case ';':
    case 'q':
    case '(':
    case ')':
    case '|':
    case '&':
    case '^':
    case '~':
    case '!':
        return Token{ch};

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':   
    {
        cin.putback(ch);
        int val;
        cin >> val; 
        return Token{'8', val};
    }

    default:
        error("Bad token");
    }
}

Token_stream ts;

int OR();

int primary()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case '(':
    {
        int d = OR();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }
    case '8':   
        return t.value;
    case '~':
        return ~primary();
    case '!': {
        int chislo = primary();  
        string inverted_number{};
        while (chislo>0) {
            int ost = chislo % 2;
            if (ost == 0) inverted_number +='1';
            else inverted_number +='0';
            chislo = chislo/2; 
        }
        int val{0};
        reverse(inverted_number.begin(), inverted_number.end());
        for (char bit : inverted_number) 
        {
            val = val * 2 + (bit - '0');
        }       
        return val;
    }   
    default:
        error("primary expected");
    }
}

int AND()
{
    int left = primary();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '&':
            left &= primary();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

int XOR()
{
    int left = AND();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '^':
            left ^= AND();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

int OR()
{
    int left = XOR();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '|':
            left |= XOR();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

void print_bin(int n)
{
    // if (n == 0)
    // {
    //     cout << "= 0";
    //     return;
    // }    
    cout << "= " << n << endl;
    // string binary = "";
    
    // while (n > 0)   
    // {
    //     if (n % 2 == 0)
    //     {
    //         binary = "0" + binary;
    //     }
    //     else
    //     {    
    //         binary = "1" + binary;
    //     }
    //     n = n / 2;
    // }
    // cout << " = " << binary << endl;
}   


int main()
try
{
    int val = 0;
    
    while (cin)
    {
        Token t = ts.get();

        if (t.kind == 'q')
            break;
        if (t.kind == ';')
        {
            print_bin(val);
        }
        else
        {
            ts.putback(t);
            val = OR();
        }
    }
}
catch (exception& e)
{
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Oops: unknown exception!\n";
    return 2;
}