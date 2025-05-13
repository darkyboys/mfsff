# **MFSFF - Magma File System For Files**

**Author**: ghgltggamer
**License**: MIT License
**Version**: 2025

---

## **Overview**

`MFSFF` (Magma File System For Files) is a low-level library designed for managing files with a custom format in memory. It provides functionality to mount, write, and unmount virtual files, where files are represented in a custom format and handled as a collection of encoded strings. The library includes file parsing, encryption, and decryption mechanisms for maintaining and processing file content in memory.

### **Features**

* Mount virtual files from raw encoded data.
* Write virtual files back to the raw encoded format.
* Support for custom file formats with delimiters for file structure.
* Built-in encryption/decryption using `cascrypt` and `CASCI` libraries.

---

## **Installation**

To use `MFSFF`, include the library in your project and ensure that the following dependencies are available:

* **scxx**: Utility for working with custom string types.
* **casci**: For performing custom encryption and decryption of file names and contents.
* **cascrypt**: Encryption utility used for decoding/encoding file content.

Include the header:

```cpp
#include "path/to/mfsff.hh"
```

---

## **Usage**

### **Namespace**: `mfsff`

All functions and classes are enclosed in the `mfsff` namespace. You need to access them via the `mfsff::` prefix.

---

### **Classes**

#### `mfsff::file`

This class represents a virtual file within the `MFSFF` system. A `file` object holds the file's raw data, along with its associated file names and contents.

##### **Public Members**:

* `bool is_mounted`: Indicates whether the file is currently mounted (parsed).
* `alph raw`: A custom string type representing the raw file data.
* `std::vector<std::string> file_name`: A list of file names (extracted from the raw data).
* `std::vector<std::string> file_content`: A list of file contents (extracted from the raw data).

---

### **Functions**

#### `int mount(mfsff::file* file_in)`

Mounts a raw file by parsing its data into file names and file contents. This function reads through the raw string and extracts information based on delimiters.

**Parameters**:

* `file_in`: A pointer to the `mfsff::file` object you wish to mount.

**Returns**:

* `1`: Success.
* `-1`: Parsing error.
* `2`: File is already mounted.

**Example**:

```cpp
mfsff::file my_file;
my_file.raw = "raw_encoded_data_here";
int result = mfsff::mount(&my_file);
```

#### `int write(mfsff::file* file)`

Writes the mounted file data back to a raw encoded format. This function encodes both the file names and contents, then constructs a raw string.

**Parameters**:

* `file`: A pointer to the `mfsff::file` object to be written.

**Returns**:

* `1`: Success.
* `-1`: File is not mounted.
* `-2`: File names and contents are not parallel (unequal lengths).

**Example**:

```cpp
int result = mfsff::write(&my_file);
```

#### `int umount(mfsff::file* file)`

Unmounts the file, clearing all its content and resetting its state.

**Parameters**:

* `file`: A pointer to the `mfsff::file` object to unmount.

**Returns**:

* `1`: Success.
* `0`: File was not mounted.

**Example**:

```cpp
int result = mfsff::umount(&my_file);
```

---

## **Data Format**

The `MFSFF` library uses a custom data format for representing virtual files in memory. Files are enclosed between delimiters and are structured as follows:

* **File Start**: Denoted by the character `(`.
* **File Name and Content Delimiters**:

  * `FILE_START ('(')` marks the start of a new file.
  * `FILE_NEND (')')` marks the end of the file name and the beginning of the content.
  * `FILE_END ('+')` marks the end of the file content.

**Example** (raw data):

```txt
(file_name_1)(file_content_1)+
(file_name_2)(file_content_2)+
```

The file names and contents are encrypted before being stored, ensuring data privacy.

---

## **Encryption & Decryption**

`MFSFF` uses two libraries for encryption:

* **`CASCI`**: Encrypts and decrypts file names and content.
* **`cascrypt`**: Handles raw encoding and decoding.

These libraries are used for encoding and decoding file names and contents to maintain privacy and security.

---

## **Example**

### **Full Example**

```cpp
#include "mfsff.hh"

int main() {
    // Create and mount a new virtual file
    mfsff::file my_file;
    my_file.raw = "(file_name_1)(file_content_1)+";
    
    // Mount file
    int mount_result = mfsff::mount(&my_file);
    if (mount_result != 1) {
        std::cerr << "Mounting failed!" << std::endl;
        return 1;
    }

    // Write the file back to the raw format
    int write_result = mfsff::write(&my_file);
    if (write_result != 1) {
        std::cerr << "Writing failed!" << std::endl;
        return 1;
    }

    // Unmount the file
    int umount_result = mfsff::umount(&my_file);
    if (umount_result != 1) {
        std::cerr << "Unmounting failed!" << std::endl;
        return 1;
    }

    std::cout << "File processed successfully!" << std::endl;
    return 0;
}
```

---

## **Contributions**

Feel free to fork, modify, and contribute to the development of `MFSFF`. If you'd like to contribute improvements, please submit a pull request, and make sure to adhere to the MIT license terms.

---

## **License**

`MFSFF` is licensed under the MIT License. See the `LICENSE` file for more details.
