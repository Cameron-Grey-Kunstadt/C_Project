## Intro

This document will outline the essential steps involved in creating a simple breakout game in C.

## Making a window (On a Windows system)

In order to create a graphical application on a Windows system, you must refer to the documentation of the Microsoft Developer Network (MSDN). This documentation teaches how to properly communicate with the windows OS to be able to run your application. Make sure to include 
#### <windows.h> 
at the top of your program.

***
The very first thing to do is to establish an entry point for Windows using WinMain.

Documentation here: https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain

Unfortunately the examples given in MSDN are all in C++, and while almost everything will be the same, sometimes there are small differences. Also the MSDN docs have this rather annoying habit of having [in] in front of all the parameters to specify it is being passed into the function. These all need to be deleted for our code. Additionally, the \_\_clrcall modifier on this function is also not needed for our purposes here, and can be removed. Feel free to research that if you so choose.

When all is said and done we go from this, from the docs:

![image](https://user-images.githubusercontent.com/38634070/207461957-7914c33d-984c-4ee0-bbb1-9345d945f1cc.png)


To this, in our code:

![image](https://user-images.githubusercontent.com/38634070/207462140-7a9eb707-5329-430f-9462-683a702d1e36.png)

I wont show these differences in every case, but I just wanted to highlight the fact that there will be some small changes like this in the rest of our program.

But we have our entry point! 
***

Now we can get started making a window, the next thing we need is WNDCLASSA struct. This struct essentials just holds a bunch of variables that Windows needs filled in. For most purposes, many of these variables can just be set to zero, so I'd start with the line:

WNDCLASSA window_class = { };

##### By default in C, setting a struct = { }, or struct = {0}, sets every variable in the struct equal to 0. This is referred to as "clearing to zero".


Doc here: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa

After setting all the variables in that struct to 0, we can change the few we actually need. These style modifiers are typically the default ones included, you can do your own research about others. The lpdnWndProc is a Windows Protocol function that we will define in the next steps, for now we will just name it window_callback. The hInstance is the instance of our application we can just pass to the window_class, and then lastly we can just give the class a name. Now our code looks like this: 

![image](https://user-images.githubusercontent.com/38634070/207518182-9d75e421-98c7-4f70-84da-763ba718f6f2.png)

So, we have WinMain, and within it we declared a WNDCLASS struct called window_class, and specified the variables that are important to our program. The next thing we need to fill in is our Windows Protocol function that we named window_callback. This procedure is just going to specify some instructions on how our application should respond to different messages coming from our systems. 

Doc here: https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

To skip over some of the small details, let's just take a look at how this window_callback should be filled in for now.

![image](https://user-images.githubusercontent.com/38634070/207523679-ccce9d8f-54ca-4153-b12c-138eea050e96.png)

We can see our LRESULT window_callback, as well as a few parameters to pass into it, the window, the message, w_param and l_param, which contain some additional info. 

Then that line 

#### LRESULT Result = 0;

basically states that our programs default response to a message is equal to 0, which for windows essentially means "That message was handled, we took care of it".

The large switch statement specifies how our program should process different messages, the names WM_SIZE, WM_DESTROY, and WM_CLOSE are all windows specific cases and can be searched in the docs to find valid responses and more information, for now we'll just leave these blank.

Then our default setting just specifies what our default response to any normal message should be, we need a "catch-all" response for anything windows might ask of our program. Here we set our LRESULT Result equal to DefWindowProc, which is a default procedure that will work for most handling most cases. We pass in the same variables as our window_callback. Then we just make sure our function returns our Result, and we're good to go. Protocol done!



