# Supported Equation Types

This system is designed to evaluate mathematical expressions represented as binary trees. Look at examples below and in Example_of_Equations.txt for what equations are allowed. It supports the following equation types and features:

## Equals Sign:
Not required but can be accepted.

## Operators:

*   **Basic Arithmetic:** `+` (addition), `-` (subtraction), `*` (multiplication), `/` (division)
*   **Exponentiation:** `^` (power)

## Operands:

*   **Integers:** Whole numbers (e.g., `3`, `-5`, `100`)
*   **Decimal Numbers:** Numbers with decimal points (e.g., `3.14`, `2.5`, `-0.75`)

## Structure and Syntax:

*   **Infix Notation:** Equations are written in the standard infix notation (e.g., `2 + 3`).
*   **Operator Precedence:** The system respects standard operator precedence (PEMDAS/BODMAS).  Exponentiation has the highest precedence, followed by multiplication and division, and then addition and subtraction.
*   **Parentheses:** Parentheses `()` can be used to override the default operator precedence and group expressions (e.g., `(5 + 3) * 2`).
*   **Negative Numbers:** The system correctly handles negative numbers, including cases where a negative sign is the first character in the expression or follows an opening parenthesis or another operator (e.g. `-3 + 5`, `2 * (-4)`).

## Examples of Valid Equations:

*   `3 + 5`
*   `3 + 5 * 2`
*   `(3 + 5) * 2`
*   `-3 + 5`
*   `2 ^ 3`
*   `6.3 / 2.1`
*   `1 + 1 + 1 + 1 + 1`
*   `4 - 3 - 2 - 1 + 67`
*   `3.5 + 2.5`
*   `8 - 2 * 3`
*   `7.1 * 3 + 5.4`
*   `12.8 / 4.0`
*   `(5 + 3) * 2.1`
*   `10 / 5 + 3 * 2`
*   `9 + (4 * 2)`
*   `15.5 - (3.5 * 2)`
*   `(8.5 + 4.5) / 3.0`
*   `5 * 3.2 - 4`
*   `9.6 / 2 + 6`
*   `(7.8 + 2.2) * 3`
*   `12 - 4.5 + 3.2`
*   `(5 + 7) / (4 + 2)`
*   `6 * (2.3 + 4.7)`
*   `20 - 5 * 3 + 6.5`
*   `4 + 5.2 * (2.1 - 1.0)`
*   `9.2 - 4 * 2 + 3`
*   `77 ^ 3`
*   `-5 + 2` (or `-5 - - 2`)

## Limitations:

*   The system relies on tokenizing the input string, so correct spacing and valid characters are expected.
*   Error handling for invalid expressions (e.g., division by zero, invalid operators) may not be comprehensive.
*   The system is set up for binary operations. More complex functions (e.g. sin, cos, tan) are not natively supported.