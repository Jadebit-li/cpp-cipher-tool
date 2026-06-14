#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
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

void encryptCaesar(CaesarCipher& cipher){
    ifstream fin("message.txt");
    if(!fin.is_open()){
        cout << "Error: unable to open message.txt";
        return;
    }
    string line, text;
    while(getline(fin, line)){
        text += line + '\n';
    }
    fin.close();
    string encrypted = cipher.encrypt(text);

    ofstream fout("caesar_encrypted.txt");
    fout << encrypted;
    fout.close();

    cout << "Encrypted Successfully!!" << endl;
}

void encryptVigenere(VigenereCipher& cipher){
    ifstream fin("message.txt");
    if(!fin.is_open()){
        cout << "Error: unable to open message.txt";
        return;
    }
    string line, text;
    while(getline(fin, line)){
        text += line + '\n';
    }
    fin.close();
    string encrypted = cipher.encrypt(text);

    ofstream fout("vigenere_encrypted.txt");
    fout << encrypted;
    fout.close();

    cout << "Encrypted Successfully!!" << endl;
}

void decryptCaesar(CaesarCipher& cipher){
    ifstream fin("caesar_encrypted.txt");
    if(!fin.is_open()){
        cout << "Error: unable to open caesar_encrypted.txt";
        return;
    }
    string line, text;
    while(getline(fin, line)){
        text += line + '\n';
    }
    fin.close();
    string decrypted = cipher.decrypt(text);

    ofstream fout("caesar_decrypted.txt");
    fout << decrypted;
    fout.close();

    cout << "Decrypted Successfully!!" << endl;
}

void decryptVigenere(VigenereCipher& cipher){
    ifstream fin("vigenere_encrypted.txt");
    if(!fin.is_open()){
        cout << "Error: unable to open vigenere_encrypted.txt";
        return;
    }
    string line, text;
    while(getline(fin, line)){
        text += line + '\n';
    }
    fin.close();
    string decrypted = cipher.decrypt(text);

    ofstream fout("vigenere_decrypted.txt");
    fout << decrypted;
    fout.close();

    cout << "Decrypted Successfully!!" << endl;
}

void bruteForceCaesar(){

    ifstream fin("caesar_encrypted.txt");

    if(!fin.is_open()){
        cout << "Error opening caesar_encrypted.txt\n";
        return;
    }

    string text, line;

    while(getline(fin,line)){
        text += line + '\n';
    }

    fin.close();

    CaesarCipher temp(0);

    cout << "\nPossible decryptions:\n\n";

    temp.bruteForce(text);
}

void displayMenu() {
    cout << "\n=================================\n";
    cout << "      JADEBIT CIPHER TOOL\n";
    cout << "=================================\n\n";

    cout << "1. Encrypt File using Caesar\n";
    cout << "2. Decrypt Caesar File\n";
    cout << "3. Encrypt File using Vigenère\n";
    cout << "4. Decrypt Vigenère File\n";
    cout << "5. Caesar Brute Force\n";
    cout << "6. Exit\n\n";

    cout << "Enter your choice: ";
}

int main() {

    VigenereCipher myVigenere("Eren");
    CaesarCipher myCaesar(3);

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch(choice){

            case 1:
                encryptCaesar(myCaesar);
                break;

            case 2:
                decryptCaesar(myCaesar);
                break;

            case 3:
                encryptVigenere(myVigenere);
                break;

            case 4:
                decryptVigenere(myVigenere);
                break;

            case 5:
                bruteForceCaesar();
                break;

            case 6:
                cout << "\nGoodbye!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
}

    } while(choice != 6);

    return 0;
}