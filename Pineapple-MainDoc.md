#### Core Ideas:
 - Graphical Implementations should be accessible within the Standard Library
 - There are many ways to say something, there is only one best way to do something, and it has to be obvious.
 - Complexity florishes with creative simplicity.
 - Higher-Level Abstractions are never a bad thing.
# Declare, Allocate, Operate

```
String: im_a_string;
Integer: im_an_integer;

im_a_string = "Hello, there"; //Allocates strings dynamically dependant on length of string during runtime.
im_an_integer = 5; //Integer simply allocate their machine value

Output(im_a_string*5)
```
Output:
```
Hello, there
Hello, there
Hello, there
Hello, there
Hello, there
```

---

# There is Always Only One Way to do Something, but Many Ways to Say Something
Aliases are used quite frequently throughout Pineapple. Types are usable as shortened versions: Int, Str, Dbl, Float

There are officially supported tools to dynamically parse, and regenerate code dependant on the aliases you use. This will allow opinions to flow, while keeping continuity still through source, and machine code.

```
Str: im_a_string;
Int: im_an_integer;

im_a_string = "Hello, there";
im_an_integer = 5;

Out(im_a_string*5)
```

You can also internally represent your source code, so external parses can pack or unpack your aliases using the `#Define` preprocessor.
When using `#Define`, your alias is as well declared.

```
#Define im_a_string as ias 

Int: im_an_integer;

ias = "Hello, there";
im_an_integer = 5;

Out(ias)

```

When someone unpacks your code, if they so please for their own readability, it will show:

```
String: im_a_string;

Integer: im_an_integer;

i_am_string = "Hello, there";
im_an_integer = 5;

Output(im_a_string)
```

The sole purpose of this feature is to provide more comfortability when reading peer's programs, while allowing an individual to make their own personal decisions on representation, and convention.

# Chapters
 - [Operators](#operators)
 - [Keywords](#keywords)
	 - [Type Delcarations](#type-declaration)
	 - [Decision Making](#decision-making)
 - [Standard Library](#standard-library)

---

## Operators

`+` - Add

`-` - Minus

`/` - Divide

`*` - Multiply

`=` - Variable declaration

`==` - Equality comparison

`>` - Greater than comparison

`>=` - Greater than or equal to comparison

`<` - Lesser than comparison

`<=` Lesser than or equal to comparison

[Chapters](#chapters) - [Top of page](#iwa-reference)

---

## Keywords

### Type Declaration

**`String` - String Type**

Example: `String greeting = "Hello";`


**`Integer` - Integer Type**

Example: `Integer age = 18;`


**`Float` - Float Type**

Example: `Float Pi = 3.141;`


### Decision Making

`If` - Begin an If conditional

`Else` - Begin an Else Conditional

[Chapters](#chapters) - [Top of page](#iwa-reference)

---

## Standard Library

`In()` - Take in input from the user

`Out()` - Output something to the console

[Chapters](#chapters) - [Top of page](#iwa-reference)
