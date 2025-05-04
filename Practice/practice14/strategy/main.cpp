#include "ValidatorPro.h"
#include <iostream>
#include <string>
#include <memory>

class TextPrinter {
public:
    virtual void print() const = 0;
    virtual std::string getText() const = 0;
    virtual ~TextPrinter() = default;
};

class RawTextPrinter : public TextPrinter {
private:
    std::string text;

public:
    RawTextPrinter(const std::string& input) : text(input) {}

    void print() const override {
        std::cout << text;
    }

    std::string getText() const override {
        return text;
    }
};

class LowerCaseDecorator : public TextPrinter {
    std::shared_ptr<TextPrinter> base;
public:
    LowerCaseDecorator(std::shared_ptr<TextPrinter> b) : base(std::move(b)) {}

    std::string getText() const override {
        std::string s = base->getText();
        for (char& c : s) c = std::tolower(c);
        return s;
    }

    void print() const override {
        std::cout << getText();
    }
};

class UpperCaseDecorator : public TextPrinter {
    std::shared_ptr<TextPrinter> base;
public:
    UpperCaseDecorator(std::shared_ptr<TextPrinter> b) : base(std::move(b)) {}

    std::string getText() const override {
        std::string s = base->getText();
        for (char& c : s) c = std::toupper(c);
        return s;
    }

    void print() const override {
        std::cout << getText();
    }
};

class NoVowelDecorator : public TextPrinter {
    std::shared_ptr<TextPrinter> base;
public:
    NoVowelDecorator(std::shared_ptr<TextPrinter> b) : base(std::move(b)) {}

    std::string getText() const override {
        std::string s;
        for (char c : base->getText()) {
            if (std::string("aeiouAEIOU").find(c) == std::string::npos)
                s += c;
        }
        return s;
    }

    void print() const override {
        std::cout << getText();
    }
};

class CensorDecorator : public TextPrinter { // my get valid string function can easily do this in a way better way but this is more like a demonstration that it works
    std::shared_ptr<TextPrinter> base;
public:
    CensorDecorator(std::shared_ptr<TextPrinter> b) : base(std::move(b)) {}

    std::string getText() const override {
        std::string s = base->getText();
        size_t pos;
        while ((pos = s.find("curse")) != std::string::npos) {
            s.replace(pos, 5, "***");
        }
        return s;
    }

    void print() const override {
        std::cout << getText();
    }
};

class ReverseDecorator : public TextPrinter {
    std::shared_ptr<TextPrinter> base;
public:
    ReverseDecorator(std::shared_ptr<TextPrinter> b) : base(std::move(b)) {}

    std::string getText() const override {
        std::string s = base->getText();
        std::reverse(s.begin(), s.end());
        return s;
    }

    void print() const override {
        std::cout << getText();
    }
};

class RemoveAllSpacesDecorator : public TextPrinter {
    std::shared_ptr<TextPrinter> base;
public:
    RemoveAllSpacesDecorator(std::shared_ptr<TextPrinter> b) : base(std::move(b)) {}    
    
    std::string getText() const override {
        std::string s = base->getText();
       
        s.erase(std::remove_if(s.begin(), s.end(), 
                [](unsigned char ch) { return std::isspace(ch); }), 
                s.end());
        return s;
    }
    
    void print() const override {
        std::cout << getText();
    }
};


int main(){
    

    std::cout << "Welcome to text decorator demo!" << std::endl;
    std::cout << "Please enter any text: ";
    std::string userInput;
    userInput = getValidString();
    std::shared_ptr<TextPrinter> printer = std::make_shared<RawTextPrinter>(userInput);
    
    while (true) {
        std::cout << "\nYour text: ";
        printer->print();

        std::cout << "\nNow what would you like to do with it?(1-8)" << std::endl;
        std::cout << "1. Make it lower case" << std::endl;
        std::cout << "2. Make it upper case" << std::endl;
        std::cout << "3. Reverse it" << std::endl;
        std::cout << "4. Get rid of vowels" << std::endl;
        std::cout << "5. Censor bad words out" << std::endl;
        std::cout << "6. Trim all spaces" << std::endl;
        std::cout << "7. Recall original text" << std::endl;
        std::cout << "8. Exit" << std::endl;


        int choice = getValidNumber(1, 8);
        if (choice == 1) {
            printer = std::make_shared<LowerCaseDecorator>(printer);
        } else if (choice == 2) {
            printer = std::make_shared<UpperCaseDecorator>(printer);
        } else if (choice == 3) {
            printer = std::make_shared<ReverseDecorator>(printer);
            
        } else if (choice == 4) {
            printer = std::make_shared<NoVowelDecorator>(printer);
            
        } else if (choice == 5) {
            printer = std::make_shared<CensorDecorator>(printer);
        } else if (choice == 6) {
            printer = std::make_shared<RemoveAllSpacesDecorator>(printer);
        } else if (choice == 7) {
            std::cout << "Original text: " << userInput << std::endl;
        } else if (choice == 8) {
            break;
        } else{
            std::cout << "Impossible to get here territory" << std::endl;
        }


    }
    std::cout << "Final output: ";
    printer->print();
    std::cout << std::endl;
    std::cout << "Thank you for using the text decorator demo!" << std::endl;
    std::cout << "Goodbye!" << std::endl;

    return 0;
}