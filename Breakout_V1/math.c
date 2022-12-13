internal int
clamp(int min, int val, int max){
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

static inline f32
lerp(f32 a, f32 t, f32 b){
    return (1-t)*a + t*b;
}

//Color
static inline u32
make_color_from_grey(u8 grey){
    return (grey << 0) |
    (grey << 8) |
    (grey << 16);
}

// Vector of two 32bit floats, for screen coordinates

struct{
    union{
        struct{
            f32 x;
            f32 y;
        };
        
        f32 e[2];
    };
} typedef v2;

static inline v2
add_v2(v2 a, v2 b){
    return (v2){a.x + b.x, a.y + b.y};
}

static inline v2
mul_v2(v2 a, f32 s){
    return (v2){a.x*s, a.y*s};
}


// Vector of two ints, for screen coordinates
struct{
    union{
        struct{
            int x;
            int y;
        };
        
        int e[2];
    };
} typedef v2i;