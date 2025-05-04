#include <iostream>
#include <memory>

// Base Writer interface
class Writer {
public:
    virtual void write() const = 0;
    virtual ~Writer() = default;
};

// PlainWriter outputs raw text
class PlainWriter : public Writer {
public:
    void write() const override {
        std::cout << "[TEXT]";
    }
};

// TimestampDecorator adds [Start] and [End]
class TimestampDecorator : public Writer {
    std::shared_ptr<Writer> base;
public:
    TimestampDecorator(std::shared_ptr<Writer> b) : base(std::move(b)) {}

    void write() const override {
        std::cout << "[Start]";
        base->write();
        std::cout << "[End]";
    }
};

// FancyDecorator adds * before and after output
class FancyDecorator : public Writer {
    std::shared_ptr<Writer> base;
public:
    FancyDecorator(std::shared_ptr<Writer> b) : base(std::move(b)) {}

    void write() const override {
        std::cout << "*";
        base->write();
        std::cout << "*";
    }
};

int main() {
    std::shared_ptr<Writer> w = std::make_shared<FancyDecorator>(
        std::make_shared<TimestampDecorator>(
            std::make_shared<PlainWriter>()));

    w->write();  // Expected output: *[Start][TEXT][End]*
    std::cout << "\n";
}
