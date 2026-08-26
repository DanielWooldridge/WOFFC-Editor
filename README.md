# WOFFC Editor

A Windows-based C++ tool for editing and managing WOFFC scene and game data.

## Overview

**WOFFC Editor** is a native Windows development tool built in C++ for working with WOFFC game content. The project combines a graphical editing environment with scene/object management, rendering, camera controls, and local data storage.

The editor provides the foundation for creating, inspecting, and modifying game-world content through a dedicated desktop tool rather than directly editing the underlying data files.

## Features

* **Scene and object editing** — Create, select, and manipulate objects within an editable scene.
* **3D rendering** — DirectX-based rendering and display systems.
* **Camera controls** — Dedicated camera and viewport functionality for navigating scenes.
* **Object management** — Scene objects, display objects, and chunk-based world structures.
* **Local data storage** — SQLite integration for project/game data.
* **Windows desktop interface** — Native Win32/MFC components and Visual Studio project support.
* **Game/tool integration** — Editor and game-oriented systems share common structures and rendering components.

## Project Structure

The main editor is located in:

```text
WOFFCEdit/
├── Camera.*              # Camera and viewport functionality
├── ChunkObject.*         # Chunk-based world objects
├── DisplayChunk.*        # Chunk rendering/display
├── DisplayObject.*       # Renderable objects
├── Game.*                # Game/tool runtime systems
├── ObjectEditor.*        # Object editing functionality
├── SceneObject.*         # Scene and object representation
├── SelectDialogue.*      # Object/asset selection UI
├── ToolMain.*            # Main editor/tool application
├── database/
│   └── data/             # Project/database data
├── packages/              # Project dependencies
├── sqlite3.c
├── sqlite3.h
└── Win32SimpleSample.vcxproj
```

## Technology

* **C++**
* **Visual Studio**
* **DirectX**
* **DirectXTK**
* **Win32 / MFC**
* **SQLite**

## Building

### Requirements

* Windows
* Visual Studio with C++ desktop development tools
* DirectX/DirectXTK dependencies included with the project
* A compatible version of the Visual Studio toolchain

### Build

Open the Visual Studio solution:

```text
Win32SimpleSample.sln
```

Select the desired configuration and platform, then build the solution from Visual Studio.

## Status

This repository contains an early-stage/legacy development version of the WOFFC Editor. Some components may reflect experimental or work-in-progress functionality.

## Purpose

The goal of WOFFC Editor is to provide a practical development environment for working with WOFFC game content, making it easier to inspect, edit, and manage scenes and objects through a dedicated graphical tool.

## License

No license is currently specified for this repository.

If you intend to distribute the project publicly, add an appropriate `LICENSE` file.

---

**Repository:** `WOFFC-Editor`

**Project:** WOFFC Editor
**Language:** C++
**Platform:** Windows
