# PVZMod - 植物大战僵尸改版制作框架（开发中……）

## 环境配置

1. 下载源码到任意文件夹。
2. 使用 Visual Studio 2022 打开解决方案 `PVZMod.sln` ，以 `x86-Debug` 和 `x86-Release` 配置编译。
3. 添加环境变量，变量名为 `PVZMod_63enjoy_Path` ，变量值为源码路径（以斜杠结尾）。
4. 将 `PVZMod_63enjoy_Template` 文件夹打包为 zip 压缩包，复制到 `C:\Users\<用户名>\Documents\Visual Studio 2022\Templates\ProjectTemplates` 。
5. 建议安装 VS 插件 [Microsoft Child Process Debugging Power Tool 2022](https://marketplace.visualstudio.com/items?itemName=vsdbgplat.MicrosoftChildProcessDebuggingPowerTool2022) 以对游戏进行调试。

## 创建项目

1. 打开 Visual Studio 2022 ，点击“创建新项目”，选择“PVZMod 模板”，创建。
2. 将启动项目设置为 `<项目名>Launcher` 。
3. 选择配置 x86 ，生成解决方案。
4. 到解决方案所在目录，进入 `Output` 文件夹，新建 `game` 文件夹，将 `1.0.4.7924` 版本的游戏复制到里面。
5. 如安装了 VS 插件 Microsoft Child Process Debugging Power Tool 2022 ，进入 `调试 -> 其它调试目标 -> Child Process Debugging Settings...` ，勾选 `Enable child process debugging` 。
6. 开始调试，如果游戏开始运行，则项目创建成功。
7. 如有需要，可以在解决方案中创建其它“PVZMod 模板”项目，多个改版项目可在一个解决方案中共存，共享游戏文件。
