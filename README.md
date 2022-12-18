# Intro, motivations, and materials

This file will document some of the important things that I learned with regards to developing software in C. I will be making a demo of a basic Breakout game in order to learn some of the standard methods of programming a Windows application in C. This motivation for this is to have an example project of C to show in interviews and on github, and to start learning how to develop applications for Windows using only C.

#### Walkthroughs 
The walkthroughs that I followed for developing this game were Dan Zaidan's **"Making a game in C from scratch"** on youtube:

https://www.youtube.com/watch?v=M0yE4Kl85to&list=PL7Ej6SUky1357r-Lqf_nogZWHssXP-hvH

as well as Casey Muratori from Molly Rocket's **"Intro to C on Windows"** and **"Windows platform layer"** series from building Handmade Hero:

https://www.youtube.com/watch?v=Ee3EtYb8d1o&list=PLEMXAbCVnmY4ZDrwfTpTdQeFe5iWtKxyb

https://www.youtube.com/watch?v=F3ntGDm6hOs&list=PLEMXAbCVnmY6RverunClc_DMLNDd3ASRp

The Handmade Hero series is a detailed and very beginner-friendly introduction to C programming. Casey goes in depth about a lot of important concepts in programming with a lower level language like C, and he frequently takes extra time for side tangents, history, and explanation. Dan Zaidan's series is much faster paced, and gets into game development very quickly, so knowing some C programming going into the series is probably most helpful for actually knowing what he is doing.
        
#### Books
*"The C Programming Language, 2nd Edition"* by Brian Kernighan and Dennis Ritchie is an excellent text to have for learning C. The examples and practice exercises are pretty good, and the book is very information dense for such a small book. Its a little dry as it is a textbook, and definitely treats the reader as an already fairly proficient programmer.

*"Programming in C"* by Stephen Kochan is also a great resource for C programming. It is a larger book, that takes a little bit more time to teach or remind the reader about basic programming principles, data types, and more. There's really great example code, as well as incredibly good exercises that would be right at home in a classroom. This book is also much newer than *The C Programming Language*, so a lot of the information is updated, and the whole style of the book and the writing in it feel much more modern and understandable. If you're a newer programmer, much like I am, this is probably the best book about C that you can find.
      

# Tools

**Text Editor**: 4coder

Dan uses 4coder in his tutorials so thats what I used as well for simplicity. Setting up 4 coder requires a 4coder project file, a build file, a run file, and all of your actual program files. The project file just shows details about the project, as well as shortcuts and commands you can specify for your project. The build file gives build and compile instructions, and the run file just runs the executable. These two files allow you to specify and give shortcuts to the terminal commands you would otherwise have to run everytime. 4coder offers a lot of customization for a text editor, and also has automatic indentation and code spacing which is incredible, but doesn't offer much in the way of debugging, so we'll need to use something else. 

**Debugger**: Visual Studio

Visual Studio is the classic IDE for Windows development, the debugger is great, and there's a ton of tools you can add. I think overall if I were to do this all over again I would probably just use Visual Studio for everthing, having a text editor doesn't seem incredibly necessary to me.

**Compiler**: GCC

The compiler used here is the GNU Complier Collection or GCC. Dan actually uses cl, which I think comes from VisualStudio, but it seems like gcc is equally or more popular for c compiling. I downloaded the minGW x64 file for my machine and added the path.

# C Programming

#### Variables (signed and unsigned)

C has the very standard variables most programming languages have mainly:
- int
- float
- char
- bool

The main thing to note about variables in C is the difference between signed and unsigned variables. Differentiating if the variables run into negative values, or remain as soley positive numbers. For example an 8 bit int is a signed variable, and runs from -128 to 127, but if specified as an unsigned int, it will run from 0 to 255. Floats work in the same way.

The specific size of the variables usually depends on your machine, so you don't always need to specify, but you always can do so if you need. The "double" variable can also be useful, as it is a float that can hold twice as many significant figures.

#### Pointers

Pointers are extremely important in C, partially because they are the most popular way to create arrays in C.

