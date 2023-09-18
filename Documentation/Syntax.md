# Chapters

Statements are ended with semi-colons.
Code blocks are started and ended with curly brackets.

All of this info is to be migrated elsewhere, and this file deleted

 - [Operators](#operators)
 - [Keywords](#keywords)
	 - [Type Delcarations](#type-declaration)
	 - [Decision Making](#decision-making)
 - [Functions](#Functions)
 - [Standard Library](#standard-library)
 - [Developer Notation](#developer-notation)

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
[Chapters](#chapters) - [Top of page](#iwa-reference)
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
Out(10 *//* 2);
```
>20

`=` - Assignment
```
integer Health = 50;
```
>5

`is` - Equality comparison
```
Answer = "Purple"

UserInput = In("What's my favorite color?")
if UserInput is Answer{
	Out("You it got right!")
} else {
	Out("You got it wrong!")
}
```

`>` - Greater than comparison
```
Hunger = 50

if Hunger > 50{
	Out("I'm hungry")
} else {
	Out("I'm not hungry")
}
```
>I'm not hungry

`>=` - Greater than or equal to comparison
```
Hunger = 50

if Hunger >= 50{
	Out("I'm hungry")
} else {
	Out("I'm not hungry")
}
```
> I'm hungry

`<` - Lesser than comparison
```
Hunger = 50

if Hunger < 50{
	Out("I'm hungry")
} else {
	Out("I'm not hungry")
}
```
> I'm not hungry

`<=` Lesser than or equal to comparison
```
Hunger = 50

if Hunger <= 50{
	Out("I'm hungry")
} else {
	Out("I'm not hungry")
}
```
> I'm hungry

[Chapters](#chapters) - [Top of page](#iwa-reference)
# Type Declaration

**`string` - String Type**
```
string Greeting = "Hello";
```

**`integer` - Integer Type**
```
int Age = 18;
```

**`float` - Float Type**
```
float Pi = 3.141;
```

[Chapters](#chapters) - [Top of page](#iwa-reference)
# Decision Making

`if` - Use specified code block if condition is met
```
if <Conditional>{
	<CodeBlock>
}



if Food is Expired{
	Food.Throw_Away();
}
```

`else` - Use after `if` statement to use specified code block if condition in `if` is not met.
```
if <Conditional>{
	<CodeBlock>
} else {
	<CodeBlock>
}



if Food is Expired{
	Food.Throw_Away();
}else{
	Food.Store();
}
```

There is no `Else If`, or `Or` conditional. Instead with Pineapple, you're expected to use pair indexing, as it's faster.
```
pair <DelcarativeName> = [Potentional:Outcome,
						  Potentional:Outcome,
						  Potential:Outcome,]

<DeclarativeName>[ConditionalData]

pair Colors = [Red:Stop,
			   Yellow:SlowForRed,
			   Green:Go,];

Colors[Red];
```

[Chapters](#chapters) - [Top of page](#iwa-reference)
## Types
Types have built-in functions that can be utilized to implement your own behavior on top of. Below are the built-ins described.

`New` - Called when a type is instantiated
`Destroy` - Called when a type is destroyed
`Name` - Utility function used to 

```
Obj <DelcarativeName>{
	>New(Parameters){
		<CodeBlock>
	}
}
```
```
Obj Human{
	>New(Name, Age){
		Self.Name = Name
		Self.Age = Age
	}
}
```

[Chapters](#chapters) - [Top of page](#iwa-reference)
## Functions

```
Func <DeclarativeName>(Parameters){
	<CodeBlock>
}
```
```
Func Addition(X, Y){
    return X + Y;
}

Addition(5, 10)
```

[Chapters](#chapters) - [Top of page](#iwa-reference)
## Import & Find
find is used to import code from another file.

```
find <File-Name>.<Declarative-Name>

find Graphs.2DPlot
```

[Chapters](#chapters) - [Top of page](#iwa-reference)

## Built-Ins

`In()` - Take in input from the user

`Out()` - Output something to the console

[Chapters](#chapters) - [Top of page](#iwa-reference)

## Developer Notation

#### Core Ideas:
 - Graphical Implementations should be accessible within the Standard Library
 - There are many ways to say something, there is only one best way to do something, and it has to be obvious.
 - Complexity flourishes with creative simplicity.
 - Higher-Level Abstractions are never a bad thing.

[Chapters](#chapters) - [Top of page](#iwa-reference)
