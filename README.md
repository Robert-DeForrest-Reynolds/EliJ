:no_entry: - Not Developing Yet

:hammer_and_wrench:	- Under Development

:warning: - Unstable Version for Use

:pineapple: - Stable Version for Use

:heavy_check_mark: - Stable Release Viable for Production

 - EliJ :hammer_and_wrench:
 - Pineapple :hammer_and_wrench:
 - Iwa :hammer_and_wrench:
 - Lily :hammer_and_wrench:
 - Hope :hammer_and_wrench:
 - HPM (Hope Package Manager) :hammer_and_wrench:
 - Pim :no_entry:
 - EliJ's Syntax Highlighting Theme :no_entry:
 - ExoFyle :no_entry:
 - Cornelius :no_entry:
 - Mel :no_entry:

---

### EliJ
A suite of completely free-to-use applications for developers. Under heavy development. don't expect anything to work yet.

The goal of EliJ is to provide a completely, truly free, and competent set of tools for anyone to use.

Optionally comes in VM form to run underneath host OS.

### Pineapple
Pineapple is a programming language.

### Iwa
Iwa is the official compiler for Pineapple, and will be capable of transplicing, and recompling other languages into Pineapple, or Pineapple into other languages.

### Lily
Lily is the official interpreter for Pineapple.

### Hope
The build system for Pineapple.

### HPM (Hope Package Manager)
The package manager built into Hope. Inspired by Cargo from Rust, and Pip from Python.

### Pim
A terminal-based text editor written in Python.

### EliJ's Syntax Highlighting Theme
A custom theme explained in standardized form, that can be easily supported whereever may be needed.

### ExoFyle
A minimal lightweight code editor, comes packaged with Pineapple.

### ExoFyle IDE
A complete integreated development environment to support Pineapple development.

### Mel
Audio development environment.


# Chapters

Statements are ended with semi-colons.
Code blocks are started and ended with curly brackets.

All of this info is to be migrated elsewhere, and this file deleted

