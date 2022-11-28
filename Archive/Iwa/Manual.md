# Manual Reference

# 0.0 - Chapters
[0.1 - Syntax](#01---syntax)
[0.2 - Compilation Targets](#02---compilation-targets) 

# 0.1 - Syntax
Almost verything within Pineapple has short-hand aliases that I tried to make them obvious, and easily interchangable mentally.<br>
Examples:<br>
`Integer` or `Int`, `String` or `Str`, `Private` or `Priv`

As well, the capitalized, or uncapitalized for can be used:<br>
`integer` or `int`, `string` or `str`, `private` or `priv`<br>

However, one or the other must be chosen to be used, they cannot be intermixed, or the compiler will indeed yell at you.

---

Variable declarations: `<Immutability Modifier*> <Access Modifier*> <Type> <Identifier>;`<br>
Example: `!Private Integer player_health;`

---

Variable definitions: `<Identifier> <Assignment Operator> <Value>`<br>
Example: `player_health += 10;`

---

Function declarations: `<Access-Modifier> <Identifier> ~ (<Parameter1>, <Parameter2>) -> <Return-Type>;`<br>
Example: `Public Log_Error ~ message, error_code: String;`

Function definitions: `<Identifier> (<Parameter1>, <Parameter2>)`<br>
Example:
```
Log ~ message, error_code {
    Out(message);
    Return message;
}
```

Function Call: `<Identifier> (<Parameter1>, <Parameter2>)`<br>
Example: `Log ~ "Failed to receive page", 404`

---

If Statement:
```
If <Expression> <Conditional Operator> <Value>:
    <Statements...>
```
Example:
```
If (2 + 2 == 4)
    Out(True);
```

---

Guard Clause:
```
Not <Expression> -> <Statements...>;
```
Example:
```
Not (2 + 2 == 4) -> False;
```

---

Switch Case:
```
Case:
    <Expression>:
        <Statements...>;
    <Expression>:
        <Statements...>;
    <Optional Emergency Operator>
```
Example
```
Case:
    & (2 + 2 == 4)
        Out("We're Sane");
    & (2 + 2 != 4)
        Out("We are definitely not sane");
    !Out("Something very wrong happened");
```

---

All whitespace is trimmed from the file during compilation, so with that in mind, write code in whatever way you please.

# 0.2 - Compilation Targets

#### Supported Compilation Targets:
 - C (C89, C11)
 - C++ (C++11, C++14, C++17)

#### Supported Source-To-Source Compilation (Transpiling) (Transplying Does NOT Make Effort to Optimize AT ALL)
*Note: Some Source-To-Source implements rely completely on LLVM IR*
 - Python 3.10
 - Lua
 - Rust
 - Go
