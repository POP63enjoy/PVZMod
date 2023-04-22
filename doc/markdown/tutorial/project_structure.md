# 项目结构 {#tutorial_project_structure}

[TOC]

## Visual Studio 中的项目结构

创建一个名为 `MyFirstMod` 的项目，在 Visual Studio 中，结构是这样的：

* 解决方案：`MyFirstMod`
  * 文件夹：`MyFirstMod`
    * DLL 项目：`MyFirstMod`
    * EXE 项目：`MyFirstModLauncher`

DLL 项目 `MyFirstMod` 编译后会生成一个 DLL，这个 DLL 将会被注入到游戏中，改版的主要代码应写在 DLL 项目中。EXE 项目 `MyFirstModLauncher` 是游戏的启动器，其编译生成的 EXE 文件，将会运行游戏并注入 DLL。

## 文件夹结构

打开解决方案文件夹，结构是这样的：

* 文件夹 `MyFirstMod`
  * 文件夹 `MyFirstMod`
    * DLL 项目所在文件夹 `MyFirstMod`
    * EXE 项目所在文件夹 `MyFirstModLauncher`
  * 文件夹 `Output`

DLL 项目和 EXE 项目编译后将生成在 `Output` 文件夹，此文件夹为游戏文件夹，发布时，应将此文件夹打包发布。

在游戏文件夹中，通常包括一个 `game` 文件夹，存放原版游戏文件，其中包括 `PlantsVsZombie.exe`，你也可以修改 `MyFirstModLauncher` 的代码，修改文件夹名称，或者将 `PlantsVsZombie.exe` 的后缀改掉，以防止玩家启动原版游戏。

为了保证项目的可维护性，请保证 `game` 文件夹中的所有文件保持为原版，不要对原版文件进行任何修改，如要修改原版文件，请使用 FolderMappingInterface 将游戏文件夹下的另一个文件夹例如 `data` 映射到游戏工作目录。这项规则仅适用于开发阶段，发布时为了节省空间，可以通过写脚本批量删除被覆盖而未使用的原版文件。

游戏文件夹下仅用于存放不变的文件，对于游戏存档、配置文件等可变的文件，应存放在 ProgramData、AppData、文档或注册表中。

## 在一个解决方案中创建多个项目

右键解决方案，新建项目，可以在现有的解决方案中添加新的项目，同一解决方案中的所有项目将共享一个 `Output` 文件夹。注意：多个项目的 DLL 不可共存于一个游戏进程。
