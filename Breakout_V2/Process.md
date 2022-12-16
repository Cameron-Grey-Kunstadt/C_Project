## Intro

This document will outline the essential steps involved in creating a simple breakout game in C. Some of the information here is already a bit outdated as Microsoft has made some new functions that supersede some of the ones here, but they still function perfectly well for our purposes here in making a simple game to learn C. I've also included excesive comments in this version of the code for explanation purposes, but see Breakout_V1 for the more consise version.

## Making a window (On a Windows system)

In order to create a graphical application on a Windows system, you must refer to the documentation of the Microsoft Developer Network (MSDN). This documentation teaches how to properly communicate with the windows OS to be able to run your application. Make sure to include 
#### <windows.h> 
at the top of your program.

***

#### WinMain (Our entry point)
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
#### WNDCLASS (Our window class)

Now we can get started making a window, the next thing we need is WNDCLASSA struct. This struct essentials just holds a bunch of variables that Windows needs filled in. For most purposes, many of these variables can just be set to zero, so I'd start with the line:

    WNDCLASSA window_class = { };

##### By default in C, setting a struct = { }, or struct = {0}, sets every variable in the struct equal to 0. This is referred to as "clearing to zero".


Doc here: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa

After setting all the variables in that struct to 0, we can change the few we actually need. These style modifiers are typically the default ones included, you can do your own research about others. The lpdnWndProc is a Windows Protocol function that we will define in the next steps, for now we will just name it window_callback. The hInstance is the instance of our application we can just pass to the window_class, and then lastly we can just give the class a name. Now our code looks like this: 

![image](https://user-images.githubusercontent.com/38634070/207518182-9d75e421-98c7-4f70-84da-763ba718f6f2.png)

***
#### Windows Protocol
So, we have WinMain, and within it we declared a WNDCLASS struct called window_class, and specified the variables that are important to our program. The next thing we need to fill in is our Windows Protocol function that we named window_callback. This procedure is just going to specify some instructions on how our application should respond to different messages coming from our systems. 

Doc here: https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

To skip over some of the small details, let's just take a look at how this window_callback should be filled in for now.

![image](https://user-images.githubusercontent.com/38634070/207523679-ccce9d8f-54ca-4153-b12c-138eea050e96.png)

We can see our LRESULT window_callback, as well as a few parameters to pass into it, the window, the message, w_param and l_param, which contain some additional info. 

Then that line 

    LRESULT Result = 0;

basically states that our programs default response to a message is equal to 0, which for windows essentially means "That message was handled, we took care of it".

The large switch statement specifies how our program should process different messages, the names WM_SIZE, WM_DESTROY, and WM_CLOSE are all windows specific cases and can be searched in the docs to find valid responses and more information, for now we'll just leave these blank.

Then our default setting just specifies what our default response to any normal message should be, we need a "catch-all" response for anything windows might ask of our program. Here we set our LRESULT Result equal to DefWindowProc, which is a default procedure that will work for most handling most cases. We pass in the same variables as our window_callback. Then we just make sure our function returns our Result, and we're good to go. Protocol done!

So far, we have WinMain, our entry point into the program, defined a window_class struct, which we've filled in with some important information about our program that windows needs, and we've made window_callback, our windows protocol function, that specifies the protocols for dealing with messages between windows and our program. Next thing we need is to Register our program. This will happen within the WinMain function.

***
#### Register and Create our Window
The windows registry is a database on our windows machines that holds the information about software applications, how they need to be ran, information, settings, etc. We just need to pass some basic information to this registry, so that windows knows how to run our application.

Again, skipping past some of the details, here is our entire function of WinMain now.

![image](https://user-images.githubusercontent.com/38634070/207528526-85a51b17-c035-477c-a565-b8e7cf695d26.png)

We start by ensuring our class is properly registered with the statement:
if(RegisterClassA(&window_class))

Docs for RegisterClassA:https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa

Then we can finally create our window using CreateWindowExA, and we need to save the handle of this window, so we'll call it window_handle. You can follow the documentation to see what each parameter is, the ones I have here name our application "Breakout", give us a visible window, use some default settings, and create the size as 1280 by 720.

Docs for CreateWindowExa: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa

Then finally we just need a loop to get our program started. We declare that if our window handle is valid, we will loop continuously, all the while grabbing any incoming messages and handling them, but if the message result ever equals 0, the program stops, and were done.

Now we have our window! Yay!
![image](https://user-images.githubusercontent.com/38634070/207694191-b56ea5e2-3209-4240-8fef-8a52c2cafe9a.png)

You'll notice that we can't close this window, this is simply because we haven't filled in a response to our WM_CLOSE message, so the program doesn't know what it should do when we hit the close button. To be able to close it, we can create a global bool variable that will keep track of whether or not our program is running, and then when we hit the close button, we can just set running = false;. Also at the top we should include stdbool.h.

So we can just add this at the top of the code somewhere:

    static bool running = true;

Then we can add into the WM_ClOSE case:

    running = false;

Lastly we can change our continuous message loop that we have in WinMain from the for(;;), which loops no matter what, to while(running), so that when we close the window, the loop will stop, and the program will end.

![image](https://user-images.githubusercontent.com/38634070/207989531-591afac3-51ea-4385-a4d6-824098fc264b.png)

Now we can close the window, change the size, all that good stuff. You can find the code up to this point is called Making_a_window.c

***
## Bitmap

Now that we have our window, the next thing we need to be able to do is paint it. What we need now is a bitmap of our window. The bitmap will allow us to have full control over all the pixels on the screen. This unfortunately will take some effort, as we need to do more communicating with Windows to allow us to store our bitmap in memory, and be able to pass it to windows so it can redraw our application.

Lets start by defining four global variables:

    static BITMAPINFO BitmapInfo; // This defines the dimensions and colors of our bitmap, among other things.
    static void *BitmapMemory; // A pointer to memory of where our bitmap is
    static HBITMAP BitmapHandle; // Handle to our bitmap
    static HDC BitmapDeviceContext; // The area and status of our bitmap

And two separate functions that we will fill in:

    // This will resize our bitmap whenever the window size changes.
    static void Win32ResizeDIBSection (int width, int height){}
    
    // This updates and redraws our window whenever we need it to.
    static void Win32UpdateWindow(HWND window, int x, int y, int width, int height){}
    
This part has a lot of nuance and is overall rather tedious, so lets just look at the code.
   
![image](https://user-images.githubusercontent.com/38634070/207993299-3d828e3e-4b31-495c-b972-4c2e0a45287f.png)

