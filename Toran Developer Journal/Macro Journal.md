### Brain Vomit for Interested Readers
I want to build a very performant OS-like "platform", Toran. On this platform will be a multitude of different pre-built applications providing tools in different fields. A programming language and 
scripting language will be avaiable for use within the platform without need of any external tools. However the use of external tools will be heavilty supported.

I want Toran to be able to run on anything literally. That means as a desktop application, or within the web browser. On mobile, or even small low level hardware devices.
I want Toran to be interpretable for sanity sake, but compilable, and executable anywhere as to be downloaded onto an external USB or sort to run anywhere, anytime, on anything.

This all lies in the technology implemented, and the patience of myself as a developer. I plan on taking this on as a single developer, and sticking to that for some time. I want there to be a well refined, ironed out product that is described and implemented well, before I even think about open-source, or suggesting using it in commercial or large-scale production.

Eventually Toran may hopefully be built into a bootloadable operating system written completely in Pineapple, that only requires the compatible hardware. Anyone will be able to take the Pineapple standard, and implement it, whereever they'd like. There will be 16-bit, 32-bit, and 64-bit versions of the standard.

A rapid prototype could be built, but I'll have to research a bit more to find out which language would be suitable. This would only accomplish user-testing the abstractions at hand, which is pretty much useless, but may be required just to cover the edge-cases.
In the meantime, I need to work on Pineapple's standard more.

# The Toran Suite

### Pineapple
Akin to C, or OpenGL, Pineapple will be codified as a standard, and implemented as the standard describes it.

Iwa will be the official compiler for Pineapple, that will come packaged in the download.

Iwa takes Pineapple code, and generates assembly from it, meaning that Pineapple compiles directly to assembly with no in-between.

Transplires for every modern language is one of the huge goals of Pineapple.

### Iwa
Iwa's goal is to be an incredibly smart compiler.

**Feature List**
 - Optional Memory-Safety during Compilation

### Lily
A virtual machine for runtime of executables, or to run Pineapple scripts on very efficiently.

**Feature List**
 - Built-in Garbage Collection
 - Optional Manual Memory Management

### Developer Notes
