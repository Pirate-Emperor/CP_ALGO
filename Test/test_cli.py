import os
import subprocess
import argparse
from prettytable import PrettyTable
from colorama import Fore, Style, init
import json

init(autoreset=True)

PASS_ICON = "✔️"  
FAIL_ICON = "❌"  

TEST_LOCATIONS_FILE = 'test_locations.json'

def load_test_locations():
    """Loads test locations from a JSON file."""
    if os.path.exists(TEST_LOCATIONS_FILE):
        with open(TEST_LOCATIONS_FILE, 'r') as file:
            return json.load(file)
    return {}

def save_test_location(name, path):
    """Saves a new test location to the JSON file."""
    normalized_path = os.path.normpath(path)
    locations = load_test_locations()
    locations[name] = path
    with open(TEST_LOCATIONS_FILE, 'w') as file:
        json.dump(locations, file)
    print(Fore.GREEN + f"Test location '{name}' added successfully.")

def compile_cpp_program(file_name):
    """Compiles the C++ program."""
    compile_command = f"g++ {file_name}.cpp -o {file_name}"
    process = subprocess.run(compile_command, shell=True)
    if process.returncode != 0:
        print(Fore.RED + "Compilation failed.")
        exit(1)

def run_test_cases(test_directory, file_name):
    """Runs the test cases and compares outputs."""
    if not os.path.exists(test_directory):
        print(Fore.RED + f"Directory does not exist: {test_directory}")
        return
    
    results_table = PrettyTable()
    results_table.field_names = ["Test Case", "Result", "Expected Output", "Your Output"]
    
    passed_count = 0
    failed_count = 0

    for filename in os.listdir(test_directory):
        if filename.endswith('.in'):
            input_file = os.path.join(test_directory, filename)
            output_file = os.path.join(test_directory, filename.replace('.in', '.ans'))
            
            
            with open(input_file) as infile, open('output.tmp', 'w') as outfile:
                subprocess.run([f'{file_name}'], stdin=infile, stdout=outfile)

            
            with open('output.tmp') as outfile, open(output_file) as ansfile:
                output = outfile.read().strip()
                expected = ansfile.read().strip()

            
            if output == expected:
                result = f"{Fore.GREEN}{PASS_ICON} {Fore.GREEN}Passed{Fore.WHITE}"
                passed_count += 1
            else:
                result = f"{Fore.RED}{FAIL_ICON} {Fore.RED}Failed{Fore.WHITE}"
                failed_count += 1

            
            results_table.add_row([filename, result, expected, output])

    print(results_table)
    
    summary_table = PrettyTable()
    summary_table.field_names = ["Total Test Cases", "Passed", "Failed", "Final Verdict"]

    total_cases = passed_count + failed_count
    final_verdict = f"{Fore.GREEN}{PASS_ICON} Accepted {Fore.WHITE}" if passed_count == total_cases else f"{Fore.RED}{FAIL_ICON} Rejected {Fore.WHITE}"
    passed_string = f"{Fore.GREEN} {passed_count} {Fore.WHITE}"
    failed_string = f"{Fore.RED} {failed_count} {Fore.WHITE}"

    summary_table.add_row([total_cases, passed_string, failed_string, final_verdict])
    print(summary_table)

def main():
    parser = argparse.ArgumentParser(description="CLI tool for testing C++ programs.")
    subparsers = parser.add_subparsers(dest='command')

    
    add_parser = subparsers.add_parser('add-test', help='Add a test location directory')
    add_parser.add_argument('test_name', type=str, help='The name to the test case')
    add_parser.add_argument('test_location', type=str, help='The path to the test case directory')
    

    
    run_parser = subparsers.add_parser('run-test', help='Run tests on the specified C++ file')
    run_parser.add_argument('test_name', type=str, help='The name of the test location to run')
    run_parser.add_argument('file_location', type=str, help='The location of the C++ file (without extension)')

    args = parser.parse_args()

    if args.command == 'add-test':
        save_test_location(args.test_name, args.test_location)
    elif args.command == 'run-test':
        locations = load_test_locations()
        if args.test_name in locations:
            compile_cpp_program(args.file_location)
            run_test_cases(locations[args.test_name], args.file_location)
        else:
            print(Fore.RED + f"Test location '{args.test_name}' not found.")

if __name__ == "__main__":
    main()
