#include <iostream>
#include <string.h>

int Char_To_Int(char data);
std::string Invert_Binary(std::string org);
int Binary_To_Decimal(std::string bin_data);
std::string Decimal_To_Binary(int decimal_value, int word_length);

int main(int argc, char const *argv[])
{
    std::string binary_val = "010";
    int dec_value = 0;
    std::cout << "Decimal Value: " << Binary_To_Decimal(binary_val) << std::endl;
    std::cout << "Binary Value: " << Decimal_To_Binary(dec_value, 8) << std::endl;
    return 0;
}

/*
 * Returns the integer value of a char representation of a number.
 * Does not convert negative numbers. Returns -1 for any error.
 */
int Char_To_Int(char data)
{
    int result = 0;

    // ----- Validate
    if ((int)data < 48 || (int)data > 57)
    {
        // Out of Bounds
        return -1;
    }

    // ----- Calculate Int Value
    int int_ascii_value = (int)data;
    result = int_ascii_value - 48;

    return result;
}

/*
 * Inverts a Binary Number from Negative to Positive for Positive to Negative
 */
std::string Invert_Binary(std::string org)
{
    std::string result = "";
    int carry = 1;

    // ----- Flip Bits
    for (int i = 0; i < org.length(); i++)
    {
        if (org[i] == '0')
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }

    // ----- Add Carry
    for (int i = result.length() - 1; i >= 0; i--)
    {
        if (result[i] == '1' && carry == 1)
        {
            result[i] = '0';
        }
        else if (result[i] == '0' && carry == 1)
        {
            result[i] = '1';
            carry = 0;
        }
    }
    return result;
}

/*
 * Returns the decimal value of a binary number.
 */
int Binary_To_Decimal(std::string bin_data)
{
    // ----- Validate Input
    for (int i = 0; i < bin_data.length(); i++)
    {
        if (bin_data[i] != '0' && bin_data[i] != '1')
        {
            std::cout << "INVALID BINARY DATA ERROR.";
        }
    }

    // ----- Initiate
    std::string data = bin_data;
    const int word_size = data.length();
    const char sign = data[0];

    // ----- Invert Binary if Negative Number
    if (sign == '1')
    {
        data = Invert_Binary(data);
    }

    // ----- Calculate Decimal
    int result = 0;
    int binary_index = 1;
    for (int i = data.length() - 1; i >= 0; i--)
    {
        int temp = Char_To_Int(data[i]);
        temp *= binary_index;
        result += temp;
        binary_index *= 2;
    }

    // ----- Set Decimal Negative if Binary Input was Negative
    if (sign == '1')
    {
        return result * -1;
    }

    return result;
}

/*
 * Returns the binary number of a decimal value.
 */
std::string Decimal_To_Binary(int decimal_value, int word_length)
{
    int division_value = std::abs(decimal_value);
    std::string result = "";
    std::string temp_result = "";

    // ----- Build Binary Signature
    while (division_value != 0)
    {
        int remainder = division_value % 2;
        if (remainder == 0)
        {
            temp_result += '0';
        }
        else
        {
            temp_result += '1';
        }
        division_value /= 2;
    }

    // ----- Add Sign Bit and Zero Padding to Word Length
    for (int i = temp_result.length(); i < word_length; i++)
    {
        temp_result += '0';
    }

    // ----- Set Result as Inverse and Spacing
    for (int i = temp_result.length() - 1; i >= 0; i--)
    {
        result += temp_result[i];
        if (i % 4 == 0)
        {
            result += ' ';
        }
    }

    // ----- Invert Binary if Negative Number
    if (decimal_value < 0)
    {
        result = Invert_Binary(result);
    }

    return result;
}
