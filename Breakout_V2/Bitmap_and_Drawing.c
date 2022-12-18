#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

// Global variable for the running status of our application
static bool running = true; 

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t  uint32;
typedef uint64_t uint64;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t  int32;
typedef int64_t int64;

static BITMAPINFO BitmapInfo;
static void *BitmapMemory;
static int BitmapWidth;
static int BitmapHeight;
static int BytesPerPixel = 4;


static void
ExampleDrawing(int xOffset, int yOffset){
    
    int width = BitmapWidth;
    int height = BitmapHeight;
    
    int Pitch = width*BytesPerPixel;
    uint8 *Row = (uint8 *)BitmapMemory;
    
    for(int y = 0;y < BitmapHeight;++y){
        
        uint8 *Pixel = (uint8 *)Row;
        for(int x = 0;x < BitmapWidth;++x){
            /*Pixel would be in memory: RR GG BB xx, and memory is little endian architecture so it used to load in as
0x xxBBGGRR
       
But devs wanted to be able to see the hexcode in memory as RGB, so it actually loads as so:
BB GG RR xx 
to
0x xxRRGGBB

*/
            *Pixel = (uint8)(x + xOffset);
            ++Pixel;
            
            *Pixel = (uint8)(y + yOffset);
            ++Pixel;
            
            *Pixel = 0;
            ++Pixel;
            
            *Pixel = 0;
            ++Pixel;
        }
        Row += Pitch;
    }
}


static void
Win32ResizeDIBSection(int width, int height){
    
    // If we already have memory for our bitmap, lets release it
    if(BitmapMemory){ 
        VirtualFree(BitmapMemory,0 ,MEM_RELEASE); 
    }
    
    // Set the new width and height of our bitmap
    BitmapWidth = width;
    BitmapHeight = height;
    
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader); // Set some important variables in our bitmap, including size
    BitmapInfo.bmiHeader.biWidth = BitmapWidth;
    BitmapInfo.bmiHeader.biHeight = -BitmapHeight; // Lets flip the height so windows draws the screen top-down
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;
    
    int BitmapMemorySize = (width*height)*BytesPerPixel; // we need the size of our memory for our bitmap, 4 bytes for each pixel
    // Now lets allocate that memory!
    BitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
}



static void
Win32UpdateWindow(HDC DeviceContext, RECT *ClientRect, int x, int y, int width, int height){
    
    // based on the sizes from the ClientRect we can get the width and height.
    int WindowWidth = ClientRect->right - ClientRect->left;
    int WindowHeight = ClientRect->bottom - ClientRect->top;
    
    /* This function automatically allows us to stretch and scale our bitmap to the size of our window, 
passing in our DeviceContext, width, height, our BitmapMemory, and BitmapInfo. The rest is default settings, and normal RGB colors*/
    StretchDIBits(DeviceContext,
                  0, 0, BitmapWidth, BitmapHeight,
                  0, 0, WindowWidth, WindowHeight,
                  BitmapMemory,
                  &BitmapInfo,
                  DIB_RGB_COLORS, SRCCOPY);
    
}

LRESULT 
window_callback (HWND    window,
                 UINT    message,
                 WPARAM  w_param,
                 LPARAM  l_param
                 ){
    LRESULT Result = 0;
    
    switch(message){
        case WM_SIZE:{ // What should our program do when we change the size of the window
            RECT ClientRect;
            GetClientRect(window, &ClientRect);
            int width = ClientRect.right - ClientRect.left;
            int height = ClientRect.bottom - ClientRect.top;
            Win32ResizeDIBSection(width, height);
        } break;
        
        case WM_DESTROY:{ // What should our program do when it is destroyed (that's something we would do)
            
        } break;
        
        case WM_CLOSE:{ // What should our program do when the closing window button is pushed.
            running = false;
        } break;
        
        case WM_PAINT:{
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(window, &Paint);
            int x = Paint.rcPaint.left;
            int y = Paint.rcPaint.top;
            int width = Paint.rcPaint.right - Paint.rcPaint.left;
            int height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            
            RECT ClientRect;
            GetClientRect(window, &ClientRect);
            
            Win32UpdateWindow(DeviceContext, &ClientRect,x , y, width, height);
            EndPaint(window, &Paint);
        } break;
        default:{ // What should our program do when it's running normally.
            Result = DefWindowProc(window, message, w_param, l_param);
        } break;
    }
    return(Result);
}

// Entry point into the program.
int WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR     lpCmdLine,
            int       nShowCmd){
    
    // Window struct, we clear all values to 0 then just change the ones we need.
    WNDCLASS window_class = {};
    
    // There are lots of style modifiers, these 2 are just the most essential for running a graphical program.
    window_class.style = CS_HREDRAW|CS_VREDRAW;
    
    // We need to define our own windows procedure up above.
    window_class.lpfnWndProc = window_callback;
    
    // Pass in a handle to our instance, we have this from WinMain.
    window_class.hInstance = hInstance;
    
    // Just need a name for our class.
    window_class.lpszClassName = "breakout_window_class";
    
    if(RegisterClassA(&window_class))
    {
        // The handle to a "create a window" function, with some parameters specifying info about our window.
        HWND window_handle = CreateWindowExA(0,window_class.lpszClassName,"Breakout",WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                             CW_USEDEFAULT,CW_USEDEFAULT,1280,720,
                                             0,0,hInstance,0);
        // As long as our window handle is valid..
        if(window_handle){
            int xOffset = 0;
            int yOffset = 0;
            running = true;
            while(running){ // This code below initializes a bool called MessageResult, which should remain non-zero while our program is running. If it ever returns 0, the program stops. 
                
                
                MSG message;
                while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)){
                    
                    if(message.message == WM_QUIT){
                        running = false;
                    }
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                
                ExampleDrawing(xOffset, yOffset); //Render our desired bitmap
                
                HDC DeviceContext = GetDC(window_handle);
                RECT ClientRect;
                GetClientRect(window_handle, &ClientRect);
                int ClientWidth = ClientRect.right - ClientRect.left;
                int ClientHeight = ClientRect.bottom - ClientRect.top;
                
                Win32UpdateWindow(DeviceContext, &ClientRect, 0, 0, ClientWidth, ClientHeight); //Update our window
                ReleaseDC(window_handle, DeviceContext); // Release our previous DC
                
                ++xOffset;
            }
        }
        return (0);
    }
    
}


