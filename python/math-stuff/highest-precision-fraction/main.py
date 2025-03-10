from fractions import Fraction

def decimal_to_fraction(decimal_value):
    fraction = Fraction(decimal_value).limit_denominator(10**6)  # High precision
    return fraction.numerator, fraction.denominator

# Example usage
decimal_number = float(input("Enter a decimal number: "))
numerator, denominator = decimal_to_fraction(decimal_number)
print(f"The fraction representation of {decimal_number} is {numerator}/{denominator}")
