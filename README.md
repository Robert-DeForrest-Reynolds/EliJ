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


### Principles & Conventions

One of the core motives of Pineapple and Iwa is to provide a better interface to a compiled language. Here are the core beliefs, and features that motivated the creation of Pineapple:
- Idiomatic syntax; programming languages help us talk to computers, but just as so, they allow computers to tell us what they are doing. If you're writing something useful, someone will read your code eventually probably. Make sure they can actually understand it when they do.
- The compiler needs to guide you to properly leveraging it; the vernacular when outputting errors must be clear, concise, and contain all of the necessary notation to access the error's properties. Just as well, functions, and behavior created by the developer should be clearly, and concisely named, documented, and provide the necessary links to all of the related properties involved. A user of the language should never get lost within thousands of lines of someone else's code, if they understand the absolute fundamentals.
- The fundamentals of something should be small and simple; the single-responsibility principle is the most universal method to organizing complex systems within code. This does not mean you cannot successfully create abstractions that use multiple responsibilities, however, take care to not create such a complex abstraction that a mind cannot easily grasp it.
- Complexity is built from abundant simplicity; if we follow the previous principle of providing simple fundamentals. Building an abundant amount of simple fundamentals is what constitutes a complex system.
#### Lifecycles
Pineapple Source Code -> Iwa Compiler -> C Code -> Clang -> Executable
Pineapple Source Code -> Iwa Compiler -> C++ Code -> Clang++ -> Executable
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
Length
Out
In
Split
```
# Language Descriptions, and Developer Commentary

I want to talk about the language I've been designing and exposé the syntax of it, and my thoughts behind it. I want to get opinions on the syntax, and my motivations. I've been making this language for a while now, and something I've had great troubles with is the syntax. **I firmly believe the syntax makes the language.** Everything else people will either roll themselves, or force their project to conform to. I do not want to cater to either of those tendencies, but I do want to recognize that syntax seems to be most crucial to success. The ability to learn the syntax, understand, and utilize is paramount to the success of the user, and everything else comes after. Let's go.

Let's start in the beginning. C is a beautiful language, I started with Java, and made my way through many languages, eventually reaching C, where I came to understand what other developers were talking about. It is, by far, the strongest language anyone has access to currently. C is the default palette of a computer scientist. It is the toolbelt compatible with any job, and it can access anything that it wants to access. The core weakness: it's taken over 50 years to get where we are with it now, and it is very difficult to teach, and practice C, as it is insanely complex. Where the language is simple, the compiler infrastructure for it is not. An argument immediately thrown is that a majority of people are just bad computer scientists, which I won't necessarily deny. I will acknowledge it, not necessarily believing it's true, but acknowledging that there's a problem. Python has a very strong community because of it's simplicity to learn, the  ability to practice, as well, the ability to teach it. Rapid prototyping, and the ability to approach a new project with momentum is absolutely valuable. Zig can compile anything is seems. C# proves the learnability of complex computer science abstractions, as long as you present it with human readability, and writability. JavaScript proves that people will walk through hell to avoid learning on their own, and thinking for themselves. C++ proves that some would sacrifice all of their sanity and then some for the sake of performance. Rust proves how much people love immutability by default, and good error messages. A lot of languages have brought a lot to the table, and some of them of been good for society, and some of them have been bad for society. What would the world be like if C# would the dominate web language?

Pineapple parses line-by-line, and does not care about indentation. Whitespace between keywords is required, but is not required between symbols. You can think of every line as a statement.
```
# As `=` and `"` are 
Str Name = "Sirley";
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
So the file name would be Lorem.papple
Import is a direct copy and paste of code #
~Lorem;

# If you want to import a specific function or variable #
~Lorem(SomeVariable);
~Lorem(SomeFunction);
~Lorem(SomeFunction,Variable);

# There is an automatic warning for importing a whole file afterward taking a portion of it #
~Lorem(SomeVariable);
~Lorem; # Produces Warning

# You can blacklist things from a whole file import with second import
This allows for *imported variables to be global by default*, but potentially hidden from a specific context. #
~Lorem(SomeVariable);
~Lorem~(SomeVariable);

# Printing out information to the console, and function call example #
Out("Hello");

# Wait for input from the user #
Str UserInput = In();

# Built-in Constants #
Out(PI); # Outputs: 3.14159

# Global Variables
Anything prefixed with an underscore will be treated by the compiler as globally accessible #
Str _ProjectName = "Pineapple";

# Boolean #
Bln Alive = True;
Bln Unhappy = False;

# Integers #
Int Health = 20;
# Float #
Flt Wallet = 3.33;
# List #
Lst Students = ["Jeffery", "Sara", "Kevin"];
Out(Students[0]) # Outputs: Jeffery #
Students.Append("Julie");
# Dictionary #
Dct TrafficLights = [
	"Green":"Go",
	"Yellow":"Slow",
	"Red":"Stop",
];
# None, Mainly used for initializing variable without a value # 
Int Wallet = None;

# Math
Increment & Assignment Operators uses References
Meaning that you variables will be directly changed#
Health += 20;
Health -= 20;
Health = Health + 20;
Health = Health - 20;

Out(5/2); # Outputs: 2.5 #

