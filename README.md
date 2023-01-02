# Example Function Hooks for X64 Architecture

Example/Template Project to demonstrate hooking Program Functions under X64 Architecture using the latest Version of Microsoft Detours.

Features:
  - Hook Void and Type Function example
  - Modify and intercept Arguments
  - Signature Scanning to find Function Address
  - Ability to specify Function Address without Signature Scanning ( For fast testing )

Compiling:
  1. Clone Repository to your local machine.
  2. Open and Build Solution in Visual Studio 2022.
  3. Go to ExampleFunctionHookX64\x64\Debug and run TestAppToHook.exe
  4. Execute SimpleInjector.exe to inject the DLL and observe Modifications
  
Motivation/Aim of Project:
  - Finding clear Information on Function Hooking is rather difficult, especially on X64 Target Platforms so this Project should simplify
  the Process for anyone looking to get started in this Topic, beware that this example is just one of many ways to do this and is also not
  the most proficient code. Function Hooking plays a very important Role if you want to create Modifications for a closed-source Game.
  
Credits:
  - Microsoft ( MS Detour Library )
  - Signature Scanning https://www.unknowncheats.me/forum/general-programming-and-reversing/317273-pattern-scan-x64-bit.html
  - Injector ( Came from Github Repo but i forgot the Link, still all Credit to the Original Author! )
