### Principles & Conventions

One of the core motives of Pineapple is to provide a better interface to a compiled language. Here are the core beliefs, and features that motivated the creation of Pineapple:
- Idiomatic syntax; programming languages help us talk to computers, but just as so, they allow computers to tell us what they are doing. If you're writing something useful, someone will read your code eventually probably. Make sure they can actually understand it when they do.
- The compiler needs to guide you to properly leveraging it; the vernacular when outputting errors must be clear, concise, and contain all of the necessary notation to access the error's properties. Just as well, functions, and behavior created by the developer should be clearly, and concisely named, documented, and provide the necessary links to all of the related properties involved. A user of the language should never get lost within thousands of lines of someone else's code, if they understand the absolute fundamentals.
- The fundamentals of something should be small and simple; the single-responsibility principle is the most universal method to organizing complex systems within code. This does not mean you cannot successfully create abstractions that use multiple responsibilities, however, take care to not create such a complex abstraction that a mind cannot easily grasp it.
- Complexity is built from abundant simplicity; if we follow the previous principle of providing simple fundamentals. Building an abundant amount of simple fundamentals is what constitutes a complex system.

#### Lifecycles
Pineapple Source Code -> Peach Parser -> Intermediate Data Files -> Iwa Compiler -> C++ Code -> Clang++ -> Executable
Pineapple Source Code -> Peach Parser -> Intermediate Data Files -> Lily -> Output