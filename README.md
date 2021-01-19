# C++17 Features tests ![Language](https://img.shields.io/badge/language-C++17-orange.svg) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE.md)

This repository contains a list of **small tests** regarding enhancements brought by the **_c++17 standard_**.

Note : Well, some of them do not really have to do with C++17 but seemed nice to incorporate here.

## Concepts

Here is the list of the concepts that I have tested :
- [**Copy ellision**](copy-ellision.cpp)
- [**Chain evaluation order**](chain-evaluation-order.cpp)
- [**Remove an element in a std::vector in O(1) Timme**](fast-remove-in-vectors.cpp)
- [**Limit variables scope to if/else/switch statements**](init-in-selection.cpp)
- [**constexpr if : Compile-time evaluations**](constexpr-if.cpp)
- [**STL algorithms policies**](stl-algorithms-policies.cpp)
- [**Playing with std::unique**](playing-with-std-unique.cpp)
- [**compress/decompress strings using std::tuples**](tuples-string-compression.cpp)
- [**std::optional**](std-optional/)
  - [_Creation_](std-optional/optional-creation.cpp)
  - [_Accessing the stored value_](std-optional/optional-accessing.cpp)
  - [_Safely signalizing failure_](std-optional/optional-safe-failure.cpp)
  - [_Example(s) of use_](std-optional/optional-examples.cpp)
- [**std::variant**](std-variant/)
  - [_Creation_](std-variant/variant-creation.cpp)
  - [_Helper functions_](std-variant/variant-helpers.cpp)
  - [_Example(s) of use_](std-variant/variant-examples.cpp)
- [**std::any**](std-any/)
  - [_Creation and basics_](std-any/any-create-and-basics.cpp)
  - [_Example(s) of use_](std-any/any-examples.cpp)
- [**std::regex**](std-regex/)
- [**std::byte**](std-byte.cpp)
- [**std::map enhancements**](std-map-features/)
  - [_std::map::try_emplace_](std-map-features/try_emplace.cpp)
  - [_std::map::insert_or_assign_](std-map-features/insert-or-assign.cpp)
- [**std::empty, std::size(), std::data()**](non-member-container-functions.cpp)
- [**std::emplace() : the new receipe**](std-emplace.cpp)
- [**std::sample() algorithm**](std-sample.cpp)
- [**Mathematical additions**](math/)
  - [_std::gcd_ : Finally !](math/gcd.cpp)
  - [_std::lcm_](math/lcm.cpp)
  - [ std::clamp_](math/clamp.cpp)
- [**Implementing algorithms as std compliant iterators**](std-compliant-fibonacci.cpp)
- [**Memory handling of legacy APIs using smart pointers**](memory_handle_legacy_api.cpp)
- [**Redirect to file (or ignore) specific outputs**](redirect-or-ignore-cout.cpp)

## Benchmarks

Here is a list of benchmark that show the improvments of C++17 with numbers :
- [**Benchmark to highlight std::from_chars and std::to_chars efficiency**](string_conversion.cpp)
- [**Benchmark C++17 std::search overloads**](std-search/)
