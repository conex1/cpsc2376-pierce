# Identified Bugs and Fixes

## 1. sumRange Function
- **Bug**: Off-by-one error in loop condition.
- **Issue**: The loop ran from `start` to `end - 1`, excluding the `end` value.
- **Fix**: Changed loop condition to `i <= end`.

## 2. containsNegative Function
- **Bug 1**: Loop ran out of bounds.
  - **Issue**: Loop used `i <= numbers.size()`, accessing invalid indices.
  - **Fix**: Corrected loop condition to `i < numbers.size()`.
- **Bug 2**: Incorrect condition checked for positive numbers.
  - **Issue**: Returned true if any positive number was found.
  - **Fix**: Changed condition to check for `numbers[i] < 0`.

## 3. findMax Function
- **Bug 1**: Returned 0 for empty vectors.
  - **Issue**: Invalid return value for empty input.
  - **Fix**: Threw `std::runtime_error` for empty vectors.
- **Bug 2**: Loop ran out of bounds.
  - **Issue**: Loop used `i <= numbers.size()`, leading to invalid access.
  - **Fix**: Corrected loop condition to `i < numbers.size()`.