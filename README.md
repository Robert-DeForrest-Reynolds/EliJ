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

---

I try to take a bit of a different perspective to this whole programming thing. I don't like doing things that same way the previous someone before did it.

Pineapple is the name of the language. Iwa is the name of the compiler I built for it.
Iwa utilizes C, and Clang to generate C code.

Pineapple is fundamentally made up of 4 things: Declarations, Structures, Conditionals, Functions

Pineapple gets translated into an intermediate language using Python that is easier to work with, that is then used when generating C code. This intermediate code can then be easily made compatible with any compiler.

### Guiding Principles & Opinions:
- Modularity over inheritance. It isn't too hard to make modularity messy, but it's very easy to make inheritance hell. Complexity is achieved through individual abstractions in multitudes.
- Programming languages allow us to talk to computers, but more importantly, it allows them to talk to us, and tell us what they are doing. When someone else comes along and reads your code, it best damn well tell them what the computer is doing. Don't hide things, make jokes at the expense of humor, not the program, and never, ever, for the love of all that is mighty, forget your documentation.
- Technology is a conceptualization to help us. Don't deny it's implementation to make your life easier. Technology will inevitably push us farther and farther as the human capacity for experience craves more than what it had yesterday. We can still keep our humanity while implementing technology for it's great benefits, with positive intents. TLDR; VR good, TikTok bad.
- A compiled, released program should never depend on another program to run. It should be absolute, and complete. This is not to say that two programs interacting with one another is bad, but more specifically, this tends leads to one-sided interactions between two programs which has proved to be very bad.
- The idea "everything in programming is an object" is a good thing. Most of the time, the backend of a language being structured as so, and allows the programmer to develop a program that is naturally modular. An integer is a object, just as much as a cat is.


#### Lifecycles
Pineapple Source Code -> Iwa Compiler -> C Code -> Clang -> Executable
Pineapple Source Code -> Iwa Compiler -> C++ Code -> Clang++ -> Executable

#### Symbols
```
+ # Addition #
- # Subtraction #
+= # Increment and assign #
-= # Decrement and assign #
* # Multiply #
/ # Division #
% # Get Remainder #
== # Equals #
!= # Not Equals #
& # And #
\ # Or #
' # String Wrapper #
~ # Import #
, # List Separator #
() # Multi-line Data Wrappers #
{} # Multi-line Data Wrappers #
```

#### Reserved Keywords
```
Str
Int
Flt
Obj
Return
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

Pineapple parses line-by-line, and does not care about indentation. Whitespace between keywords is required, but is not required between symbols, for example: `Int X=5` is valid, but `IntX=5` is not as there is no way for the compiler to identify the type, and declarative name.

```
# As `=`, `"`, and `;` are symbols, and `Str` and `Name` are keywords.
Str Name="Sirley";
```

You can think of every line as a statement. A line can contain two statements, but the philosophy of the languages asks for modularity, and to conform to the single-responsibility principle, within reason. We have opening, and closing tokens for code blocks containing multiple statements, and most importantly, all variables are immutable by default, and when the values are changed, if they are not assigned, they are not held.

Pineapple's memory management aims to be simple, easy to use, and east to extend. Iwa analyzes the source code you feed it, and attempts to create a memory safe program by testing against the bounds of each variable. Everything is dynamically allocated otherwise, and if you need to take control of memory, you can access the control flow exactly how you would an array.

All `Int`'s are 64 bit signed integers by default unless otherwise compiling for a 32 bit system. Pineapple explicitly supports standard implementions over backwards compatibility, and future proofing. Therefore an expectation is allowed that you have access to the largest forms of data structures allowed by the system.
When you download the compiler for 32 bit systems, they will be 32 bit integers.
The `O` flag when compiling will tell Iwa to optimize, and finds the outer bounds of each integer case, and utilize a integer will less bits if allowed.
```
Int X = 5;
Int Y = 6;

Out(&0);
```
Outputs:
```
5
```

You can assign values
```
&0 = "I'm a string";
```
Outputs:
```
ERROR | &0 = "I'm a string";
		 ^ is typed: Int, cannot implicitly cast to: Str

Explicit Cast Example:
Str Greeting:&0 = "I'm a String"	 
```

Pineapple's memory space accepts the ultimate foot-gun in favor of an explicit, and simplistic knowledge on how it works. Everything in the program is bounded, living, and accessible. Everything outside of the program is not accessible.

The Iwa compiler tests all accessible bounds, and determines if the declarative bounds are measurable. If they are not, you will be provided an error at compile time dependant on the context, and you will have to flag the specific variable UNBOUNDED, or you will have to guard against it's bounds.
```
Int X = 5;
While X < 0{
	Out(X);
	X++
};
```
Outputs:
```
ERROR | Unbounded Loop
```

```
Int X = 5;
If X < 0{
	Out(X);
} ? X++ | 2000;
```
Outputs:
```
ERROR |
If X < 0{
} ? X++ | 2000;
  ^ Touched bounds during compilation
