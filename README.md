# Matrix Library

## Overview

This project is a static library for matrix operations implemented in C. It provides functions for creating, manipulating, and performing calculations on numerical matrices. This library is designed to help developers handle matrix computations efficiently, with a focus on accuracy and performance.

---

## Features

- **Matrix Creation and Deletion**
   - Create matrices with specified dimensions.
   - Free up memory after use.

- **Matrix Operations**
   - Addition, subtraction, and multiplication (with another matrix or a scalar).
   - Transpose matrices.
   - Calculate determinants, minors, and algebraic complements.
   - Find the inverse of a matrix.

- **Comparison**
   - Check if two matrices are equal to 7 decimal places.

- **Error Handling**
   - Comprehensive return codes for incorrect operations or invalid matrices.

---

## Getting Started

### Prerequisites

- **C Compiler**: GCC with C11 standard support.
- **Libraries**: [Check](https://libcheck.github.io/check/) for unit testing.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/le0ruslan/matrix-library-cpp.git
   cd matrix-library-cpp
   ```
   
2. Build the library and tests:
   ```bash
   make all
   ```

3. Run unit tests:
   ```bash
   make test
   ```
   
4. Generate a coverage report:
   ```bash
   make gcov_report
   ```

---

## Getting Started
Include s21_matrix.h in your project and link the compiled static library s21_matrix.a.
   ```c++
#include "s21_matrix.h"

int main() {
matrix_t A, B, result;
s21_create_matrix(3, 3, &A);
s21_create_matrix(3, 3, &B);
// Initialize matrices A and B here
s21_sum_matrix(&A, &B, &result);
// Use the result matrix
s21_remove_matrix(&A);
s21_remove_matrix(&B);
s21_remove_matrix(&result);
return 0;
}
   ```

---

## Functions

| No. | Function                                | Description                                                    |
|-----|----------------------------------------|----------------------------------------------------------------|
| 1   | `s21_create_matrix	`                   | Creates a matrix with given dimensions.               |
| 2   | `s21_remove_matrix`       | Frees the allocated memory for a matrix.                                      |
| 3   | `s21_eq_matrix`         | Compares two matrices for equality.                                         |
| 4   | `s21_sum_matrix`        | Adds two matrices.                                      |
| 5   | `s21_sub_matrix`        | Subtracts one matrix from another.    |
| 6   | `s21_mult_number`         | 	Multiplies a matrix by a scalar.                                              |
| 7   | `s21_mult_matrix`         | 	Multiplies two matrices.                          |
| 8   | `s21_transpose`        | Transposes a matrix.            |
| 9   | `s21_determinant`       | Calculates the determinant of a square matrix.  |
| 10  | `s21_calc_complements`| Computes the matrix of algebraic complements.         |
| 11  | `s21_inverse_matrix`        | Calculates the inverse of a matrix (if determinant ≠ 0).                            |
 |

---

## File Structure
* src/
  - Contains the implementation of the library functions.
* tests/
  - Includes unit tests written using the Check library.
* Makefile
  - Automates building the library, running tests, and generating reports.

---

## Testing
* The project uses the Check library for unit tests. Run the tests using:
   ```bash
   make test
   ```

* Check the coverage report with:
   ```bash
   make gcov_report
   ```
The coverage report will be generated as an HTML file in the gcov_report/ directory.

---

## Project Requirements
* Accuracy: All calculations should be accurate up to 6 decimal places.
  * Return Codes: Functions return codes for easy error handling:
  - `0` - OK
  - `1` - Incorrect matrix
  - `2` - Calculation error
