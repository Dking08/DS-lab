import subprocess
import os
import json
import datetime
import random
import re
import sys

CONFIG_FILE = "c_test_config.json"

def load_config():
    try:
        with open(CONFIG_FILE, "r") as f:
            return json.load(f)
    except FileNotFoundError:
        return {"input_sets": {}, "c_files": {}, "last_used": None}

def save_config(config):
    with open(CONFIG_FILE, "w") as f:
        json.dump(config, f, indent=2)

def compile_c_file(c_file):
    exe_file = os.path.splitext(c_file)[0]
    compile_command = f"gcc {c_file} -o {exe_file}"
    
    try:
        result = subprocess.run(compile_command, check=True, shell=True, capture_output=True, text=True)
        print(f"Successfully compiled {c_file} to {exe_file}")
        if result.stderr:
            print("Compiler warnings:")
            print(result.stderr)
        return exe_file
    except subprocess.CalledProcessError as e:
        print(f"Error: Failed to compile {c_file}")
        print("Compiler output:")
        print(e.output)
        return None

def process_input(input_str):
    # Handle random number generation
    rand_pattern = r'rand\s+(\d+)(?:\s+(\d+))?'
    match = re.match(rand_pattern, input_str)
    if match:
        if match.group(2):
            min_val, max_val = int(match.group(1)), int(match.group(2))
        else:
            min_val, max_val = 0, int(match.group(1))
        return str(random.randint(min_val, max_val))

    # Handle for loop
    for_pattern = r'for\s+(\d+):\s+(.*)'
    match = re.match(for_pattern, input_str)
    if match:
        count = int(match.group(1))
        sub_input = match.group(2)
        return '\n'.join([process_input(sub_input) for _ in range(count)])

    # Handle range generation
    range_pattern = r'range\s+(\d+)(?:\s+(\d+))?(?:\s+(\d+))?'
    match = re.match(range_pattern, input_str)
    if match:
        if match.group(3):
            start, end, step = map(int, match.groups())
        elif match.group(2):
            start, end, step = int(match.group(1)), int(match.group(2)), 1
        else:
            start, end, step = 0, int(match.group(1)), 1
        return '\n'.join(map(str, range(start, end, step)))

    # Handle repeat command
    repeat_pattern = r'repeat\s+(\d+)\s+(.*)'
    match = re.match(repeat_pattern, input_str)
    if match:
        count = int(match.group(1))
        value = match.group(2)
        return '\n'.join([value] * count)

    # Handle shuffle command
    shuffle_pattern = r'shuffle\s+(.*)'
    match = re.match(shuffle_pattern, input_str)
    if match:
        items = match.group(1).split()
        random.shuffle(items)
        return ' '.join(items)

    # Handle choice command
    choice_pattern = r'choice\s+(.*)'
    match = re.match(choice_pattern, input_str)
    if match:
        items = match.group(1).split()
        return random.choice(items)

    # Handle file input command
    file_input_pattern = r'file\s+(.*)'
    match = re.match(file_input_pattern, input_str)
    if match:
        filename = match.group(1)
        try:
            with open(filename, 'r') as f:
                return f.read().strip()
        except FileNotFoundError:
            print(f"Error: File '{filename}' not found.")
            return ''

    return input_str

