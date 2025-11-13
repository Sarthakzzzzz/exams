# Explanation

This file contains explanation for dynamic linking library program (Assignment-A3)

---

Please note the files referred in this guide:
- [A3.java](https://git.kska.io/sppu-te-comp-content/SystemsProgrammingAndOperatingSystem/src/branch/main/Codes/Group%20A/Assignment-A3/A3.java)
- [A3.c](https://git.kska.io/sppu-te-comp-content/SystemsProgrammingAndOperatingSystem/src/branch/main/Codes/Group%20A/Assignment-A3/A3.c)
- [A3.h](https://git.kska.io/sppu-te-comp-content/SystemsProgrammingAndOperatingSystem/src/branch/main/Codes/Group%20A/Assignment-A3/A3.h)

---

- We're using Java for writing the main program.
- To demonstrate Dynamic Linking Library (DLL) in Java, we'll be declaring functions in Java and implementing them in C (can be C/C++).
- First, we create a Java program `A3.java`,
  - This is the main Java file containing function definition and the main function.
  - Functions (add, sub, mul, div) in `A3` class in this file are native functions, meaning their body is written in C/C++ in a different file.
- After creating this file, you need to compile it. To do so, run `javac A3.java` (assuming you're already in the directory that contains this file).
- Now, we will generate the header file. For this, run `javac -h . A3.java`.
- There will be a new file called `A3.h` in your current working directory,
  - This is the header file.
  - It contains signatures for native functions we created in the Java file.
  - Thus, there's **no need to memorized boilerplate in `A3.c`** since the functions defined in that file can be found in the header file. I have included the [A3.h](https://git.kska.io/sppu-te-comp-content/SystemsProgrammingAndOperatingSystem/src/branch/main/Codes/Group%20A/Assignment-A3/A3.h) file in this folder for reference. Note that it is automatically generated.
- Create a new `A3.c` file which is the C program file containing function definitions (for add, sub, mul, div)
  - Define all the functions (add, sub, mul, div)
- Then, we have to compile the C program file, i.e. `A3.c`. For this, run `gcc -shared -o libA3.so -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" A3.c`,
  - `gcc` -> GNU compiler for C program
  - `-shared` -> tells the compiler to create a shared file (.so) instead of a regular executable file
  - `-o libA3.so` -> tells the compiler to save the output to `libA3.so` file
  - `fPIC` -> stands for Position-Independent Code. Needed for creating shared libraries.
  - `-I"$JAVA_HOME/include"` and `-I"$JAVA_HOME/include/linux"` -> `-I` flag used for specifiying directories to include. Values in double quotes are directories
  - `A3.c` -> name of the C program file to compile
- Lastly, run the program using `java -Djava.library.path=. A3`
  - `java` -> Loads Java Virtual Machine (JVM)
  - `-Djava.library.path=.` -> `-D` is used to set a system property. In this case, we’re setting the `java.library.path` (for .so or .dll files) property.
  - `A3` -> name of the Java class containing the main method

---
