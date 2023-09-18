[[Toran]]

# Explanation

Toran is an architecture with an embedded software suite, a programming language with a compiler, interpreter, and a runtime for that language. Toran (ToranV) will be available as a virtual environment atop a host environment. A standalone Toran (ToranC) will be available as an computer all-in-one computer. A Toran OS (Toran OS) will be available to boot onto almost any computer.

---

Focus on the use of data-driven development, wrapped around a procedural model.

There will be rules, and guidelines on structuring Toran, and it’s tools. Rules _must_ be followed, and guidelines are recommended as defaults when one has no alternative, but are not meant to constrain development in any way, so do not get stuck trying to follow them.

---

_Some words can be swapped out with other words for better understanding of the abstraction at hand_

<aside> 📖 “Function” ~ Process, Action

</aside>

---

### Rules

- Define the data that is expected, and conform processes to the expectation.
    - A function should never define, or generate data.
    - A function should only return data, dependent on the processes execution.

---

### Guidelines

- All data should be procedurally generated and dependent on returned results from functions.

---

### Diverging Linear Scheme

This is the abstraction that is used throughout Toran. This paradigm is not necessarily recommended for casual use. It is only for covering absolutely every single use-case and edge-case.

This paradigm is used to have absolute control over the entirety of a project. It can be used for individual files, or modules, but is not recommended, it’d be a bit overboard.

Dynamic behavior isn’t impossible with this paradigm. DLS just doesn’t use state, and state change to implement dynamic behavior. Dynamic behavior is done by using safe, and constrained concurrency.

Concurrency should only be used if you are expected two different outcomes, however if you are expecting to different outcomes, you probably shouldn’t be putting them in the same program/project anyways. Programs using programs, and so on, are safer, and simpler idea than a single program with dynamic behavior that has objects with unused inherited data, invisible edge-cases, and impossible to reach out-of-bounds errors. Modulization and unifying is key; avoid complex procedures, and mutability.

Using “Context Codes” a program is broken up into it’s potential possibilities and divergencies.

A context is a returned data from a function. The context of a program always exists singularly, there are no, and should never be clones, or copies.

A variable is a normal variable, but this design pattern enforces rules on where variables are declared. Variables should never be declared within a function. If you pass a variable into a function, the variable must be treated as immutable. A function should return _new_ data, dependent on the given data from the last given context.

If we’re moving into a new functions dependent on the context, we use alphabetical identification.

If we’re using a conditional within a function on the context, we use numerical identification.

If we’re changing logic spaces holding the context, we use a period to partition the context code delineating the next procedure.

_Explanation:_

A diverging linear scheme is a model of architecture or an application that relies on defining the expected data, and linear processes. Dependent on the returned data from the functions.

---

### Pythonic Implementation