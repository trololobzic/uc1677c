# UC1677C LCD Library (CGS164A00-THW-R / CGS214A06-THW-R)

A lightweight, **header-only** C++11 library for controlling LCD displays based on the **UC1677C** controller by the I2C interface. Designed specifically for resource-constrained embedded systems.

## 🚀 Key Features
- **Header-only**: No complex build system required, just include the header.
- **C++11 Standard**: Efficient code without unnecessary overhead.
- **Supported Modules**: Full compatibility with **CGS164A00** and **CGS214A06** displays.
- **Cross-Compiler Support**: Tested with `msp430-elf-g++` and `avr-gcc`.

## 🛠 Prerequisites
- A compiler with **C++11** support or higher.
- A configured communication interface I2C on your target MCU.

## 📦 Installation
Since this is a header-only library, no installation is needed:
1. Copy the `include/` directory into your project.
2. Include in your source code:
    ```c++
    #include "cgs164a00.hpp"
    ```

    or:

    ```c++
    #include "cgs164a00.hpp"
    ```

## 🛠 Hardware Interface (I2C)

The library is **template-based**, meaning you must provide an I2C implementation as a template parameter. This allows for zero-overhead abstraction and easy porting between different MCUs (MSP430, AVR, etc.).

### Required I2C Structure
Your I2C provider must be a `struct` with the following static methods:

```c++
struct MyI2C {
    static void init() {
        /* Initialize I2C hardware */
    }
    static void start_transmission(uint8_t byte) {
        /* Send START condition and device address */
    }
    static void end_transmission() {
        /* Send END condition */
    }
    static bool write_byte(uint8_t byte) {
        /* Send byte and return true if ACK received */
        return true;
    }
    static uint8_t read_byte() {
        /* Read byte from bus */
        return 0x00;
    }
};
```

## 📂 Examples
The library includes ready-to-use examples located in the [/examples](./examples) folder:

### 🔧 MSP430 (Professional Toolchain)
Located in `examples/msp430_demo/`. This example uses a **Makefile** for automated building.
- **Compiler**: `msp430-elf-g++`
- **How to run**: Navigate to the folder and run `GCC_PATH='path_to_msp430_gcc' make`. For example `GCC_PATH=/opt/ti/msp430-gcc make`

### ♾️ AVR / Arduino
Located in `examples/avr_arduino/`. Provided as a standard `.ino` file.
- **Environment**: Arduino IDE or PlatformIO.
- **Hardware**: Any ATmega-based board (e.g., Arduino Nano/Uno).
- **How to run**: Open the `.ino` file in Arduino IDE and click **Upload**.

### Basic Usage Snippet
```c++
#include "cgs164a00.hpp"

using Lcd = uc1677c::Cgs164a00<MyI2C>;
Lcd lcd;

int main()
{
    lcd.init();
    lcd.print(Lcd::CharacterStrings::main, "Trololo");
    lcd.update();
    return 0;
}
```

## 📝 License
This project is licensed under the MIT License.

