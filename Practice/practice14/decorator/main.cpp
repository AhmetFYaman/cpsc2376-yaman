#include "ValidatorPro.h"
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>




class GetCost {
public:
    virtual double getCost() const = 0;
    virtual std::string getDescription() const = 0;
    virtual ~GetCost() = default;
};

class BaseCost : public GetCost {
    double cost;
public:
    BaseCost(double c) : cost(c) {}

    double getCost() const override {
        return cost;
    }

    std::string getDescription() const override {
        return "Base Cost";
    }
};

class TaxDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    TaxDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() * 1.2; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + 20% Tax";
    }
};

class ShippingDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    ShippingDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + 5.0; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + $5.00 Shipping";
    }
};

class DiscountDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    DiscountDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() * 0.9; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " - 10% Discount";
    }
};

class ManualLaborDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    ManualLaborDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + 7.5; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + $7.50 Manual Labor";
    }
};

class PollutionFeeDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    PollutionFeeDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + (base->getCost() * 0.05); 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + 5% Pollution Fee";
    }
};

class DonationDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    DonationDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + 2.0; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + $2.00 Donation";
    }
};

class WorldHungerDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    WorldHungerDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + 3.0; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + $3.00 World Hunger Donation";
    }
};

class PersonalHungerDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    PersonalHungerDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + 495000.0; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + $495000.00 Personal Hunger Fee";
    }
};

class WorldThirstDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
public:
    WorldThirstDecorator(std::shared_ptr<GetCost> b) : base(std::move(b)) {}

    double getCost() const override {
        return base->getCost() + 2.5; 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + $2.50 World Thirst Donation";
    }
};

class TipDecorator : public GetCost {
    std::shared_ptr<GetCost> base;
    double tipPercentage;
public:
    TipDecorator(std::shared_ptr<GetCost> b, double percentage) : base(std::move(b)), tipPercentage(percentage) {}

    double getCost() const override {
        return base->getCost() * (1.0 + tipPercentage/100.0); 
    }

    std::string getDescription() const override {
        return base->getDescription() + " + " + std::to_string(tipPercentage) + "% Tip";
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);
    
    double baseCost{0.0};
    printCharByChar("Welcome to your cart, I am your personal cost calculator!\n");
    printCharByChar("It seems like your cart holds a bunch of items costing you... (write it down): ");
    baseCost = getValidNumber(0.01, 100000000000.0);
    std::cout << "$" << baseCost;
    printCharByChar(" base cost.\n\n");

    printCharByChar("Please stay calm and apply the extra charges and stay with us through the process.\n");
    printCharByChar("We believe in transparency, so we will show you the cost at every step.\n");
    printCharByChar("And we know you have the courage to stick with us till the end!\n");
    printCharByChar("minimum charges to apply before checkout: 3\n\n");

    std::shared_ptr<GetCost> costCalculator = std::make_shared<BaseCost>(baseCost);
    int chargesApplied = 0;
    int minChargesApplied = 3;
    int disattempts = 0;
    std::string mymeal = "The most expensive meal in the world is a multi-course\n "
    "meal served in a space balloon, costing $495,000. It's a collaboration between Alchemist's \n"
    "Michelin-starred chef, Rasmus Munk, and SpaceVIP! ";
    
    while (true) {
        std::cout << "\nCurrent total: $" << costCalculator->getCost() << " (" << costCalculator->getDescription() << ")\n\n";
        
        printCharByChar("Please pick the charge that you will add this time:\n");
        printCharByChar("1. Tax (20%)\n");
        printCharByChar("2. Shipping Fee ($5.00)\n");
        printCharByChar("3. Discount of the Day! (10% off)\n");
        printCharByChar("4. Manual Labor ($7.50)\n");
        printCharByChar("5. Fighting Pollution (5%)\n");
        printCharByChar("6. Donations to us ($2.00)\n");
        printCharByChar("7. Save World Hunger ($3.00)\n");
        printCharByChar("8. Save my hunger ($1.00)\n");
        printCharByChar("9. Save World Thirst ($2.50)\n");
        printCharByChar("10. Add Tip\n");
        printCharByChar("11. Finish and checkout\n\n");
        
        int choice = getValidNumber(1, 11);
        
        if (choice == 11) {
            if (chargesApplied < minChargesApplied) {
                printCharByChar("\nSorry, you must apply at least " + std::to_string(minChargesApplied) + 
                               " charges before checkout. You've only applied " + 
                               std::to_string(chargesApplied) + " so far.\n\n");
                continue;
            }
            break;
        }
        
        chargesApplied++;
        
        double beforeCost = costCalculator->getCost();
        

            if(choice == 1){
                costCalculator = std::make_shared<TaxDecorator>(costCalculator);
                
            }else if(choice == 2){
                costCalculator = std::make_shared<ShippingDecorator>(costCalculator);
                
            }else if(choice ==  3){
                
                if (disattempts > 0){
                    printCharByChar("Oh no! Sorry the Discount Machine IS Broken! Please try another day!\n");
                    chargesApplied--;
                    continue;
                }
                costCalculator = std::make_shared<DiscountDecorator>(costCalculator);
                disattempts++;
                
            }else if(choice == 4){
                costCalculator = std::make_shared<ManualLaborDecorator>(costCalculator);
                
            }else if(choice == 5){
                costCalculator = std::make_shared<PollutionFeeDecorator>(costCalculator);
                
            }else if(choice == 6){
                costCalculator = std::make_shared<DonationDecorator>(costCalculator);
                
            }else if(choice == 7){
                costCalculator = std::make_shared<WorldHungerDecorator>(costCalculator);
                
            }else if(choice == 8){
                costCalculator = std::make_shared<PersonalHungerDecorator>(costCalculator);
                printCharByChar("Oh my, thank you for paying for my (1.00) special meal of: \n");
                printCharByChar(mymeal);

                printCharByChar("You seriously didn't have to do that, but I appreciate it!\n");
                
            }else if(choice == 9){
                costCalculator = std::make_shared<WorldThirstDecorator>(costCalculator);
                
            }else if(choice == 10){
                printCharByChar("How many p//cents would you like to tip: ");
                double tipPercentage = getValidNumber(0.0, 10000.0);
                printCharByChar("Oh my! thanks a lot, you didn't have to tip me " + std::to_string(tipPercentage) + "%, how generous of you! \n");
                costCalculator = std::make_shared<TipDecorator>(costCalculator, tipPercentage);
                
            }else{
                printCharByChar("Mission Immpossible territory \n");
                break;
            }
        
        double afterCost = costCalculator->getCost();
        printCharByChar("\nCharge applied! Cost changed from $" + std::to_string(beforeCost) + 
                       " to $" + std::to_string(afterCost) + ".\n");
        printCharByChar("That's a difference of $" + std::to_string(afterCost - beforeCost) + "!\n");
    }
    
    printCharByChar("\n\nThank you for your patience! Your final cost is $" + 
                   std::to_string(costCalculator->getCost()) + ".\n");
    printCharByChar("Here's the breakdown of your charges: " + costCalculator->getDescription() + "\n");
    printCharByChar("We hope you enjoyed our transparent pricing system!\n");
    printCharByChar("Please come again!\n");
    
    return 0;
}