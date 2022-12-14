#include <windows.h>

LRESULT 
window_callback (HWND    window,
                 UINT    message,
                 WPARAM  w_param,
                 LPARAM  l_param
                 ){
    LRESULT Result = 0;
    
    switch(message){
        case WM_SIZE:{ // What should our program do when we change the size of the window
        } break;
        
        case WM_DESTROY:{ // What should our program do when it is destroyed (that's something we would do)
        } break;
        
        case WM_CLOSE:{ // What should our program do when the closing window button is pushed.
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
            
            for(;;){
                MSG message;
                BOOL MessageResult = GetMessage(&message, 0, 0, 0);
                if(MessageResult > 0)
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                else{
                    break;
                } 
            }
        }
        return (0);
    }
    
}