def run_executable(exe_file, inputs):
    try:
        processed_inputs = [process_input(input_str) for input_str in inputs]
        flattened_inputs = '\n'.join(processed_inputs).split('\n')
        process = subprocess.Popen(exe_file, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate(input='\n'.join(flattened_inputs))
        
        print("Program output:")
        print(stdout)
        
        if stderr:
            print("Error output:")
            print(stderr)
        
        return process.returncode
    except Exception as e:
        print(f"Error: Failed to run {exe_file}")
        print(f"Exception: {str(e)}")
        return None

def get_numbered_selection(options, prompt):
    if not options:
        return None
    
    print("\n" + prompt)
    for i, option in enumerate(options, 1):
        print(f"{i}. {option}")
    
    while True:
        try:
            choice = int(input("Enter the number of your selection: "))
            if 1 <= choice <= len(options):
                return options[choice - 1]
            else:
                print("Invalid selection. Please try again.")
        except ValueError:
            print("Please enter a valid number.")

def manage_input_sets(config):
    while True:
        print("\nInput Set Management:")
        print("1. Create new input set")
        print("2. View existing input sets")
        print("3. Edit existing input set")
        print("4. Delete input set")
        print("5. Input commands guide")
        print("6. Return to main menu")
        
        choice = input("Enter your choice (1-6): ")
        
        if choice == "1":
            set_name = input("Enter a name for the new input set: ")
            inputs = []
            print("Enter inputs (special commands available, press Enter with no input to finish):")
            print("  - 'rand max' or 'rand min max' for random integers")
            print("  - 'for n: command' to repeat a command n times")
            print("  - 'range end' or 'range start end [step]' for number sequences")
            print("  - 'repeat n value' to repeat a value n times")
            print("  - 'shuffle item1 item2 ...' to shuffle items")
            print("  - 'choice item1 item2 ...' to choose a random item")
            print("  - 'file filename' to read input from a file")
            while True:
                user_input = input("> ")
                if user_input == "":
                    break
                inputs.append(user_input)
            config["input_sets"][set_name] = inputs
            save_config(config)
            print(f"Input set '{set_name}' created successfully.")
        
        elif choice == "2":
            if config["input_sets"]:
                for name, inputs in config["input_sets"].items():
                    print(f"\nInput set: {name}")
                    for i, inp in enumerate(inputs, 1):
                        print(f"  {i}. {inp}")
            else:
                print("No input sets found.")
        
        elif choice == "3":
            set_name = get_numbered_selection(list(config["input_sets"].keys()), "Select an input set to edit:")
            if set_name:
                print("Current inputs:")
                for i, inp in enumerate(config["input_sets"][set_name], 1):
                    print(f"  {i}. {inp}")
                inputs = []
                print("Enter new inputs (special commands available, press Enter with no input to finish):")
                print("  - 'rand max' or 'rand min max' for random integers")
                print("  - 'for n: command' to repeat a command n times")
                print("  - 'range end' or 'range start end [step]' for number sequences")
                print("  - 'repeat n value' to repeat a value n times")
                print("  - 'shuffle item1 item2 ...' to shuffle items")
                print("  - 'choice item1 item2 ...' to choose a random item")
                print("  - 'file filename' to read input from a file")
                while True:
                    user_input = input("> ")
                    if user_input == "":
                        break
                    inputs.append(user_input)
                config["input_sets"][set_name] = inputs
                save_config(config)
                print(f"Input set '{set_name}' updated successfully.")
            else:
                print("No input sets found.")
        
        elif choice == "4":
            set_name = get_numbered_selection(list(config["input_sets"].keys()), "Select an input set to delete:")
            if set_name:
                del config["input_sets"][set_name]
                save_config(config)
                print(f"Input set '{set_name}' deleted successfully.")
            else:
                print("No input sets found.")
        
        elif choice == "5":
            print("\nInput Commands Guide:")
            print("  - 'rand max' or 'rand min max': Generate a random integer within the specified range.")
            print("  - 'for n: command': Repeat a command n times. For example, 'for 3: rand 1 10' will produce three random numbers.")
            print("  - 'range end' or 'range start end [step]': Generate a sequence of numbers within the specified range.")
            print("  - 'repeat n value': Repeat a value n times. For example, 'repeat 5 42' will produce five 42s.")
            print("  - 'shuffle item1 item2 ...': Shuffle and return the items in random order.")
            print("  - 'choice item1 item2 ...': Choose a random item from the provided list.")
            print("  - 'file filename': Read input from the specified file.")
        
        elif choice == "6":
            break
        
        else:
            print("Invalid choice. Please try again.")

def inject_echo_code(c_file_path):
    with open(c_file_path, 'r') as f:
        content = f.read()

    # Regular expression to find scanf statements
    scanf_pattern = r'scanf\s*\(\s*"([^"]+)"\s*,\s*([^)]+)\);'
    
    def replace_scanf(match):
        format_specifier = match.group(1)
        variables = [v.strip() for v in match.group(2).split(',')]
        
        cleaned_variables = []
        for var in variables:
            if var.startswith('&'):
                cleaned_variables.append(var[1:].strip())
            else:
                cleaned_variables.append(var.strip())
    
        # Create printf statement to echo the input
        echo_printf = f'printf("{format_specifier}\\n", {", ".join(cleaned_variables)});'
    
        
        # Return the original scanf followed by the echo printf
        return f'{match.group(0)}    {echo_printf}'

    # Replace all scanf statements
    modified_content = re.sub(scanf_pattern, replace_scanf, content)

    # Create a new file with _testbench suffix
    base_name = os.path.splitext(c_file_path)[0]
    testbench_file = f"{base_name}_testbench.c"

    with open(testbench_file, 'w') as f:
        f.write(modified_content)

    return testbench_file

def manage_c_files(config):
    while True:
        print("\nC File Management:")
        print("1. Add new C file")
        print("2. View existing C files")
        print("3. Update C file location")
        print("4. Delete C file")
        print("5. Return to main menu")
        
        choice = input("Enter your choice (1-5): ")
        
        if choice == "1":
            file_name = input("Enter the name of the C file: ")
            file_path = input("Enter the full path of the C file: ")
            if os.path.isfile(file_path):
                config["c_files"][file_name] = {"path": file_path, "last_compiled": None}
                save_config(config)
                print(f"C file '{file_name}' added successfully.")
            else:
                print(f"Error: File not found at {file_path}")
        
        elif choice == "2":
            if config["c_files"]:
                for i, (name, info) in enumerate(config["c_files"].items(), 1):
                    print(f"\n{i}. C file: {name}")
                    print(f"   Path: {info['path']}")
                    print(f"   Last compiled: {info['last_compiled'] or 'Never'}")
            else:
                print("No C files found.")
        
        elif choice == "3":
            file_name = get_numbered_selection(list(config["c_files"].keys()), "Select a C file to update:")
            if file_name:
                new_path = input("Enter the new path for the C file: ")
                if os.path.isfile(new_path):
                    config["c_files"][file_name]["path"] = new_path
                    save_config(config)
                    print(f"C file '{file_name}' updated successfully.")
                else:
                    print(f"Error: File not found at {new_path}")
            else:
                print("No C files found.")
        
        elif choice == "4":
            file_name = get_numbered_selection(list(config["c_files"].keys()), "Select a C file to delete:")
            if file_name:
                del config["c_files"][file_name]
                save_config(config)
                print(f"C file '{file_name}' deleted successfully.")
            else:
                print("No C files found.")
        
        elif choice == "5":
            break
        
        else:
            print("Invalid choice. Please try again.")

def compile_c_file(c_file):
    exe_file = os.path.splitext(c_file)[0]
    compile_command = f"gcc {c_file} -o {exe_file}"
    
    try:
        result = subprocess.run(compile_command, check=True, shell=True, capture_output=True, text=True)
        print(f"Successfully compiled {c_file} to {exe_file}")
        if result.stderr:
            print("Compiler warnings:")
            print(result.stderr)
        return exe_file
    except subprocess.CalledProcessError as e:
        print(f"Error: Failed to compile {c_file}")
        print("Compiler output:")
        print(e.output)
        return None
def compile_and_run(config):
    if not config["c_files"]:
        print("No C files found. Please add a C file first.")
        return

    file_name = get_numbered_selection(list(config["c_files"].keys()), "Select a C file to compile and run:")
    if not file_name:
        return

    c_file_path = config["c_files"][file_name]["path"]
    
    # Inject echo code
    testbench_file = inject_echo_code(c_file_path)
    print(f"Created testbench file: {testbench_file}")

    exe_file = compile_c_file(testbench_file)
    if not exe_file:
        return

    config["c_files"][file_name]["last_compiled"] = datetime.datetime.now().isoformat()
    save_config(config)

    if config["input_sets"]:
        set_name = get_numbered_selection(list(config["input_sets"].keys()), "Select an input set to use:")
        if set_name:
            inputs = config["input_sets"][set_name]
        else:
            print("No input set selected. Using empty input set.")
            inputs = []
    else:
        print("No input sets found. Using empty input set.")
        inputs = []

    print("\nRunning the compiled program with the selected input set:")
    return_code = run_executable(exe_file, inputs)
    
    if return_code is not None:
        print(f"\nProgram exited with return code: {return_code}")

    config["last_used"] = {"c_file": file_name, "input_set": set_name if set_name else None}
    save_config(config)

    # Clean up the testbench file
    os.remove(testbench_file)
    print(f"Removed testbench file: {testbench_file}")

def main():
    config = load_config()
    
    while True:
        print("\nMain Menu:")
        print("1. Compile and run C program")
        print("2. Manage input sets")
        print("3. Manage C files")
        print("4. Re-run last test")
        print("5. Exit")
        
        choice = input("Enter your choice (1-5): ")
        
        if choice == "1":
            compile_and_run(config)
        
        elif choice == "2":
            manage_input_sets(config)
        
        elif choice == "3":
            manage_c_files(config)
        
        elif choice == "4":
            if config["last_used"]:
                last_c_file = config["last_used"]["c_file"]
                last_input_set = config["last_used"]["input_set"]
                print(f"Re-running last test: C file '{last_c_file}' with input set '{last_input_set}'")
                
                c_file_path = config["c_files"][last_c_file]["path"]
                exe_file = compile_c_file(c_file_path)
                if exe_file:
                    inputs = config["input_sets"].get(last_input_set, [])
                    run_executable(exe_file, inputs)
            else:
                print("No previous test found.")
        
        elif choice == "5":
            print("Exiting the program. Goodbye!")
            break
        
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()