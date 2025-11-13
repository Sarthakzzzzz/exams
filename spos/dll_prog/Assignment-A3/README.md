## Steps to run this code

These are the steps to run code for Assignment-A3.

---

### Refer [EXPLANATION](https://git.kska.io/sppu-te-comp-content/SystemsProgrammingAndOperatingSystem/src/branch/main/Codes/Group%20A/Assignment-A3/EXPLANATION.md) to understand how everything works.

> [!IMPORTANT]
> Tested on Linux and Windows.

### Prerequisites

1. open-jdk (version 11 or higher)
2. gcc
3. Set open-jdk and gcc as environment variables using bin folder in path (For Windows Users only)
4. Common sense

### Steps For Linux

1. Compile `A3.java`:
```shell
javac A3.java
```

2. Generate header file:
```shell
javac -h . A3.java
```

3. Compile C code:
```shell
gcc -shared -o libA3.so -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" A3.c
```

> [!NOTE]
> If you get an error saying _"fatal error: jni.h: No such file or directory"_, this might be because you haven't set `$JAVA_HOME` environment variable. Usually JVM stuff is in `/usr/lib/jvm/java-<version>-openjdk-amd64`. To set `JAVA_HOME` environment variable, run: `export $JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64` (for version 17, adjust for your version accordingly.)

4. Run program:
```shell
java -Djava.library.path=. A3
```
### Steps For Windows

1. Compile `A3.java`:
```shell
javac A3.java
```

2. Generate header file:
```shell
javac -h . A3.java
```

3. Set `JAVA_HOME` to the path of your jdk file location:
> Note that this is my file location for jdk. It may differ for you.
```shell
set JAVA_HOME=C:\Program Files\openjdk-23.0.1_windows-x64_bin\jdk-23.0.1
```

4. Compile C code:
```shell
gcc -shared -o A3.dll -fPIC -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" A3.c
```

5. Run program:
```shell
java -Djava.library.path=. A3
```
