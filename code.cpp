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

string readFile(string filename){

    ifstream fin(filename);

    if(!fin.is_open()){
        cout << "Error opening " << filename << endl;
        return "";
    }

    string text;
    string line;

    while(getline(fin, line)){
        text += line + '\n';
    }

    fin.close();

    return text;
}

void writeFile(string filename, string content){

    ofstream fout(filename);

    if(!fout.is_open()){
        cout << "Error creating " << filename << endl;
        return;
    }

    fout << content;

    fout.close();
}

void encryptCaesar(CaesarCipher& cipher){

    string text = readFile("message.txt");

    if(text.empty()) return;

    string encrypted = cipher.encrypt(text);

    writeFile("caesar_encrypted.txt", encrypted);

    cout << "\n✓ Encrypted Successfully!" << endl;
    cout << "Saved to caesar_encrypted.txt\n";
}

void decryptCaesar(CaesarCipher& cipher){

    string text = readFile("caesar_encrypted.txt");

    if(text.empty()) return;

    string decrypted = cipher.decrypt(text);

    writeFile("caesar_decrypted.txt", decrypted);

    cout << "\n✓ Decrypted Successfully!" << endl;
    cout << "Saved to caesar_decrypted.txt\n";
}

void encryptVigenere(VigenereCipher& cipher){

    string text = readFile("message.txt");

    if(text.empty()) return;

    string encrypted = cipher.encrypt(text);

    writeFile("vigenere_encrypted.txt", encrypted);

    cout << "\n✓ Encrypted Successfully!" << endl;
    cout << "Saved to vigenere_encrypted.txt\n";
}

void decryptVigenere(VigenereCipher& cipher){

    string text = readFile("vigenere_encrypted.txt");

    if(text.empty()) return;

    string decrypted = cipher.decrypt(text);

    writeFile("vigenere_decrypted.txt", decrypted);

    cout << "\n✓ Decrypted Successfully!" << endl;
    cout << "Saved to vigenere_decrypted.txt\n";
}

void bruteForceCaesar(){

    string text = readFile("caesar_encrypted.txt");

    if(text.empty()) return;

    CaesarCipher temp(0);

    cout << "\nPossible Decryptions:\n\n";

    temp.bruteForce(text);
}

void displayMenu() {

    cout << "\n=================================\n";
    cout << "      JADEBIT CIPHER TOOL\n";
    cout << "=================================\n\n";

    cout << "1. Encrypt File using Caesar\n";
    cout << "2. Decrypt Caesar File\n";
    cout << "3. Encrypt File using Vigenere\n";
    cout << "4. Decrypt Vigenere File\n";
    cout << "5. Caesar Brute Force\n";
    cout << "6. Exit\n\n";

    cout << "Enter your choice: ";
}

int main() {

    int shift;
    cout << "Enter Caesar shift : ";
    cin >> shift;

    cout << "Enter Keyword for Vigenere : ";
    string keyword;
    cin >> keyword;
    VigenereCipher myVigenere(keyword);
    CaesarCipher myCaesar(shift);

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
                cout << "\nByeee!!!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
}

    } while(choice != 6);

    return 0;
}