# C++17 Features tests ![Language](https://img.shields.io/badge/language-C++17-orange.svg) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE.md)

This repository contains a list of **small tests** regarding enhancements brought by the **_c++17 standard_**.

Note : Well, some of them do not really have to do with C++17 but seemed nice to incorporate here.

Here is the list of the concepts that I have tested :
- [**Copy ellision**](copy-ellision.cpp)
- [**Chain evaluation order**](chain-evaluation-order.cpp)
- [**Remove an element in a std::vector in O(1) Timme**](fast-remove-in-vectors.cpp)
- [**Limit variables scope to if/else/switch statements**](init-in-selection.cpp)
- [**constexpr if : Compile-time evaluations**](constexpr-if.cpp)
- [**STL algorithms policies**](stl-algorithms-policies.cpp)
- [**std::optional**](std-optional/)
  - [_Creation_](std-optional/optional-creation.cpp)
  - [_Accessing the stored value_](std-optional/optional-accessing.cpp)
  - [_Safely signalizing failure_](std-optional/optional-safe-failure.cpp)
  - [_Example(s) of use_](std-optional/optional-examples.cpp)
- [**std::variant**](std-variant/)
  - [_Creation_](std-variant/variant-creation.cpp)
  - [_Helper functions_](std-variant/variant-helpers.cpp)
  - [_Example(s) of use_](std-variant/variant-examples.cpp)
- [**std::any**]
  - Coming soon !