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
    string keyword;
    string repeatKeyword(string text){
        string repkey = "";
        int index = 0;
        for(char c : text){
            if(isalpha(c)){
                repkey += keyword[index % keyword.length()];
                index++;
            }
            else 
                repkey += c;    
        }
        return repkey;
    }
public:
    VigenereCipher(string key) {
        keyword = "";
        // Convert the keyword to uppercase to make the math easier later
        for (char c : key) {
            if (isalpha(c)) {
                keyword += toupper(c);
            }
        }
    }
    string encrypt(string text) override{
        string result = "";
        string key = repeatKeyword(text);
        for(int i = 0; i<text.length(); i++){
            char c = text[i];
            if(isalpha(c)){
                char base = islower(c) ? 'a' : 'A';
                int shift = key[i] - 'A';
                result += (c - base + shift) % 26 + base;
            }
            else
                result += c;
        }
        return result;
    }

    string decrypt(string text) override{
        string result = "";
        string key = repeatKeyword(text);
        for(int i = 0; i<text.length(); i++){
            char c = text[i];
            if(isalpha(c)){
                char base = islower(c) ? 'a' : 'A';
                int shift = key[i] - 'A';
                result += (c - base - (shift%26) + 26) % 26 + base;
            }
            else
                result += c;
        }
        return result;
    }
    

};

int main() {
    CaesarCipher myCipher(3);

    string coriginal = "abc xyz";
    
    string cencrypted = myCipher.encrypt(coriginal);
    string cdecrypted = myCipher.decrypt(cencrypted);

    cout << "Original:  " << coriginal << endl;
    cout << "Encrypted: " << cencrypted << endl;
    cout << "Decrypted: " << cdecrypted << endl;

    string interceptedMessage = "R Uxen Bcajfknaarnb!!"; 
    
    cout << "\n[ INTERCEPTED MESSAGE ]" << endl;
    cout << "Ciphertext: " << interceptedMessage << endl;

    myCipher.bruteForce(interceptedMessage);

    cout << "=== Vigenere Cipher Tool ===" << endl;

    VigenereCipher myVigenere("Eren");
    string voriginal = "Attack on Titan!";
    
    string vencrypted = myVigenere.encrypt(voriginal);
    string vdecrypted = myVigenere.decrypt(vencrypted);

    cout << "Keyword:   Eren" << endl;
    cout << "Original:  " << voriginal << endl;
    cout << "Encrypted: " << vencrypted << endl;
    cout << "Decrypted: " << vdecrypted << endl;

    return 0;
}