<p align="center">
  <img src="./media/banner.png" alt="Ciphron Banner">
</p>

# Ciphron

**Introspection for your code.**

> Ciphron is a play on “C interpreter” and “phronesis” (ancient Greek for practical wisdom).  
> The logo, which recalls Sigmund Freud, hints at the idea of interpreting—just as Freud interpreted dreams, Ciphron interprets your C-style commands in real time.

## 🎬 Demo

<p align="center">
  <img src="./media/demo.gif" alt="Ciphron demo">
</p>

## 🔎 What is Ciphron?

Ciphron is a tiny C-style REPL (Read-Eval-Print Loop) that lets you declare variables, print values, and introspect types right from your terminal. Inspired by C syntax, it’s a playground for anyone curious about interpreters.

## 🧠 Features

- **Declare** integer and string variables at runtime
- **Print** the value of any defined variable
- **Type introspection**: use `:t varname` to check a variable’s type (just like Haskell)
- **Error messages** for unknown variables or invalid syntax
- **Minimal, hackable codebase**—easy to read and extend

## 🛠️ Installation

**Requirements:**

- GCC or any standard C compiler
- (Recommended) Make utility

### 🔹 Option 1: Build and run with `make`

```bash
git clone https://github.com/antoniocaporrini/ciphron.git
cd ciphron
make
./ciphron
```

### 🔹 Option 2: Build without `make`

```bash
git clone https://github.com/antoniocaporrini/ciphron.git
cd ciphron
gcc ciphron.c common.c -o ciphron
./ciphron
```

## ▶️ Usage

Start Ciphron from your terminal:

```bash
./ciphron
```

You’ll see the Ciphron banner and the prompt:

```bash
ciphron>
```

Here are some example commands you can try:

```bash
ciphron> int x = 5;
Variable 'x' set to 5

ciphron> string dev = "Antonio";
Variable 'dev' set to "Antonio"

ciphron> print x;
x = 5

ciphron> print dev;
dev = "Antonio"

ciphron> :t x
x :: int

ciphron> :t dev
dev :: string

ciphron> print y;
Variable 'y' not found

ciphron> exit
```

## 🗺️ Roadmap

- [x] Declare integer and string variables dynamically
- [x] Print variable values
- [x] Type introspection (`:t varname`)
- [x] Error handling for unknown variables and invalid syntax
- [ ] Arithmetic operations and variable assignment (e.g., `x = x + 1`)
- [ ] Command history and editing
- [ ] Built-in help system (`help` command)
- [ ] Add a minimal parser/lexer for richer expressions
- [ ] (Future) Integrate a simple compiler or code generation module

## 🧩 Design Philosophy

Ciphron is currently a minimal REPL: It is not a full interpreter or scripting engine (yet!)—but its modular codebase is designed for easy extension toward more advanced language features, or even basic compilation in the future.

<img src="https://img.shields.io/badge/Built%20with-Love%20%26%20Freud%20in%20mind-blueviolet" alt="Built with Love & Freud in mind ❤️" />
