# ---- LPeDNN v0 ---- #

Starting project template: 12_sample_GLCD_touchpanel

GIT INCLUDE PATH PROBLEM:
The launcher of the project (sample.uvprojx) is a XML file which contains compiling, linking, debugging configurations
and also the targeted files in the project along with groups of targets.
This means that it's necessary and recommended synchronize also this file, especially when you add new files, folders and target groups.
When you want to push this file into main branch, you may want to solve conflicts, so leave the lines that you don't want to globally modify
as they are.
Briefly: in this XML file the only useful thing to have always synchronized is the <Targets>/<Target>/<Groups> XML-object because it maps the actual files present in folders
in the targeted groups appearing on the left project file/folders pane.
The most important line that you don't have to change is:
<IncludePath>C:\Users\rugge\AppData\Local\Arm\Packs\ARM\CMSIS\5.7.0\CMSIS\Core\Include</IncludePath>
Pull: When you want to pull the sample.uvprojx along with new files commited from other users, you'll are prompted with a conflict on this line along with other
changed parameter configurations.
Always discard the pulled <IncludePath> parameter and just always leave your own <IncludePath> parameter while solving conflicts on this file.
Push: When you want to push this file to main, always remember to don't change the default configuration parameters (debug, linking..) with strange testing parameters..
So you may want to pull the origin/main, resolving the conflict leaving the default well-tested debug/compiling/linking configuration that is present on origin/main and, after that,
push your commit.

Debug/Compiling/Linking configurations:
You may notice that in sample.uvprojx there is the whole toolchain configuration, so if you don't want to overwrite your own configuration, when pulling the origin/main
you'll have a conflict, while resolving the conflict you'll have the choice of maintain your own parameter(s) or overwrite it/them with origin/main parameter(s).

GIT CONFIGURATION IN KEIL (!NOT RECOMMENDED)
- Open SVCS -> Configure Software Version Control...
- Enter the path to the template file (usually located in C:\Keil_v5\UV4\GIT.SVCS)
- Ok
Then, under SVCS, you can:
- Blame files (for resolving conflicts)..
- Stash, pull, push, status, rebase etc.
