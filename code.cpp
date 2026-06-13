#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Cipher{
public:
    virtual string encrypt(string plaintext) = 0;
    virtual string decrypt(string ciphertext) = 0;
    virtual ~Cipher(){};
};

class CaesarCipher : public Cipher{
    int shift;
public:
    CaesarCipher(int s){shift = s;}
    string encrypt(string text) override{
        string result = "";
        for(char c : text){
            if(isalpha(c)){
                char base = islower(c) ? 'a' : 'A';
                result += (c - base + shift) % 26 + base;
            }
            else
                result += c;
        }
        return result;
    }
    string decrypt(string text) override {
        string result = "";
        for (char c : text) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                result += (c - base - (shift % 26) + 26) % 26 + base;
            } 
            else 
                result += c;
        }
        return result;
    }
    
    void bruteForce(string ciphertext){
        int s;
       for(s = 1; s<26; s++){
        string result = "";
            for(char c : ciphertext){
                if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                result += (c - base - (s % 26) + 26) % 26 + base;
            } 
            else 
                result += c;
            }
            cout << "Shift " << s << " : " << result << endl;
        }
    }
};

class VigenereCipher : public Cipher{
    
};

int main() {
    CaesarCipher myCipher(3);

    string original = "abc xyz";
    
    string encrypted = myCipher.encrypt(original);
    string decrypted = myCipher.decrypt(encrypted);

    cout << "Original:  " << original << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    string interceptedMessage = "R Uxen Bcajfknaarnb!!"; 
    
    cout << "\n[ INTERCEPTED MESSAGE ]" << endl;
    cout << "Ciphertext: " << interceptedMessage << endl;

    myCipher.bruteForce(interceptedMessage);

    return 0;
}