# CAN Bus Lab

## Raspberry Pi GCC and GDB Command-Line Training

### Training goal

This short lab introduces you to the basic command-line workflow for:

- connecting to a Raspberry Pi using SSH,
- organizing source files in a personal working directory,
- compiling a provided C program with GCC,
- editing the program with Nano,
- running the compiled program, and
- debugging the program with GDB.

> [!NOTE]
> The provided C source file, `can_example.c`, is used as the lab application. Its implementation is not discussed in this document.

---

## 1. Connect to the private Wi-Fi network

Connect the computer to the private wireless network used during the lab.

| Setting | Value |
|---|---|
| SSID | `A1-4883e1` |
| WPA2 password | Will be provided during the lecture. |

---

## 2. Connect to the Raspberry Pi via SSH

Open a terminal and enter:

```bash
ssh pi@raspberrypi
```
or

```bash
ssh pi@10.0.0.1
```

The Raspberry Pi password will be provided during the lecture.

If SSH asks whether you trust the host, verify that you are connecting to the correct lab device before accepting its host key.

After login, the terminal prompt belongs to the Raspberry Pi. All following commands are executed on the Raspberry Pi.

---

## 3. Create a personal working directory

Change to the lab directory:

```bash
cd ~/CAN_Lab/
```

Create a directory using your name or initials:

```bash
mkdir <your-name>
```

Change to your new directory:

```bash
cd <your-name>
```

Copy the provided C example into the current directory:

```bash
cp ~/CAN_Src/can_example.c can_example.c
```

List the directory contents and verify that `can_example.c` is present:

```bash
ls
```

### Example

The following example uses the folder `test`:

```bash
cd ~/CAN_Lab/
mkdir test
cd test
cp ~/CAN_Src/can_example.c can_example.c
ls
```

> [!IMPORTANT]
> Replace `<your-name>` with an actual directory name. Do not type the angle brackets.

---

## 4. Compile the C example with GCC

Compile the source file and create the executable `can_example.out`:

```bash
gcc can_example.c -g -v -o can_example.out
```

### Options used

| Option | Purpose |
|---|---|
| `can_example.c` | Input source file |
| `-g` | Adds debugging information required by GDB |
| `-v` | Displays detailed compiler information |
| `-o can_example.out` | Defines the name of the output executable |

If compilation succeeds, verify that the executable exists:

```bash
ls
```

---

## 5. Run the C example

Start the compiled program:

```bash
./can_example.out
```

The `./` prefix tells the shell to run the executable from the current directory.

---

## 6. Edit the C example with Nano

Open the source file in the Nano text editor:

```bash
nano can_example.c
```

Useful Nano shortcuts are shown at the bottom of the editor. The `^` symbol represents the **Ctrl** key.

| Shortcut | Action |
|---|---|
| `Ctrl+O` | Save the file |
| `Enter` | Confirm the file name when saving |
| `Ctrl+X` | Exit Nano |

Complete the assigned programming task, save the source file, and exit Nano.

Then compile and run the program again:

```bash
gcc can_example.c -g -v -o can_example.out
./can_example.out
```

> [!TIP]
> Recompile the program after every source-code change. Otherwise, the executable still contains the previous version.

---

## 7. Debug the program with GDB

Start GDB and load the executable:

```bash
gdb can_example.out
```

After startup, commands are entered at the `(gdb)` prompt.

### 7.1 Display source code

Display source code around line 80:

```gdb
list 80
```

### 7.2 Set a breakpoint

Set a breakpoint at source-code line 84:

```gdb
break 84
```

The short form is:

```gdb
b 84
```

> [!NOTE]
> The line numbers assume that the provided source file has not been changed above the relevant lines. Use `list 80` to verify the location before setting the breakpoint.

### 7.3 Run the program

Start program execution inside GDB:

```gdb
run
```

The short form is:

```gdb
r
```

GDB pauses execution when the breakpoint is reached.

### 7.4 Print the received CAN frame

Print `rx_frame` using hexadecimal formatting:

```gdb
print /x rx_frame
```

The short form is:

```gdb
p /x rx_frame
```

### 7.5 Display local variables

Show the local variables in the current stack frame:

```gdb
info locals
```

### 7.6 Display CPU registers

Show all CPU registers:

```gdb
info all-registers
```

### 7.7 Display breakpoints

Show all currently defined breakpoints:

```gdb
info breakpoints
```

### 7.8 Disassemble the `main` function

Display the assembly instructions generated for `main`:

```gdb
disassemble main
```

### 7.9 Remove a breakpoint

Remove the breakpoint at source-code line 84:

```gdb
clear 84
```

Alternatively, first display the breakpoint numbers:

```gdb
info breakpoints
```

Then delete a breakpoint by its number, for example breakpoint 1:

```gdb
delete 1
```

> [!NOTE]
> `clear breakpoint` is not the command for removing an arbitrary breakpoint. Use `clear <location>` or `delete <breakpoint-number>`.

### 7.10 Exit GDB

Exit the debugger:

```gdb
quit
```

If the program is still running, GDB may ask for confirmation before exiting.

---

## 8. Complete command sequence

The following overview summarizes the main lab workflow. Replace `<your-name>` with your own name or initials.

```bash
ssh pi@raspberrypi
cd ~/CAN_Lab/
mkdir <your-name>
cd <your-name>
cp ~/CAN_Src/can_example.c can_example.c
ls
gcc can_example.c -g -v -o can_example.out
./can_example.out
nano can_example.c
gcc can_example.c -g -v -o can_example.out
./can_example.out
gdb can_example.out
```

Example GDB session:

```gdb
list 80
break 84
run
print /x rx_frame
info locals
info all-registers
info breakpoints
disassemble main
clear 84
quit
```

---


