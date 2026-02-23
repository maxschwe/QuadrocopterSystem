# API Laser Tracker SDK – Python Wrapper

## Overview

This package provides Python bindings for the **API Laser Tracker SDK**, enabling communication with laser tracking hardware directly from Python. It includes sample code, documentation, and prebuilt `.whl` files for supported platforms.

---

## Folder Contents

- `api_lasertracker-<sdk-version>-<python-tag>-<os-arch>.whl`  
  Prebuilt Python wheel for a specific Python version and platform.

- `LaserTrackerInterfaceDocument.chm`  
  SDK documentation in CHM format (Windows only).  
  > ⚠️ If the contents appear blank after opening, right-click the file → **Properties** → check **Unblock** → click **Apply** and **OK**. Reopen the file to view contents properly.

- `html/`  
  Alternative HTML documentation. Open `html/index.html` in your browser.

- `tracker_example.ipynb`  
  Jupyter notebook demonstrating basic usage and function calls.

---

## Installation

To install the Python package, use the appropriate `.whl` file matching your Python version and OS architecture.

```bash
pip install api_lasertracker-<sdk-version>-<python-tag>-<os-arch>.whl
```

### Notes

- `<python-tag>` specifies the required Python version:  
  - `cp38-cp38` → Python 3.8.x  
  - `cp310-cp310` → Python 3.10.x  
  - `cp312-cp312` → Python 3.12.x

- `<os-arch>` specifies the operating system and architecture:  
  - `win_amd64` → Windows 64-bit (Windows 10 / 11)  
  - `x86_64-linux-gnu` → Linux 64-bit (x86-based)  
  - `aarch64-linux-gnu` → Linux 64-bit (ARM-based)  
  - `darwin` → macOS

---

## Getting Help

You can explore SDK functionality using built-in Python introspection tools or the documentation.

### Using Python `help()`

```python
from api_lasertracker import ltpy

# General module help
help(ltpy)

# Specific class help
help(ltpy.LaserTrackerInterface)

# Specific function help
help(ltpy.LaserTrackerInterface.connect)
```

These will provide descriptions, argument details, and return types for SDK functions.

### Documentation

- **Windows**: `LaserTrackerInterfaceDocument.chm`
- **Cross-platform**: `html/index.html` (open in any browser)