Pointers in C are the same in other languages in the fact that they are simply pointing to a specific location in memory, usually the address of a variable of interest. There are numerous reasons that these are useful outside of the afforementioned arrays. You can declare a pointer to a variable's address like this:

                int x = 10;
                int *pointer_to_x; // The * at the declaration signifies this variable is a pointer
                
                pointer_to_x = &x; // The & signifies the address of the variable. 
                
I've personally found the pointer declaration kind of confusing, since when you declare the pointer and you're specifying its type you must prefix it with "\*", signifying it's a pointer, but then when actually using the pointer normally you drop the "\*". 

And actually, after declaring and initalizing everything above, and pointer_to_x represents &x, it is now known that 

                *pointer_to_x = x.

I like to think of the "*" as actually meaning "the real variable stored where this pointer is pointing to", but thats what we have to initialize it with.

but then afterwards

                pointer_to_x, means the pointer to the address
and

                *pointer_to_x, means the value of the variable that is located in that address.
                
I'm sure most people understood this much faster than me, I just found it confusing.

#### Arrays

Arrays in C can often be pretty different than other languages, they are in fact just a pointer to one place in memory, which can be considered the start of the array. Then you can store the information you need sequentially, in spaces after that starting point.


<img src="https://user-images.githubusercontent.com/38634070/208217985-0ad84842-77c7-44f1-9523-1bc2cbe9833a.png" width="640" height="300">

This lets you do some real funky things so its important to be careful. For example you can just increment your initial pointer, like in this example just

                p*++; 
                
And boom, your array now starts one place up, and you've left that first variable behind. But you can also actually decrement, completely into the unknown memory behind your array.

                p*--;

I think this will make it pretty easy to shoot yourself in the foot, but they have a ton of interesting functionality.

#### Structures

From tutorialspoint.com, I will state their definition of a struct.

###### structure is another user defined data type available in C that allows to combine data items of different kinds.

I cant help but think these are similar to objects in Java, although I'm sure there are enough differences that that is not a good comparison. C isn't an OOP language after all. Heres a visual example of declaring a struct.

<img src="https://user-images.githubusercontent.com/38634070/208032328-b382d1af-9dbe-44b3-b258-222733130db2.png" width="400" height="400">

The structure is basically a framework for a group of variables and data of all types. They have massive amounts of variability and functionality and I'm sure most programmers will find themselves very comfortable in creating and handling them.

#### Type Casting

In higher-level languages, they will always complain if you are trying to use a variable type that isn't correct in the context you've used them in. C however allows you the power to say "I know this variable isn't the type that this function or procedure wants, but I know what I'm doing, so do it anyway". 

The following example, again from tutorialspoint, illustrates an example here.

                #include <stdio.h>
                main() {

                        int sum = 17, count = 5;
                        double mean;

                        mean = (double) sum / count;
                        printf("Value of mean : %f\n", mean );
                }

In this example, the variables sum and count are type *int*, but the mean is a *double*, which is a floating point variable. Normally you would not be able to do any calculations with these different types of variables, so:

                mean = sum / count; // This line will break the program
                
Will absolutely throw an error at you, reminding you of the fact that these are different data types. But if you add (double) to the begining of the equation. It signifies that the program should treat these integer variables as if they were floats, and the program runs just fine. C is doing something in the background to convert the types of these variables, so if you want to use type casting, it is crucial to understand exactly how C is converting your variables, and what effect they will have, because they are not all this simple.

#### The *Static* Keyword

Based on the tutorials I've seen, people really hate how the C language uses the word static. It can mean up to three very different things that are entirely dependent on context. Static can mean:

- A global variable, not visible outside of the file it is defined in.
- A locally persisting variable within a function, that doesn't lose its value between function calls.
- A function that is not visible ouside of the C filed it is defined in.

From the tutorials, it seems common to define your own keywords for these different meanings, so you can keep track of which version of "static" you actually mean to use. Something like this:

                #define internal_function static
                #define local_persist static
                #define global_variable static
                
Now all three of these keywords can be used in place of static, but it gives a more accurate definition of which type of static the programmer meant.

