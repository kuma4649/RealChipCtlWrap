@echo off
echo zip,dll,exe�t�@�C����Zone���ʎq���폜���܂��B
pause

echo on
FOR %%a in (*.zip *.dll *.exe) do (echo . > %%a:Zone.Identifier)
FOR %%a in (compiler\*.zip compiler\*.dll compiler\*.exe) do (echo . > %%a:Zone.Identifier)
FOR %%a in (player\*.zip player\*.dll player\*.exe) do (echo . > %%a:Zone.Identifier)
FOR %%a in (toVgm\*.zip toVgm\*.dll toVgm\*.exe) do (echo . > %%a:Zone.Identifier)
FOR %%a in (toWav\*.zip toWav\*.dll toWav\*.exe) do (echo . > %%a:Zone.Identifier)
@echo off

echo �������܂����B
pause
echo on
