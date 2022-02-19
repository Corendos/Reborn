$vsPath = (& "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -products * -property installationPath)
cmd /c "`"$vsPath\VC\Auxiliary\Build\vcvarsall.bat`" x64 & set" | ForEach-Object {
    if ($_ -match "=") {
        $v = $_.split("="); Write-Output "$($v[0])=$($v[1])" >> $GITHUB_ENV; Write-Output "$($v[0])=$($v[1])"
    }
}