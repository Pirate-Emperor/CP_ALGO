import os
import subprocess
from prettytable import PrettyTable
from colorama import Fore, Style, init

init(autoreset=True)

PASS_ICON = "✔️ "  
FAIL_ICON = "❌"  

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
    
    
    table = PrettyTable()
    table.field_names = ["Test Case", "Result", "Expected Output", "Your Output"]

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
                result = f"{Fore.GREEN}{PASS_ICON} Passed {Fore.WHITE}"
                passed_count += 1
            else:
                result = f"{Fore.RED}{FAIL_ICON} Failed {Fore.WHITE}"
                failed_count += 1
            
            Fore.WHITE
            table.add_row([filename, result, expected, output])

    
    print(table)
    summary_table = PrettyTable()
    summary_table.field_names = ["Total Test Cases", "Passed", "Failed", "Final Verdict"]

    total_cases = passed_count + failed_count
    final_verdict = f"{Fore.GREEN}{PASS_ICON} Accepted {Fore.WHITE}" if passed_count == total_cases else f"{Fore.RED}{FAIL_ICON} Rejected {Fore.WHITE}"
    passed_string = f"{Fore.GREEN} {passed_count} {Fore.WHITE}"
    failed_string = f"{Fore.RED} {failed_count} {Fore.WHITE}"
    summary_table.add_row([total_cases, passed_string, failed_string, final_verdict])

    
    print(summary_table)

if __name__ == "__main__":
    directory = r"D:\Z_CONTEST\ICPC\Problems\2017\icpc2017data\A-airport"
    file_name = r"D:\Z_CONTEST\CP_ALGO\Try\\icpc_a"
    compile_cpp_program(file_name)
    run_test_cases(directory, file_name)