# Floor Division #
Out(5//2); # Outputs: 2 #

# Float Rounding #
Out(Round(2.5)); # Outputs 3, typed Int #

# Casting #
Flt Wallet = 5.26;
Out(Cast(Wallet, Int)); # Outputs: 5 #
# Iwa will automatically floor float conversions, if you want it rounded, you'll have to round it #
Out(Cast(Rnd(Wallet), Flt))`

# Nicknaming/Rereferencing #
Ref Rnd = Round;
Out(Rnd(2.5));
# Outputs: 3 #
Out(Type(Rnd(2.5)));
# Outputs: Int #

# Copying/Duplicating #
Int Total = 50;
New Total;

# Strings # 
Str FirstName = "Roger"
Str LastName = "Rabbit";
Str FullName = f"{FirstName} {LastName}"
Str Multiline = | # Always skips the first new line
This is
a multiline
string.
; # Also skips the last new line

# Also valid, compiler will properly introduce the newline at beginning and end but this is an unsuggested way of formatting. #
Str Multiline = | This is
a multiline
string.;

# Strings are arrays as always, and can be index, and sliced #
Str Greeting = "Hello there!";
Str Hello = Greeting[0:4];

# Functions
Parameters are passed by reference by default, or you can decide to make a copy #
Fnc Sum: Number1, Number2 {
	Return Number1 + Number2;
}

# Variables not declared in place will be held as anonymous in memory #
Sum(Int 5, Int 6);

# Objects
Obj Person:
	Fnc Init: Str Name
	{
		# Global variables declared in an objects scope are not global to the project, only to the object #
		Str _Name = Name;
	}
;

# Inheritance
Obj Human:
	Fnc Init:
	{
		Int _Age = 0;
	}
;
Obj Person | Human:
	Fnc Init: Str Name
	{
		Str _Name = Name;
	}

	Fnc Greeting:
	{
		Return f"Hello, my name is {_Name}, and I'm {_Age} years old.";
	}
;

# Conditionals #
If Food is Grapefruit {
	Out("I don't like this food.");
} Or Food is Strawberries {
	Out("I like this food.");
} Else {
	Out("I don't know about this food.");
}

# `not in` is a thing #
Lst Students = ["Jeffery", "Sara", "Kevin"];
If "Aaron" not in Students {
	Students.Append("Aaron");
}

Lst Fruits = ["Oranges", "Apples", "Bananas"]

# For loops can be used for looping through elements in data structures
For Fruit in Fruits {
	Out(Fruit);
}

Dct Students = [
	"Kevin": 14,
	"Bill":15,
	"Julia":14,
]

For Name, Age in Students {
	Out(f"{Name} is {Age} years old.");
}

# While loops don't exist in Pineapple, instead we have looped conditionals
Int Iterator = 0;
If Iterator < 10{
	Out(Iterator);
} ? I++;

# The compiler will not allow you to create "Improperly Bounded Looped Conditionals". At least it will rationally attempt to catch them. #
Int Iterator = 0;
If Iterator < -1{
	Out(Iterator);
} ? I++;

# Iwa will test the bounds of each side, and see if the bounds reaches a iteration count of 68,000,000 or greater, if so, it will deem it improperly bounded. I think that it's fair to say that if you're iterations are in the millions in the first place, some kind of normalization needs to be implemented. If you wish to control this bound, you can buy piping the value #

Int Iterator = 0;
If Iterator < -1{
	Out(Iterator);
} ? I++ | 2000;

# You can also make the bound infinite by passing nothing. Here's the shotgun you might've been looking for. #
Int Iterator = 0;
If Iterator < -1{
	Out(Iterator);
} ? I++ |;


```


Everything largely translates directly into some kind of C derivative, whether that's a keyword, operators, or function.

```
Out("Hello");
```


```C
printf("Hello");
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
Str Answer = "Purple";

Str UserInput = In("What's my favorite color?");
If UserInput is Answer {
	Out("You it got right!");
} Else {
	Out("You got it wrong!");
}
```

`>` - Greater than comparison
```
Int Hunger = 50;

If Hunger > 50 {
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
>I'm not hungry

`>=` - Greater than or equal to comparison
```
Int Hunger = 50;

If Hunger >= 50 {
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
> I'm hungry

`<` - Lesser than comparison
```
Int Hunger = 50;

If Hunger < 50 {
	Out("I'm hungry");
} Else {
	Out("I'm not hungry");
}
```
> I'm not hungry

`<=` Lesser than or equal to comparison
```
Int Hunger = 50;

If Hunger <= 50{
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
If <Conditional> {
	<Statement>;
}



If Food is Expired {
	Out("Food is expired");
}
```

`Else` - Use after `If` statement to use specified code block if condition in `if` is not met.
```
If <Conditional>{
	<Statement>;
} Else {
	<Statement>;
}




If Food is Expired {
	Out("Food is expired.");
} Else {
	Out("Store this food.");
}

If Food is Grapefruit {
	Out("I don't like this food.");
} Or Food is Strawberries {
	Out("I like this food.");
} Else {
	Out("I don't know about this food.");
}
```

```

[Chapters](#chapters)
# Objects
Objects have built-in functions that can be utilized to implement your own behavior on top of. Below are the built-ins described.

`New` - Called when a object is instantiated
`Destroy` - Called when a object is destroyed
`Get_Obj` - Utility function returns a list of two elements: the object name, and memory address

Obj <DelcarativeName>:
	Fnc New: Parameters
	{
		<Statement>;
	}
;

Obj Human:
	Fnc New: Int Name, Int Age
	{
		Str _Name = InitName;
		Int _Age = InitAge;
	}
;

Human Jerry = Jerry("Jerry", 15);
Out(Jerry.Get_Obj()); # Outputs: [Human, Human<0x6dfed4>] #
Jerry.Destroy();
Out(Jerry.Name)
```

[Chapters](#chapters)
# Functions

```
Fnc <DeclarativeName>: Parameters
{
	<Statement>;
}
```
```
Fnc Addition: X, Y
{
    Return X + Y;
}

Addition: 5, 10;
```

[Chapters](#chapters)
# Importing
find is used to import code from another file.

```
~<File-Name>:<Declarative-Name>

~Graphs:2DPlot
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
