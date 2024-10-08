# Test Case Runner CLI Tool

## Overview

The Test Case Runner CLI Tool is a command-line interface designed to simplify the process of running test cases against a C++ program. This tool allows users to add directories of test cases, run those test cases, and view the results in a clear and organized manner.

## Features

- **Add Test**: Specify the location of the test cases directory.
- **Run Test**: Execute test cases on a specified C++ program and compare outputs with expected results.
- **Output**: Visually appealing results displayed in the console with colors and tables for better readability.

## Prerequisites

- Python 3.x
- GCC (GNU Compiler Collection) for compiling C++ programs

## Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. Ensure you have the necessary permissions to run the script:
   ```bash
   chmod +x test_cli.py
   ```

## Usage

### Adding Test Cases Directory

To add the location of your test cases directory, use the following command:

```bash
python test_cli.py add-test <test-location>
```

**Example:**
```bash
python test_cli.py add-test "A-airport" "D:\Z_CONTEST\ICPC\Problems\2017\icpc2017data\A-airport"
```

### Running Test Cases

To run the test cases on a specified C++ program, use the following command:

```bash
python test_cli.py run-test <test-name> <file-location>
```

**Example:**
```bash
python test_cli.py run-test "A-airport" "D:\Z_CONTEST\CP_ALGO\Try\icpc_a"
```

## Output

The output will include a summary table indicating the number of test cases passed and failed, along with a final verdict (Accepted or Rejected).

### Example Output:
```
==========================
Test Case Results
==========================
| Test Case   | Result   |
|-------------|----------|
| case1.in    | Passed   |
| case2.in    | Failed   |
==========================
Summary:
- Passed: 1
- Failed: 1
Final Verdict: Rejected
```

## Example Usage

1. **Add Test Cases Directory**:
   ```bash
   python test_cli.py add-test "A-airport" "D:/Z_CONTEST/ICPC/Problems/2017/icpc2017data/A-airport"
   ```

2. **Run Test Cases**:
   ```bash
   python test_cli.py run-test "A-airport" "D:\Z_CONTEST\CP_ALGO\Try\icpc_a"
   ```

## License

This project is licensed under the MIT License.