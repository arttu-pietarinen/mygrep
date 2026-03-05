# mygrep

**mygrep** is a C++ command-line tool that searches text files for lines containing a given string. It is inspired by the Linux `grep` utility. Built as a course project for *Advanced C++ Programming*.

---

## What it does

- Search a file line by line for a matching string
- Show line numbers for matches
- Count how many lines matched
- Case-insensitive search
- Reverse search — find lines that do NOT contain the string
- Interactive mode when run with no arguments

---

## How to build

```
g++ main.cpp -o mygrep
```

---

## How to use

### Interactive mode
Run with no arguments:
```
./mygrep
```
The program will prompt you for a source string and a search string.

---

### Basic file search
```
./mygrep <search> <filename>
```
Prints every line in the file that contains the search string.

---

### With options
```
./mygrep -o<flags> <search> <filename>
```

| Flag | What it does |
|------|--------------|
| `l`  | Show line numbers before each match |
| `o`  | Show total count of matching lines at the end |
| `i`  | Case-insensitive — treats uppercase and lowercase as equal |
| `r`  | Reverse — print lines that do NOT contain the search string |

Flags can be combined freely, for example `-olir`.

---

## Examples

```
./mygrep following text.txt
./mygrep -ol following text.txt
./mygrep -oo following text.txt
./mygrep -oi folloWING text.txt
./mygrep -olori folloWING text.txt
```

---

## Error handling

If a file cannot be opened, the program throws an exception:

```
An exception occurred. Exception Nr. -1
Could not find out the size of file "missingfile.txt"
```

---

## Project structure

| File | Description |
|------|-------------|
| `main.cpp` | All source code |
| `text.txt` | Test file used during development |

---

## Increments completed

| Increment | Description | Points |
|-----------|-------------|--------|
| 1 | Interactive string search | 1p |
| 2 | File search with arguments | 3p |
| 3 | Line numbers and occurrence count | 4p |
| 4 | Case-insensitive, reverse search, exceptions | 5p |

**Target: 5 points**
