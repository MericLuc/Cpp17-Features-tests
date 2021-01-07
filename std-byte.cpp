/************************************************************
 *                         STD::BYTE                        *
 ************************************************************/

/*!
 * @brief 
 * 
 * std::byte is a type introduced in C++17 that implements
 * the concept of bytes.
 * 
 * You can use it to access raw memory of objects - just like you
 * would with char, but std::byte is not a character nor an
 * arithmetic type - just a collection of bits.
 * 
 * That said, it becomes clear why the only defined operators
 * are the bitwise ones.
 * 
 * More informations here
 * https://en.cppreference.com/w/cpp/types/byte
 */

/*!
 * @note std::byte is defined as an enum
 *       enum class byte : unsigned char {} ;
 * 
 *       It allows for numeric value n conversion to
 *       std::byte value using std::byte{n}, due to C++17 
 *       relaxed enum class initialization rules. 
 */

#include <iostream>
#include <cstddef>

int main()
{
    std::byte myByte{42}, myByte2;

    // std::to_integer to convert to IntegerType
    std::cout << "Byte value : " << std::to_integer<int>(myByte) << "\n";

    // Convert an integer to a byte
    int myInt{142};
    myByte2 = std::byte{myInt};

    // Some bitwise operators
    myByte <<= 1;
    myByte2 = myByte << 1;

    return EXIT_SUCCESS;
}