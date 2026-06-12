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
};

int main() {
    CaesarCipher myCipher(3);

    string original = "I wanna be me me me!!";
    
    string encrypted = myCipher.encrypt(original);
    string decrypted = myCipher.decrypt(encrypted);

    cout << "Original:  " << original << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}