```

You can explicitly cast `Int`'s if one would like.
```
Int x = 5;  // Default to system word size
Int64 y = 1000000000000;  // Explicitly 64-bit
Int8 z = 100;  // Explicitly 8-bit

Fnc ProcessData: Int32 data {
    // Function that explicitly works with 32-bit integers
}

// Compiler error that this will probably overflow:
Int8 small = 200;
```
Pineapple attempts to take on a form of test-driven philosophy during compilation. Iwa will not let you compile what it thinks to be an unsafe program unless you painstakingly accept the consequences. This means that you should never ship a production product that does not check against it's bounds before compile time. All bounds are checked at 2 million by default.

### Quick & Dirty Summary

Comments:
```
# I'm a comment #

#
Anything between
two pound signs
is a comment
#
```

Importing:
```
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
```

Output:
```
# Printing out information to the console, and function call example #
Out("Hello");
```

Input:
```
# Wait for input from the user #
Str UserInput = In();
```

Variables:
```
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
```

Math:
```
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
```
Casting
```
# Casting #
Flt Wallet = 5.26;
Out(Cast(Wallet, Int)); # Outputs: 5 #
# Iwa will automatically floor float conversions, if you want it rounded, you'll have to round it #
Out(Cast(Rnd(Wallet), Flt))`
```

Rereferencing:
```
Ref Rnd = Round;
Out(Rnd(2.5));
# Outputs: 3 #
Out(Type(Rnd(2.5)));
# Outputs: Int #
```
Copying/Duplicating:
```
Int Total = 50;
New Total;

```
Strings: 
```
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
```

Functions:
```
Parameters are passed by reference by default, or you can decide to make a copy #
Fnc Sum: Number1, Number2 {
	Return Number1 + Number2;
}

# Variables not declared in place will be held as anonymous in memory #
Sum(Int 5, Int 6);


```

Objects:
```
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
```

Conditionals:
```
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

# There are no for, or while loops, instead Pineapple has looped conditionals
For Str Fruit in Fruits {
	Out(Fruit);
}

Dct Students = [
	"Kevin":14,
	"Bill":15,
	"Julia":14,
]

For Str Name, Int Age in Student{
	Out("{Name} is {Age} years old");
}
```
The compiler will try not to allow you to create "Improperly Bounded While Loops". At least it will rationally attempt to catch them.
The below out will produce an error that will not allow you to compile because it can never be identified that Alive will ever be made true.
Iwa will make great attempt to test down a loop-chain, ensuring that each variable is changed, or at least referenced within a bounded count.
```
Bln Alive = False;
While Alive == True {
	If Alive == true {
		Alive = False
	}
}
```

Iwa would warn against the below code, because it does not mutate the variable that the conditional is checked against at all.
```
Int Health = 50
Bln Alive = False;
While Alive == True {
	If Health <= 0 {
		Alive = False
	}
}
```

This code would be allowed to compile, as long as it passed the default 2 million bound check. Which it would not, as it would only iterate 50 times.
```
Int Health = 50
Bln Alive = False;
While Alive == True {
	If Health <= 0 {
		Alive = False
	}
	Health -= 1
}
```

You can bound loops to a specific iteration count yourself. The below code would not compile, and throw an error. This is my take on how to solve memory safety problems. We clearly define the limits we're willing to allow our program to break. If it breaks, we do not allow it in production. If we don't know the bounds, we test for them. If we do know the bounds, we assert we're within them.
```
Bln Alive = False;
While Alive == True {
	If Alive == true {
		Alive = False
	}
} ? 2000;
```

You can also make the bound infinite by passing nothing. Here's the shotgun you might've been looking for. This code will compile, but will warn you, and you *cannot* turn off this warning.
```
Bln Alive = False;
While Alive == True {
	If Alive == true {
		Alive = False
	}
} ?;
```


Everything largely translates directly into some kind of C derivative, whether that's a keyword, operators, or function.

```
Out("Hello");
```


```C
printf("Hello");
```


# Developer Notation

#### Core Ideas:
 - Graphical Implementations should be accessible within the Standard Library
 - There are many ways to say something, there is only one best way to do something, and it has to be obvious.
 - Complexity flourishes with creative simplicity.
 - Higher-Level Abstractions are never a bad thing.


