// this will stub host, based on your api yaml files
import { readFile } from 'fs/promises'
import YAML from 'yaml'
import { glob } from 'glob'

const types = YAML.parse(await readFile('api/types.yml', 'utf8'))

// map param/return types to C types
function typeMap(t) {
  if (t === 'void') return 'void'
  if (t === 'string' || t.endsWith('[]') || t[0].toUpperCase() === t[0]) return 'u32'
  return t  // use the type directly from yaml (u8, u32, etc)
}

const out = [`// Null0 cart API definition for C

#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef float f32;
typedef double f64;

// import function from host
#define HOST_FUNCTION(return_type, name, params) __attribute__((import_module("null0"), import_name(#name))) return_type name params;

// export function to host
#define CART_FUNCTION(n) __attribute__((export_name(n)))

// mem-management

CART_FUNCTION("malloc")
void* _wasm_host_malloc(size_t size) {
  return malloc(size);
}

CART_FUNCTION("free")
void _wasm_host_free(void* ptr) {
  free(ptr);
}

// callbacks
CART_FUNCTION("load")
void load();

CART_FUNCTION("update")
void update(uint64_t timeMS);

CART_FUNCTION("unload")
void unload();


typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

Color LIGHTGRAY = (Color){.r = 200, .g = 200, .b = 200, .a = 255};
Color GRAY = (Color){.r = 130, .g = 130, .b = 130, .a = 255};
Color DARKGRAY = (Color){.r = 80, .g = 80, .b = 80, .a = 255};
Color YELLOW = (Color){.r = 253, .g = 249, .b = 0, .a = 255};
Color GOLD = (Color){.r = 255, .g = 203, .b = 0, .a = 255};
Color ORANGE = (Color){.r = 255, .g = 161, .b = 0, .a = 255};
Color PINK = (Color){.r = 255, .g = 109, .b = 194, .a = 255};
Color RED = (Color){.r = 230, .g = 41, .b = 55, .a = 255};
Color MAROON = (Color){.r = 190, .g = 33, .b = 55, .a = 255};
Color GREEN = (Color){.r = 0, .g = 228, .b = 48, .a = 255};
Color LIME = (Color){.r = 0, .g = 158, .b = 47, .a = 255};
Color DARKGREEN = (Color){.r = 0, .g = 117, .b = 44, .a = 255};
Color SKYBLUE = (Color){.r = 102, .g = 191, .b = 255, .a = 255};
Color BLUE = (Color){.r = 0, .g = 121, .b = 241, .a = 255};
Color DARKBLUE = (Color){.r = 0, .g = 82, .b = 172, .a = 255};
Color PURPLE = (Color){.r = 200, .g = 122, .b = 255, .a = 255};
Color VIOLET = (Color){.r = 135, .g = 60, .b = 190, .a = 255};
Color DARKPURPLE = (Color){.r = 112, .g = 31, .b = 126, .a = 255};
Color BEIGE = (Color){.r = 211, .g = 176, .b = 131, .a = 255};
Color BROWN = (Color){.r = 127, .g = 106, .b = 79, .a = 255};
Color DARKBROWN = (Color){.r = 76, .g = 63, .b = 47, .a = 255};
Color WHITE = (Color){.r = 255, .g = 255, .b = 255, .a = 255};
Color BLACK = (Color){.r = 0, .g = 0, .b = 0, .a = 255};
Color BLANK = (Color){.r = 0, .g = 0, .b = 0, .a = 0};
Color MAGENTA = (Color){.r = 255, .g = 0, .b = 255, .a = 255};
Color RAYWHITE = (Color){.r = 245, .g = 245, .b = 245, .a = 255};`]

for (const f of await glob('api/*.yml')) {
  if (f === 'api/types.yml') continue
  const api = YAML.parse(await readFile(f, 'utf8'))
  const apiName = f.split('/').pop().split('.')[0]
  out.push(`// ${apiName.toUpperCase()} API\n`)

  for (const [fname, func] of Object.entries(api)) {
    out.push(`// ${func.description}`)
    const args = Object.entries(func.arguments).map(([name, type]) => `${type.replace('string', 'char*').replace('[]', '*')} ${name}`).join(', ')

    const returnType = typeMap(func.returns)
    out.push(`HOST_FUNCTION(${returnType}, ${fname}, (${args}))\n`)
  }
}

console.log(out.join('\n'))