Welcome to functional programming done right.

 - [Comments](#comments)
 - [Operators](#operators)
 - [Type Declarations](#type-declaration)
 - [Decision Making](#decision-making)
 - [Objects](#objects)
 - [Functions](#functions)
 - [Import & Find](#import-&-find)
 - [Standard Library](#standard-library)
 - [Developer Notation](#developer-notation)

# Defining Syntax Character Names
#### Operators
```
+ # Addition
- # Subtraction
+= # Increment and assign
-= # Decrement and assign
* # Multiply
/ # Division
% # Get Remainder
!= # Not Equals
== # Equals
& # And
\ # Or
' # String Wrapper
~ # Import
, # List Separator
() # Multi-line Data Wrappers
{} # Multi-line Data Wrappers
```

#### Reserved Keywords
```
Str
Int
Flt
Fnc
Obj
```
#### Built-Ins
```
Sum
Size
```
# Language Descriptions, and Developer Commentary

I want to talk about the language I've been designing and exposé the syntax of it, and my thoughts behind it. I want to get opinions on the syntax, and motivations. I've been making this language for a while now, and something I've had great troubles with is the syntax. **I firmly believe the syntax makes the language.** Everything else people will either roll themselves, or force their project to conform to. I do not want to cater to either of those tendencies, but I do want to recognize that syntax seems to be most crucial to success. The ability to learn the syntax, understand, and utilize is paramount to the success of the user, and everything else comes after. Let's go.

Let's start in the beginning. C is a beautiful language, I started with Java, and made my way through many languages, eventually reaching C, where I came to understand what other developers were talking about. It is, by far, the strongest language anyone has access to currently. C is the default palette of a computer scientist. It is the toolbelt compatible with any job, and it can access anything that it wants to access. The core weakness: it's taken over 50 years to get where we are with it now, and it is very difficult to teach, and practice C, as it is insanely complex. An argument immediately thrown is that a majority of people are just bad computer scientists, which I won't necessarily deny. I will acknowledge it, not necessarily believing it's true, but acknowledging that there's a problem. Python has a very strong community because of it's simplicity to learn, and ability to practice. As well, the ability to teach it. Python has it's own weaknesses. Every language so far seems to have their own weaknesses. I propose accepting weaknesses purposefully to strengthen what feels like matters. Pineapple's core weakness will be it's 

Pineapple parses line-by-line, and does not care about indentation. Whitespace between keywords is required, but is not required between symbols. You can think of every line as a statement.
```
# As `=` and `"` are 
Str Name="Sirley"
```

This will allow ease of parsing.
### Large Form Example Script
```
# I'm a comment #

#
Anything between
two pound signs
is a comment
#

# Importing another file; uses name of file, excluding .papple extension
# So the file name would be Lorem.papple
# Import is a direct copy and paste of code
~Lorem
# If you want to import a specific function or variable, just use . notation
~Lorem.SomeVariable;
~Lorem.SomeFunction;
~Lorem.(SomeFunction,Variable);
# There is an automatic warning for importing a whole file afterward taking a portion of it
~Lorem.SomeVariable;
~Lorem # Produces Warning

# Printing out information to the console
Out("Hello")

# Wait for input from the user
Str UserInput = In();

# Built-in Constants
Out(PI) # Outputs: 3.14159;

# Integers
Int Health = 20;
# Float
Flt Wallet = 3.33;

# Math

# Increment & Assignment Operators uses References
# Meaning that you variables will be directly changed
Health += 20;
Health -= 20;
Health = Health + 20;
Health = Health - 20;

Out(5/2) # Outputs: 2.5;
# Floor Division
Out(5//2);

# Float Rounding
Round(2.5);

# Nicknaming/Rereferencing
Ref Rnd = Round;

# Copying/Duplicating
Int Total = 50;
New Total;

# Functions
# Parameters are passed by reference by default, or you can decide to make a copy
Fnc Sum(Int Number1, Int Number2):
	Return Number1 + Number2;

Obj Person:
	Fnc Init(Ref Name):
		Str Name
```


Everything largely translates directly into some kind of C derivative, whether that's a keyword, operators, or function.

```
Out("Hello")
```


```
char* Print()
{

}
```
# Comments
```
# <Text> #
```

```
# Comments are anything between two pound/hash symbols #

#
This rule works
for multi-line
comments as well
#
```
[Chapters](#chapters)
# Operators
`+` - Add
```
Out(5 + 5);
```
>10

`-` - Minus
```
Out(10 - 5);
```
>5

`/` - Float Division
```
Out(9 / 2);
```
>4.5

`/`/ - Float Division
```
Out(10 // 2);
```
>5

`*` - Multiply
```
Out(10 * 2);
```
>20

`=` - Assignment
```
Int Health = 50;
```
>5

`Is` - Equality comparison
```
Str Answer = "Purple"

UserInput = In("What's my favorite color?")
If (UserInput is Answer){
	Out("You it got right!");
} Else {
	Out("You got it wrong!");
}
```

`>` - Greater than comparison
```
Int Hunger = 50;

If (Hunger > 50){
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
>I'm not hungry

`>=` - Greater than or equal to comparison
```
Hunger = 50

If (Hunger >= 50){
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
> I'm hungry

`<` - Lesser than comparison
```
Hunger = 50

If (Hunger < 50){
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
> I'm not hungry

`<=` Lesser than or equal to comparison
```
Str Hunger = 50;

If (Hunger <= 50){
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
> I'm hungry

[Chapters](#chapters)
# Type Declaration

**`Str` - String Type**
```
Str Greeting = "Hello";
```

**`Int` - Integer Type**
```
Int Age = 18;
```

**`Flt` - Float Type**
```
Flt Pi = 3.141;
```

[Chapters](#chapters)
# Decision Making

`If` - Use specified code block if condition is met
```
If (<Conditional>){
	<Statements>;
}



If (Food is Expired){
	Food.Throw_Away();
}
```

`Else` - Use after `If` statement to use specified code block if condition in `If` is not met.
```
If (<Conditional>){
	<Statements>l
} Else {
	<Statements>;
}



If (Food is Expired){
	Food.Throw_Away();
}Else{
	Food.Store();
}
```

If (Food is Grapefruit){
    Throw_Away(Food);
} Or (Food is Strawberries){
    Eat(Food);
} Else {
	Store(Food);
}
```

Colors[Red];
```

[Chapters](#chapters)
# Objects
Objects have built-in functions that can be utilized to implement your own behavior on top of. Below are the built-ins described.

`New` - Called when a object is instantiated
`Destroy` - Called when a object is destroyed
`Name` - Utility function used to easily get name of object as string

```
Obj <DelcarativeName>{
	Fnc New(Parameters){
		<CodeBlock>
	}
}
```
```
Obj Human{
	Fnc New(Name, Age){
		Self.Name = Name
		Self.Age = Age
	}
}
```

[Chapters](#chapters)
# Functions

```
Fnc<DeclarativeName>(Parameters){
	<CodeBlock>
}
```
```
FncAddition(Int X, Int Y){
    Return X + Y;
}

Addition(5, 10)
```

[Chapters](#chapters)
# Import & Find
`Find` is used to import code from another file.

```
Find <File-Name>.<Declarative-Name>

Find Graphs.2DPlot
```

[Chapters](#chapters)

# Built-Ins

`In()` - Take in input from the user

`Out()` - Output something to the console

[Chapters](#chapters)

# Developer Notation

#### Core Ideas:
 - Graphical Implementations should be accessible within the Standard Library
 - There are many ways to say something, there is only one best way to do something, and it has to be obvious.
 - Complexity flourishes with creative simplicity.
 - Higher-Level Abstractions are never a bad thing.

[Chapters](#chapters)
