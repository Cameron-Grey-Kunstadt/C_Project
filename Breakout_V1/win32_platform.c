#include "utils.c"
#include "math.c"
#include <windows.h>
#include "platform_common.c"
#include "collision.c"
struct{
    // Platform non-spoecific part
    int width, height;
    u32 *pixels;
    
    // PLatform specific part
    BITMAPINFO bitmap_info;
    
} typedef Render_Buffer;


Render_Buffer render_buffer;

#include "software_rendering.c"
#include "game.c"

internal LRESULT
window_callback (HWND window, UINT message, WPARAM w_param,
                 LPARAM l_param){
    
    LRESULT result = 0;
    
    switch(message){
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;
        
        case WM_SIZE:{
            RECT rect;
            GetClientRect(window, &rect);
            render_buffer.width = rect.right - rect.left;
            render_buffer.height = rect.bottom - rect.top;
            
            if (render_buffer.pixels) {
                VirtualFree(render_buffer.pixels,0, MEM_RELEASE);
                //free
            }
            
            render_buffer.pixels = VirtualAlloc(0, sizeof(u32)*render_buffer.width*render_buffer.height,
                                                MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
            
            //Get width and height
            
            //allocate the buffer
            
            //fill the bitmapinfo
            render_buffer.bitmap_info.bmiHeader.biSize = sizeof(render_buffer.bitmap_info.bmiHeader);
            render_buffer.bitmap_info.bmiHeader.biWidth = render_buffer.width;
            render_buffer.bitmap_info.bmiHeader.biHeight = render_buffer.height;
            render_buffer.bitmap_info.bmiHeader.biPlanes = 1;
            render_buffer.bitmap_info.bmiHeader.biBitCount = 32;
            render_buffer.bitmap_info.bmiHeader.biCompression = BI_RGB;
        } break;
        
        default:{
            result = DefWindowProcA(window, message, w_param, l_param);
        }
    }
    return result;
}

int WinMain(HINSTANCE hINSTANCE, HINSTANCE hPrevInstance,
            LPSTR lpCmdLine, int nShowCmd){
    
    WNDCLASSA window_class = {0};
    window_class.style = CS_HREDRAW|CS_VREDRAW;
    window_class.lpfnWndProc = window_callback;
    window_class.lpszClassName = "Game_Window_Class";
    
    RegisterClassA(&window_class);
    
    HWND window =
        CreateWindowExA(0, window_class.lpszClassName, "ET_clone",
                        WS_VISIBLE|WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                        CW_USEDEFAULT, 1280,720, 0, 0, 0, 0);
    
    //Handle to device context
    HDC  hdc = GetDC(window);
    
    Input input = {0};
    
    LARGE_INTEGER last_counter;
    QueryPerformanceCounter(&last_counter);
    
    LARGE_INTEGER frequency_counter_large;
    QueryPerformanceFrequency(&frequency_counter_large);
    f32 frequency_counter = (f32)frequency_counter_large.QuadPart;
    
    f32 last_dt = 0.01666;
    
    while (running){
        //Input
        
        for (int i = 0; i < BUTTON_COUNT; i++){
            input.buttons[i].changed = false;
        }
        
        MSG message;
        while (PeekMessageA(&message, window, 0, 0, PM_REMOVE)){
            
            switch(message.message){
                case WM_SYSKEYDOWN:
                case WM_SYSKEYUP:
                case WM_KEYDOWN:
                case WM_KEYUP:{
                    u32 vk_code = (u32)message.wParam;
                    b32 was_down = ((message.lParam & (1 << 30)) != 0);
                    b32 is_down  = ((message.lParam & (1 << 31)) == 0);
                    
#define process_button(vk, b) \
if (vk_code == vk){\
input.buttons[b].changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
}
                    
                    process_button(VK_LEFT, BUTTON_LEFT);
                    process_button(VK_RIGHT, BUTTON_RIGHT);
                    process_button(VK_UP, BUTTON_UP);
                    process_button(VK_DOWN, BUTTON_DOWN);
                }break;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        
        
        /* Call the mouse cursor, this GetCursorPos returns the position relative to screen, so we need ScreenToClient
to convert those coordinates for our game. Also the y-coordinate is naturally inverted and offset by an entire
window height.

*/
        POINT mouse_pointer;
        GetCursorPos(&mouse_pointer);
        ScreenToClient(window, &mouse_pointer);
        
        input.mouse.x = mouse_pointer.x;
        input.mouse.y = render_buffer.height-mouse_pointer.y;
        
        //SIMULATIONclear_screen(0x551100)
        simulate_game(&input, last_dt);
        
        
        //Render
        StretchDIBits(hdc, 0, 0, render_buffer.width, render_buffer.height, 0, 0, render_buffer.width, render_buffer.height, render_buffer.pixels, &render_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
        
        // Get the frame time
        LARGE_INTEGER current_counter;
        QueryPerformanceCounter(&current_counter);
        
        last_dt = (f32)(current_counter.QuadPart - last_counter.QuadPart) / frequency_counter;
        
        last_counter = current_counter;
    }
}